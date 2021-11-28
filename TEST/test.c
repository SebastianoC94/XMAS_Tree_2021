#include "test.h"

#include "bsp_conf.h"
#include "led.h"
#include "timer.h"
#include "random.h"

void led_test(void)
{
  led_set_mask_status(0x00);
  
  led_set_mask_status(LED_0);
  led_toggle_mask_status();
  led_set_mask_status(LED_0);

  led_set_mask_status(LED_1);
  led_toggle_mask_status();
  led_set_mask_status(LED_1);

  led_set_mask_status(LED_2);
  led_toggle_mask_status();
  led_set_mask_status(LED_2);

  led_set_mask_status(LED_3);
  led_toggle_mask_status();
  led_set_mask_status(LED_3);

  led_set_mask_status(LED_4);
  led_toggle_mask_status();
  led_set_mask_status(LED_4);

  led_set_mask_status(LED_5);
  led_toggle_mask_status();
  led_set_mask_status(LED_5);

  led_set_mask_status(LED_6);
  led_toggle_mask_status();
  led_set_mask_status(LED_6);

  led_set_mask_status(0x00);
}

void delay_test(void)
{
  uint8_t cnt = 255;
  
  while(cnt-- > 0)
  {
    delay(1);
    GPIO_ToggleBits(GPIO_LED, LED_0);
  }
  
  return;
}
