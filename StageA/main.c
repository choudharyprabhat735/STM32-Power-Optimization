/* Stage A - Run Mode Baseline
 * Current Measured: 23.4mA
 * Clock: 16MHz HSI
 * LED: Blinking 500ms
 */

/* USER CODE BEGIN WHILE */

HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
HAL_Delay(500);

/* USER CODE END WHILE */
```

---
