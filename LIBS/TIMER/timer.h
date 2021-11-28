#ifndef __TIMER_H__
#define __TIMER_H__

#define F_TIM_2                 60
#define F_TIM_3                 12000
#define F_TIM_4                 1000

#define TIM_SLOTS               F_TIM_3 / F_TIM_2
#define TIM_SLOTS_DELTA         TIM_SLOTS / 100

void TIM4_Config(void);

void TIM2_Config(void);

void TIM3_Config(void);

void delay(uint32_t ms);

#endif // __TIMER_H__