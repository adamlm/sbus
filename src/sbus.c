/**
 * MIT License
 *
 * Copyright (c) 2020 Adam Morrissett
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdint.h>
#include "../inc/sbus.h"

static uint8_t inFrame = 0U;
static uint8_t frame[SBUS_FRAME_SIZE] = {0x00U};
static uint8_t frameIndex = 0U;

static SBusPacketTypeDef packet;

uint8_t SBus_ParseByte(uint8_t byte) {
    if (!inFrame && byte == SBUS_START_BYTE) {
        frameIndex = 0U;
        inFrame = 1U;
    }

    if (inFrame) {
        frame[frameIndex++] = byte;

        if (frameIndex >= SBUS_FRAME_SIZE) {
            if (byte == SBUS_END_BYTE) {
                return SBUS_FRAME_READY;
            }

            frameIndex = 0U;
            inFrame = 0U;
        }
    }

    return SBUS_FRAME_NOT_READY;
}

void SBus_DecodeFrame(void) {
    packet.channel0 = ((frame[2] & 0x07U) << 8U) | frame[1];
    packet.channel1 = ((frame[3] & 0x3FU) << 5U) | ((frame[2] & 0xF8U) >> 3U);
    packet.channel2 = ((frame[5] & 0x01U) << 10U) | ((frame[4] & 0xFFU) << 2U) | ((frame[3] & 0xC0U) >> 6U);
    packet.channel3 = ((frame[6] & 0x0FU) << 7U) | ((frame[5] & 0xFEU) >> 1U);
    packet.channel4 = ((frame[7] & 0x7FU) << 4U) | ((frame[6] & 0xF0U) >> 4U);
    packet.channel5 = ((frame[9] & 0x03U) << 9U) | ((frame[8] & 0xFFU) << 1U) | ((frame[7] & 0x80U) >> 7U);
    packet.channel6 = ((frame[10] & 0x1FU) << 6U) | ((frame[9] & 0xFCU) >> 2U);
    packet.channel7 = ((frame[11] & 0xFFU) << 3U) | ((frame[10] & 0xE0U) >> 5U);
    packet.channel8 = ((frame[13] & 0x03U) << 8U) | frame[12];
    packet.channel9 = ((frame[14] & 0x3FU) << 5U) | ((frame[13] & 0xF8U) >> 3U);
    packet.channel10 = ((frame[16] & 0x01U) << 10U) | ((frame[15] & 0xFFU) << 2U) | ((frame[14] & 0xC0U) >> 6U);
    packet.channel11 = ((frame[17] & 0x0FU) << 7U) | ((frame[16] & 0xFEU) >> 1U);
    packet.channel12 = ((frame[18] & 0x7FU) << 4U) | ((frame[17] & 0xF0U) >> 4U);
    packet.channel13 = ((frame[20] & 0x03U) << 9U) | ((frame[19] & 0xFFU) << 1U) | ((frame[18] & 0x80U) >> 7U);
    packet.channel14 = ((frame[21] & 0x1FU) << 6U) | ((frame[20] & 0xFCU) >> 2U);
    packet.channel15 = ((frame[22] & 0xFFU) << 3U) | ((frame[21] & 0xE0U) >> 5U);
}

uint16_t SBus_GetChannel(uint8_t channel) {
    return ((uint16_t *)&packet)[channel];
}
