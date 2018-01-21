#include "stm32f1xx_hal.h"
#include "PWM_OUT.h"
#include "TARGET.h"


void Init_PWM(TIM_HandleTypeDef *htimx);
void SystemClock_Config(void);
//void HAL_TIM_PWM_MspInit(void);

int main(void)
{
TIM_HandleTypeDef htim2;
PWM_OUT_PIN pinout1 ={GPIO_PIN_6,GPIOA,TIM3,TIM_CHANNEL_1};

HAL_Init();
SystemClock_Config();
__GPIOA_CLK_ENABLE();
PWMOut_Init(pinout1,&htim2);

HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
__HAL_TIM_SET_AUTORELOAD(&htim2,500);


while(1)
{
SetDutyCycle(pinout1,&htim2,490);
HAL_Delay(499);
SetDutyCycle(pinout1,&htim2,200);
HAL_Delay(499);
}
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
