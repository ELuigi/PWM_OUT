#include "stm32f1xx_hal.h"


void Init_PWM(TIM_HandleTypeDef *htimx);
void SystemClock_Config(void);
//void HAL_TIM_PWM_MspInit(void);

int main(void)
{
  TIM_HandleTypeDef htim2;

HAL_Init();
SystemClock_Config();
__GPIOA_CLK_ENABLE();
HAL_TIM_PWM_MspInit(&htim2);
Init_PWM(&htim2);
HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
__HAL_TIM_SET_AUTORELOAD(&htim2,500);


uint16_t duty_cycle =HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_1);

  while(1)
  {
    while(duty_cycle < 500)
    {
      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,++duty_cycle);
      HAL_Delay(1);
    }
    while(duty_cycle > 0)
    {
      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,--duty_cycle);
      HAL_Delay(1);
    }
  }
}

void Init_PWM(TIM_HandleTypeDef *htimx)
{

  //TIM3_CHANEL 1 --> PA6
  TIM_OC_InitTypeDef sConfigOC;

  htimx->Instance = TIM3;
  htimx->Init.Prescaler = 499;
  htimx->Init.CounterMode = TIM_COUNTERMODE_UP;
  htimx->Init.Period = 999;
  htimx->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(htimx);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 499;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(htimx,&sConfigOC,TIM_CHANNEL_1);


}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_base) {
  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim_base->Instance==TIM3) {
    __TIM3_CLK_ENABLE();

    /**TIM3 GPIO Configuration
    PA6     ------> TIM3_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  // SysTick_IRQn interrupt configuration
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
void SysTick_Handler(void) {
  HAL_IncTick();
}
