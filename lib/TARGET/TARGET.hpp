//list of pin and associated timer and chanel
#ifndef __TARGET_H
#define __TARGET_H

#include "stm32f1xx_hal.h"

//create structur to contains all information needed to create pwm output
typedef struct PWM_OUT_PIN PWM_OUT_PIN;
struct PWM_OUT_PIN
{
  uint16_t GPIO_PPIN;
  TIM_TypeDef* TIMER;
  uint32_t CHANNEL;  
};

//liste of available pwm output

//creation of all structs
PWM_OUT_PIN pinout1 = {GPIO_PIN_6,TIM3,TIM_CHANNEL_1};
PWM_OUT_PIN pinout2;
PWM_OUT_PIN pinout3;
PWM_OUT_PIN pinout4;



#endif
