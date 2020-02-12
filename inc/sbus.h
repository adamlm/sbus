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

/**
 * @file sbus.h
 * @author Adam Morrissett
 * @brief File contains SBus parameters and parsing functions.
 *
 * @details Contains macros for SBus frame size, start and end bytes. Also
 * contains functions for building and decoding the frame and the SBus packet.
 */

#ifndef SBUS_SBUS_H
#define SBUS_SBUS_H

#include <stdint.h>

#define SBUS_FRAME_SIZE 25U  //!< Size of SBus frame in bytes
#define SBUS_START_BYTE 0x0FU  //!< Start byte for SBus frame
#define SBUS_END_BYTE 0x00U  //!< End byte for SBus frame

#define SBUS_FRAME_READY 1U  //!< SBus frame is built and ready for decoding
#define SBUS_FRAME_NOT_READY 0U  //!< SBus frame not yet built

#define SBUS_CHANNEL_COUNT 16U  //!< Number of analog channels in SBus frame

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint16_t channel0;  //!< Analog channel 0
    uint16_t channel1;  //!< Analog channel 1
    uint16_t channel2;  //!< Analog channel 2
    uint16_t channel3;  //!< Analog channel 3
    uint16_t channel4;  //!< Analog channel 4
    uint16_t channel5;  //!< Analog channel 5
    uint16_t channel6;  //!< Analog channel 6
    uint16_t channel7;  //!< Analog channel 7
    uint16_t channel8;  //!< Analog channel 8
    uint16_t channel9;  //!< Analog channel 9
    uint16_t channel10;  //!< Analog channel 10
    uint16_t channel11;  //!< Analog channel 11
    uint16_t channel12;  //!< Analog channel 12
    uint16_t channel13;  //!< Analog channel 13
    uint16_t channel14;  //!< Analog channel 14
    uint16_t channel15;  //!< Analog channel 15
} SBusPacketTypeDef;  //!< Structure containing all analog channel values

/** Parses currently read byte into frame.
 *
 * Adds the passed byte into the SBus frame. If after the byte the frame is
 * built, function returns SBUS_FRAME_READY. Otherwise, function returns
 * SBUS_FRAME_NOT_READY.
 *
 * @param byte currently byte in the read sequence
 * @return if the SBus frame is ready to be decoded
 */
uint8_t SBus_ParseByte(uint8_t byte);

/** Decodes the SBus frame into an SBus packet.
 *
 */
void SBus_DecodeFrame(void);

/** Returns the current value of the specified analog SBus channel.
 *
 * @param channel channel number
 * @return value of channel
 */
uint16_t SBus_GetChannel(uint8_t channel);

#ifdef __cplusplus
};
#endif

#endif //SBUS_SBUS_H
