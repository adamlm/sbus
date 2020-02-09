//
// Created by adam on 2/6/20.
//

#ifndef SBUS_SBUS_H
#define SBUS_SBUS_H

#include <stdint.h>

#define SBUS_FRAME_SIZE 25U
#define SBUS_START_BYTE 0x0FU
#define SBUS_END_BYTE 0x00U

#define SBUS_FRAME_READY 1U
#define SBUS_FRAME_NOT_READY 0U

#define SBUS_CHANNEL_COUNT 16U

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint16_t channel0;
    uint16_t channel1;
    uint16_t channel2;
    uint16_t channel3;
    uint16_t channel4;
    uint16_t channel5;
    uint16_t channel6;
    uint16_t channel7;
    uint16_t channel8;
    uint16_t channel9;
    uint16_t channel10;
    uint16_t channel11;
    uint16_t channel12;
    uint16_t channel13;
    uint16_t channel14;
    uint16_t channel15;
} SBusPacketTypeDef;

uint8_t SBus_ParseByte(uint8_t byte);
void SBus_DecodeFrame(void);
uint16_t SBus_GetChannel(uint8_t channel);

#ifdef __cplusplus
};
#endif

#endif //SBUS_SBUS_H
