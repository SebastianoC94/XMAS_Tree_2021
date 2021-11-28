/**
  ******************************************************************************
  * @file    stm8l10x_it.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    30-September-2014
  * @brief   This file contains all the interrupt routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "stm8l10x_it.h"
    
#include "bsp_conf.h"
#include "led.h"
#include "random.h"
#include "timer.h"

static const uint16_t tim_slots_delta = TIM_SLOTS_DELTA;
static const uint16_t tim_slots = TIM_SLOTS;
    


    
extern uint32_t delay_time_keeper;

volatile uint32_t sequences_glb_counter = 0;
volatile uint32_t sequences_done = 0;
volatile uint16_t num_slots_on = 0;

volatile uint8_t num_slots_on_array[8];
volatile DIRECTION direction[8];
volatile LED_CHANGE_SPEED speed[8];

extern void BSP_Post_Halt_Init(uint8_t on_demand);

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

INTERRUPT_HANDLER(EXTI7_IRQHandler, 15){ // Reset button
  EXTI_ClearITPendingBit(EXTI_IT_Pin7);
  
  BSP_Post_Halt_Init(0);
 
}


#if 0

INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_IRQHandler, 19) //TIMER LENTO -> TIM 2 
{
  if(num_slots_on < TIM_SLOTS)
    num_slots_on += TIM_SLOTS_DELTA;
  else
    num_slots_on = 0;
  
  sequences_done = 0;
  
  TIM2_ClearITPendingBit(TIM2_IT_Update);  
}

INTERRUPT_HANDLER(TIM2_CAP_IRQHandler, 20){}



INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_IRQHandler, 21) //TIMER VELOCE -> TIM 3
{
  sequences_done++;

  if(sequences_done < num_slots_on)
  {
    led_set_mask_status(0xFF);
  }
  else
  {
    led_set_mask_status(0x00);
  }
    
  TIM3_ClearITPendingBit(TIM3_IT_Update);  
}

#endif

DIRECTION calc_direction(uint8_t curr_val, DIRECTION curr_dir)
{
  if(curr_val >= tim_slots)
    return TO_MINIMUM;
  else if(curr_val <= 0)
    return TO_MAXIMUM;
  else
    return curr_dir;         
}


INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_IRQHandler, 19) //TIMER LENTO -> TIM 2 
{ 
  for(uint8_t i = 0; i < 8; i++)
  {
    if(num_slots_on_array[i] >= tim_slots)
      direction[i] = TO_MINIMUM;
    else if(num_slots_on_array[i] <= 0)
      direction[i] = TO_MAXIMUM;
        
    uint8_t tmp_num = (tim_slots_delta * speed[i]);
    
    if(direction[i] == TO_MAXIMUM)
    {
      num_slots_on_array[i] += tmp_num;
    }
    else
    {
      num_slots_on_array[i] -= tmp_num;
    }
  }
  
  sequences_done = 0;
  sequences_glb_counter++;

  TIM2_ClearITPendingBit(TIM2_IT_Update);  
}



INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_IRQHandler, 21) //TIMER VELOCE -> TIM 3
{
  sequences_done++;
  uint8_t led_bit_msk = 0x00;
  uint8_t tmp_seq = sequences_done; //Need to define a tmp_seq due to the fact that using two volatile variables in one statement produces a WARNING
  for(uint8_t i = 0; i < 8; i++)
  {
    led_bit_msk |= (tmp_seq < num_slots_on_array[i]) << i;
  }
  
  led_set_mask_status(led_bit_msk);
  
  TIM3_ClearITPendingBit(TIM3_IT_Update);  
}


INTERRUPT_HANDLER(TIM3_CAP_IRQHandler, 22){}

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 25){
  
  if(delay_time_keeper != 0)
    delay_time_keeper--;
  else
   TIM4_Cmd(DISABLE);

  TIM4_ClearITPendingBit(TIM4_IT_Update);
}

INTERRUPT_HANDLER(SPI_IRQHandler, 26){}
INTERRUPT_HANDLER(USART_TX_IRQHandler, 27){}
INTERRUPT_HANDLER(USART_RX_IRQHandler, 28){}
INTERRUPT_HANDLER(I2C_IRQHandler, 29){}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

