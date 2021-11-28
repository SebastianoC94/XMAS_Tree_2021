#ifndef __XMAS_TREE_BSP_CONF__
#define __XMAS_TREE_BSP_CONF__

#define NUM_LED_USED            7

/* LED */
#define GPIO_LED                GPIOB

#define LED_0                   1 << 0
#define LED_1                   1 << 1
#define LED_2                   1 << 2
#define LED_3                   1 << 3
#define LED_4                   1 << 4
#define LED_5                   1 << 5
#define LED_6                   1 << 6
                              
/* USER BUTTON */
#define GPIO_BUTTON             GPIOB
#define PIN_BUTTON              GPIO_Pin_7          

#endif // __XMAS_TREE_BSP_CONF__