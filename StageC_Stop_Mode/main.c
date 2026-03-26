/* =========================================
 * Stage C - Stop Mode
 * Board: STM32 Nucleo F446RE
 * Current Measured: <500uA
 * Improvement: 46x+ better than Run Mode
 * What's OFF: CPU + All Clocks
 * RAM: Data retained
 * ========================================= */

#include "main.h"

void Configure_GPIO_Analog(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    /* LED ON briefly - board alive confirm */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    /* Configure all GPIO to Analog
     * This eliminates GPIO leakage current
     * Most engineers miss this step!
     */
    Configure_GPIO_Analog();

    /* Enter Stop Mode
     * CPU + all clocks disabled
     * Low power regulator ON
     * RAM data retained
     * Wakeup: external interrupt or RTC
     */
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,
                           PWR_STOPENTRY_WFI);

    /* Should never reach here */
    while(1);
}

void Configure_GPIO_Analog(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Enable clocks */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /* Set all pins to Analog — stops leakage */
    GPIO_InitStruct.Pin  = GPIO_PIN_All;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
```

---
