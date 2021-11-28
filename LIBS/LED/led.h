#ifndef __LED_H__
#define __LED_H__

#include "stm8l10x.h"

void led_set_mask_status(uint8_t bit_mask);

void led_toggle_mask_status(void);

#endif // __LED_H__