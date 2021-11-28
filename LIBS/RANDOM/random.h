#ifndef __RANDOM_GENERATOR_H__
#define __RANDOM_GENERATOR_H__

#include "stm8l10x.h"

uint32_t NextVal();

void InitSeed();

uint8_t random_bit_mask(void);

uint8_t random_number(uint8_t min, uint8_t max);

#endif // __RANDOM_GENERATOR_H__