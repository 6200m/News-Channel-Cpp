//
// Created by void on 8/19/18.
//

#include "Types.h"

// signed bits
int8_t s8(int8_t x) {
	return x;
};
int16_t s16(int16_t x) {
	return htobe16(x);
};
int32_t s32(int32_t x) {
	return htobe32(x);
};
// unsigned bits
uint8_t u8(uint8_t x) {
	return x;
};
uint16_t u16(uint16_t x) {
	return htobe16(x);
};
uint32_t u32(uint32_t x) {
	return htobe32(x);
};
// little endian
uint32_t u32_le(uint32_t x) {
	return htole32(x);
};
