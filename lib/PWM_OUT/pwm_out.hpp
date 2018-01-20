#ifndef __PWM_OUT_H
#define __PWM_OUT_H

#include "stm32f1xx_hal.h"
#include "TARGET.hpp"
class PWM_OUT
{

private:
    TIM_HandleTypeDef* htim;
    PWM_OUT_PIN outputpin;
public:

PWM_OUT(PWM_OUT_PIN Pinout);
void SetFrequency(uint16_t Freq);
void SetDutyCycle(float duty_cycle);
};
#endif
