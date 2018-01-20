#ifndef __PWM_OUT_H
#define __PWM_OUT_H

#include "stm32f1xx_hal.h"
class PWM_OUT
{

private:

public:

PWM_OUT(uint16_t Pin);
void SetFrequency(uint16_t Freq);
void SetDutyCycle(float duty_cycle);
};
#endif
