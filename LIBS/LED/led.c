#include "led.h"
#include "bsp_conf.h"
#include "stm8l10x_gpio.h"

void led_set_mask_status(uint8_t bit_mask)
{  
  GPIO_Write(GPIO_LED, (LED_0 | LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6) & bit_mask);
}

void led_toggle_mask_status(void)
{  
  GPIO_ToggleBits(GPIO_LED, (LED_0 | LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6));
}
