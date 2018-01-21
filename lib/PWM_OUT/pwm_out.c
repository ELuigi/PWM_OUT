#include "pwm_out.h"


void PWMOut_Init(PWM_OUT_PIN Pinout,TIM_HandleTypeDef* htim){
    TIM_OC_InitTypeDef sConfigOC;
    GPIO_InitTypeDef GPIO_InitStruct;
    htim->Instance = Pinout.TIMER;
    htim->Init.Prescaler = 499;
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim->Init.Period = 999;
    htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_PWM_Init(htim);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 499;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(htim,&sConfigOC,Pinout.CHANNEL);

    if(htim->Instance==TIM3) {
        __TIM3_CLK_ENABLE();

        /**TIM3 GPIO Configuration
        PA6     ------> TIM3_CH1
        */
        GPIO_InitStruct.Pin = Pinout.GPIO_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        HAL_GPIO_Init(Pinout.GPIO, &GPIO_InitStruct);
    }
    HAL_TIM_PWM_Start(htim,Pinout.CHANNEL);
    __HAL_TIM_SET_AUTORELOAD(htim,500);
}

void SetDutyCycle(PWM_OUT_PIN Pinout,TIM_HandleTypeDef* htim,uint16_t duty_cycle)
{
     __HAL_TIM_SET_COMPARE(htim,Pinout.CHANNEL,duty_cycle);
}
