//
// Created by adam on 2/6/20.
//

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
