#include "pwm_out.hpp"


PWM_OUT::PWM_OUT(PWM_OUT_PIN Pinout,TIM_HandleTypeDef* htim2){
    outputpin = Pinout;
    htim=htim2;
    TIM_OC_InitTypeDef sConfigOC;
    GPIO_InitTypeDef GPIO_InitStruct;
    htim->
    htim->Instance = outputpin.TIMER;
    htim->Init.Prescaler = 499;
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim->Init.Period = 999;
    htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_PWM_Init(htim);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 499;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(htim,&sConfigOC,outputpin.CHANNEL);

    if(htim->Instance==TIM3) {
        __TIM3_CLK_ENABLE();

        /**TIM3 GPIO Configuration
        PA6     ------> TIM3_CH1
        */
        GPIO_InitStruct.Pin = outputpin.GPIO_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        HAL_GPIO_Init(outputpin.GPIO, &GPIO_InitStruct);
    }
    HAL_TIM_PWM_Start(htim,outputpin.CHANNEL);
    __HAL_TIM_SET_AUTORELOAD(htim,500);
}

void PWM_OUT::SetDutyCycle(uint16_t duty_cycle)
{
     __HAL_TIM_SET_COMPARE(htim,outputpin.CHANNEL,duty_cycle);
}
