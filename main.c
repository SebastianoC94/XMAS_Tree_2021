#include "stm8l10x_it.h"
#include "stm8l10x_conf.h"

#include "bsp_conf.h"
#include "led.h"
#include "timer.h"
#include "random.h"
#include "test.h"
#include "structs.h"

#define MAX_NUM_SEQ_GLB_CNT             (2000U)

extern volatile uint32_t sequences_glb_counter;

extern volatile LED_Manager led_man;

static void led_manager_init()
{
  for(uint8_t i= 0; i < NUM_LED_USED; i++)
    {
      led_man.descr[i].num_slots_on_array = random_number(0,TIM_SLOTS);
      led_man.descr[i].direction = (DIRECTION)random_number(TO_MINIMUM,TO_MAXIMUM);
      led_man.descr[i].speed = (LED_CHANGE_SPEED)random_number(NORMAL_SPEED,TRIPLE_SPEED);
    }
}

static void BSP_GPIO_Init()
{  
  /* TIMERS */
  GPIO_Init(GPIOB, GPIO_Pin_0 | GPIO_Pin_2, GPIO_Mode_Out_PP_High_Fast);
    
  /* LED */
  GPIO_Init(GPIO_LED, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6, GPIO_Mode_Out_PP_High_Fast);
  led_set_mask_status(0x00);
  
  /* BUTTON */
  GPIO_Init(GPIO_BUTTON, PIN_BUTTON, GPIO_Mode_In_PU_IT);
  EXTI_SetPinSensitivity(EXTI_Pin_7, EXTI_Trigger_Rising_Falling);
  
}

static void BSP_GPIO_Deinit()
{  
  /* LED */
  led_set_mask_status(0x00);
}


static void BSP_Halt_Init()
{
  BSP_GPIO_Deinit();
  
  TIM2_DeInit();
  
  TIM3_DeInit();
  
  TIM4_DeInit();
    
  halt();
}


void BSP_Post_Halt_Init(uint8_t on_demand)
{
  if(sequences_glb_counter == MAX_NUM_SEQ_GLB_CNT || on_demand)
  {
    InitSeed();
    
    led_manager_init();
      
    CLK_MasterPrescalerConfig(CLK_MasterPrescaler_HSIDiv1);
  
    BSP_GPIO_Init(); 
    
    TIM2_Config();
    
    TIM3_Config();
    
    TIM4_Config();
    
    enableInterrupts();
  }
  
  sequences_glb_counter = 0;

}

int main( void )
{       
  BSP_Post_Halt_Init(1);
   
  while(1)
  {
    wfi();
    
    if(sequences_glb_counter == MAX_NUM_SEQ_GLB_CNT)
    {
      BSP_Halt_Init();
    }
  }

}
