/* =========================================
 * Stage B - Sleep Mode
 * Board: STM32 Nucleo F446RE
 * Current Measured: 13mA
 * Improvement: 1.8x better than Run Mode
 * What's OFF: CPU only
 * Clock: 16MHz HSI
 * ========================================= */

#include "main.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while(1)
    {
        /* Toggle LED before sleeping */
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(500);

        /* Enter Sleep Mode
         * CPU halts — peripherals stay active
         * Wakes up on any interrupt (SysTick)
         */
        HAL_PWR_EnableSleepOnExit();
        HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,
                                PWR_SLEEPENTRY_WFI);
    }
}
```

---
