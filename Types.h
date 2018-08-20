//
// Created by void on 8/18/18.
//

#ifndef FILE_MAKER_TYPES_H
#define FILE_MAKER_TYPES_H

#include <cstdint>
#include <endian.h>

// Convert to correct types for the Wii's architecture

// signed bits
int8_t s8(int8_t);
int16_t s16(int16_t);
int32_t s32(int32_t);
// unsigned bits
uint8_t u8(uint8_t);
uint16_t u16(uint16_t);
uint32_t u32(uint32_t);

uint32_t u32_le(uint32_t);

#endif //FILE_MAKER_TYPES_H
