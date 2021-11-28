#include "stm8l10x_it.h"
    
#include "bsp_conf.h"
#include "led.h"
#include "random.h"
#include "timer.h"
#include "structs.h"

/* VARIABLES SECTION */

static const uint16_t tim_slots_delta = TIM_SLOTS_DELTA;
static const uint16_t tim_slots = TIM_SLOTS;
    
extern uint32_t delay_time_keeper;

volatile uint32_t sequences_glb_counter = 0;
volatile uint32_t sequences_done = 0;
volatile uint16_t num_slots_on = 0;

volatile LED_Manager led_man;


extern void BSP_Post_Halt_Init(uint8_t on_demand);


/* IMPLEMENTED INTERRUPT HANDLERS SECTION*/

INTERRUPT_HANDLER(EXTI7_IRQHandler, 15) // Button reset
{
  EXTI_ClearITPendingBit(EXTI_IT_Pin7);
  BSP_Post_Halt_Init(0);
}


INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_IRQHandler, 19) // 60 Hz timer
{ 
  for(uint8_t i = 0; i < NUM_LED_USED; i++)
  {
    if(led_man.descr[i].num_slots_on_array >= tim_slots)
      led_man.descr[i].direction = TO_MINIMUM;
    else if(led_man.descr[i].num_slots_on_array <= 0)
      led_man.descr[i].direction = TO_MAXIMUM;
        
    uint8_t tmp_factor = (tim_slots_delta * led_man.descr[i].speed);
    
    if(led_man.descr[i].direction == TO_MAXIMUM)
      led_man.descr[i].num_slots_on_array += tmp_factor;
    else
      led_man.descr[i].num_slots_on_array -= tmp_factor;
  }
  
  sequences_done = 0;
  sequences_glb_counter++;

  TIM2_ClearITPendingBit(TIM2_IT_Update);  
}



INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_IRQHandler, 21) // 12 kHz timer
{
  sequences_done++;
  uint8_t led_bit_msk = 0x00;
  uint8_t tmp_seq = sequences_done; //Need to define a tmp_seq due to the fact that using two volatile variables in one statement produces a WARNING
  for(uint8_t i = 0; i < NUM_LED_USED; i++)
  {
    led_bit_msk |= (tmp_seq < led_man.descr[i].num_slots_on_array) << i;
  }
  
  led_set_mask_status(led_bit_msk);
  
  TIM3_ClearITPendingBit(TIM3_IT_Update);  
}


INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 25) // 1 ms time-base interrupt handler
{
  if(delay_time_keeper != 0)
    delay_time_keeper--;
  else
   TIM4_Cmd(DISABLE);

  TIM4_ClearITPendingBit(TIM4_IT_Update);
}


/* UNUSED INTERRUPT_HANDLERs*/

#ifdef _COSMIC_
INTERRUPT_HANDLER(NonHandledInterrupt,0){}
#endif
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler){}
INTERRUPT_HANDLER(FLASH_IRQHandler,1){}
INTERRUPT_HANDLER(AWU_IRQHandler,4){}
INTERRUPT_HANDLER(EXTIB_IRQHandler, 6){}
INTERRUPT_HANDLER(EXTID_IRQHandler, 7){}
INTERRUPT_HANDLER(EXTI0_IRQHandler, 8){}
INTERRUPT_HANDLER(EXTI1_IRQHandler, 9){}
INTERRUPT_HANDLER(EXTI2_IRQHandler, 10){}
INTERRUPT_HANDLER(EXTI3_IRQHandler, 11){}
INTERRUPT_HANDLER(EXTI4_IRQHandler, 12){}
INTERRUPT_HANDLER(EXTI5_IRQHandler, 13){}
INTERRUPT_HANDLER(EXTI6_IRQHandler, 14){}
INTERRUPT_HANDLER(COMP_IRQHandler, 18){}
INTERRUPT_HANDLER(TIM3_CAP_IRQHandler, 22){}
INTERRUPT_HANDLER(SPI_IRQHandler, 26){}
INTERRUPT_HANDLER(USART_TX_IRQHandler, 27){}
INTERRUPT_HANDLER(USART_RX_IRQHandler, 28){}
INTERRUPT_HANDLER(I2C_IRQHandler, 29){}
