# STM32 Power Optimization 🔋

> Reducing STM32F446RE power consumption by 46x
> through low-power sleep modes and GPIO optimization.

---

## 🎯 Project Goal

Power consumption is a critical factor in battery-powered
embedded systems. This project measures and optimizes the
current consumption of the STM32F446RE microcontroller —
from active run mode down to Stop mode.

Real world applications: IoT sensors, GPS trackers,
medical patches, and wireless nodes where battery life
must last months or even years.

---

## 🛠️ Hardware Used

| Component   | Details                          |
|-------------|----------------------------------|
| MCU Board   | STM32 Nucleo F446RE              |
| Processor   | STM32F446RE (Cortex-M4, 180MHz)  |
| Multimeter  | Haoyue DT830D Digital Multimeter |
| Interface   | USB via ST-Link v2               |

---

## 📊 Results

| Mode  | Current | Improvement  | What is OFF      |
|-------|---------|--------------|------------------|
| Run   | 23.4mA  | Baseline     | Nothing          |
| Sleep | 13mA    | 1.8x better  | CPU only         |
| Stop  | <500µA  | 46x+ better  | CPU + All Clocks |

### 📉 Visual Comparison
```
Run Mode   ████████████████████  23.4mA
Sleep Mode ███████████           13mA  
Stop Mode  ░                     <500µA
```

---

## 💡 Key Technical Findings

### 1. GPIO Leakage Current
Floating GPIO pins continuously leak current.
Setting all unused pins to ANALOG mode completely
eliminates this leakage.
```c
GPIO_InitStruct.Pin  = GPIO_PIN_All;
GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
```

### 2. Sleep Mode
Only the CPU is halted — peripherals stay active.
Fast wakeup response. Measured: 13mA
```c
HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,
                        PWR_SLEEPENTRY_WFI);
```

### 3. Stop Mode
CPU and all clocks are disabled. RAM data is retained.
Maximum power saving achieved. Measured: <500µA
```c
HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,
                       PWR_STOPENTRY_WFI);
```

---

## 🔬 Measurement Setup
```
[USB Power]
     |
[ST-Link] -- JP5 jumper REMOVED (ST-Link isolated)
     |
[IDD Pins] -- Multimeter connected in SERIES here
     |
[STM32F446RE MCU]
```

---

## 📁 Branch Structure
```
main              ← Stage A: Run Mode (23.4mA)
feature/sleep-mode ← Stage B: Sleep Mode (13mA)
feature/stop-mode  ← Stage C: Stop Mode (<500µA)
```

---

## 🚀 How to Run

1. Clone this repository
2. Open in STM32CubeIDE
3. Build project — Ctrl + B
4. Remove JP5 jumper on Nucleo board
5. Connect multimeter in series at IDD pins
6. Flash firmware and measure current at each mode

---

## 🎓 What I Learned

- Real hardware measurements differ from theoretical values
- GPIO configuration directly impacts power consumption
- Each power mode has different power vs wakeup time tradeoff
- Always profile first, then optimize

---

*Board: STM32 Nucleo F446RE | IDE: STM32CubeIDE | HAL: STM32F4xx HAL Driver*
