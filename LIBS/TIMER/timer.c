#include "stm8l10x_conf.h"
#include "timer.h"
     

volatile uint32_t delay_time_keeper = 0;

//Genera interrupt con f_tim2 = 60 Hz
void TIM2_Config(void)
{
  uint32_t f_cpu = CLK_GetClockFreq() / 32;
  uint16_t ARR = f_cpu / F_TIM_2;  

  /* Enable TIM2 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
  
  TIM2_DeInit();
    
  /* Time base configuration */
  TIM2_TimeBaseInit(TIM2_Prescaler_32, TIM2_CounterMode_Up, ARR);
  
  TIM2_ITConfig(TIM2_IT_Update, ENABLE);
  
  TIM2_Cmd(ENABLE);
}


//Genera interrupt con f_tim_3 = 10 kHz
void TIM3_Config(void)
{
  uint32_t f_cpu = CLK_GetClockFreq();
  uint16_t ARR = f_cpu / F_TIM_3;
    
  /* Enable TIM2 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);
  
  TIM3_DeInit();
    
  /* Time base configuration */
  TIM3_TimeBaseInit(TIM3_Prescaler_1, TIM3_CounterMode_Up, ARR);
  
  TIM3_ITConfig(TIM3_IT_Update, ENABLE);
  
  TIM3_Cmd(ENABLE);
}


void TIM4_Config(void) // 1 ms timebase
{
   uint32_t f_cpu = CLK_GetClockFreq() / 128;
   uint16_t ARR = f_cpu / F_TIM_4;

/* Enable TIM4 CLK */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
  
  TIM4_DeInit();
  
  /* Time base configuration */ 
  TIM4_TimeBaseInit(TIM4_Prescaler_128, ARR);
  
  
  TIM4_ITConfig(TIM4_IT_Update, ENABLE);
}


void delay(uint32_t ms)
{
  delay_time_keeper = ms;
  
  TIM4_SetCounter(TIM4_CNTR_RESET_VALUE);
  
  TIM4_Cmd(ENABLE);
  
  while(delay_time_keeper);
}


