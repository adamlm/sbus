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

#include "gtest/gtest.h"
#include "../inc/sbus.h"

namespace {
    const uint8_t frame[SBUS_FRAME_SIZE] = {SBUS_START_BYTE, 0x80, 0x08, 0x84,
                                            0x20, 0x06, 0x41, 0x88, 0x42, 0x18,
                                            0xE2, 0x10, 0x88, 0x48, 0x84, 0x22,
                                            0x16, 0xC1, 0x88, 0x46, 0x38, 0xE2,
                                            0x11, 0x00, SBUS_END_BYTE};

    const SBusPacketTypeDef packet = {
        .channel0 = 128,
        .channel1 = 129,
        .channel2 = 130,
        .channel3 = 131,
        .channel4 = 132,
        .channel5 = 133,
        .channel6 = 134,
        .channel7 = 135,
        .channel8 = 136,
        .channel9 = 137,
        .channel10 = 138,
        .channel11 = 139,
        .channel12 = 140,
        .channel13 = 141,
        .channel14 = 142,
        .channel15 = 143
    };

    TEST(SBusTest, FrameBuild) {
        int i = 0;
        for (; i < SBUS_FRAME_SIZE - 1; i++) {
            EXPECT_TRUE(SBus_ParseByte(frame[i]) == SBUS_FRAME_NOT_READY);
        }
        EXPECT_TRUE(SBus_ParseByte(frame[i]) == SBUS_FRAME_READY);
    }

    TEST(SBusTest, FrameDecode) {
        SBus_DecodeFrame();

        for (int i = 0; i < SBUS_CHANNEL_COUNT; i++) {
            EXPECT_TRUE(SBus_GetChannel(i) == ((uint16_t *)&packet)[i]);
        }
    }
}
