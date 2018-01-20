//list of pin and associated timer and chanel
#ifndef __TARGET_H
#define __TARGET_H

#include "stm32f1xx_hal.h"

//create structur to contains all information needed to create pwm output
struct Pwmout
{
  uint16_t GPIO_PPIN;
  TIM_TypeDef* TIMER;
  uint32_t CHANNEL;  
};

#endif
