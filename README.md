# Microcontroller-Based LED and Sounder Control System

## Project Overview
This project demonstrates the design and implementation of a microcontroller-based system using an ATmega328P. The system includes:
- Smooth LED brightness control via PWM.
- Adjustable sounder frequency using a potentiometer and UART commands.
- Interaction with a Virtual Terminal for feedback and control.
- Low-power mode to conserve energy when the system is inactive.

The project is fully modular, making it maintainable, scalable, and reusable for similar applications.

---

## Features
1. **LED Brightness Control**:
   - Smooth transitions in brightness using Timer2 in Fast PWM mode.
2. **Sounder Frequency Control**:
   - Frequency adjustments using:
     - **Potentiometer**: Dynamically scaled to the range 50–1000 Hz.
     - **Virtual Terminal Commands**:
       - `+`: Increase frequency by 10 Hz.
       - `-`: Decrease frequency by 10 Hz.
       - Numeric Input (e.g., `440`): Set the frequency directly.
3. **Low-Power Mode**:
   - System transitions to power-down mode when the switch is toggled off.
   - Resumes normal operation when the switch is toggled back on.
4. **Virtual Terminal Feedback**:
   - Displays the current frequency and system state in real-time.

---

## Circuit Components
1. **Microcontroller**: ATmega328P
2. **LED**: Connected to `PD3/OC2B`
3. **Sounder**: Connected to `PB1/OC1A`
4. **Potentiometer**: Provides analog input to ADC0
5. **On/Off Switch**: Connected to `PD2/INT0`
6. **Virtual Terminal**: UART connection via `PD0 (RXD)` and `PD1 (TXD)`

---

## Circuit Diagram
![Circuit Diagram] Circuit_Schematic.png

---

## PCB Layout
![PCB Layout]

---

## Software Structure

The program is divided into the following modules:

1. **`main.c`**:
   - Manages the overall control flow and interaction between modules.
2. **`led.c` and `led.h`**:
   - Handles LED brightness using PWM on Timer2.
3. **`sounder.c` and `sounder.h`**:
   - Controls the sounder frequency using Timer1 in CTC mode.
4. **`adc.c` and `adc.h`**:
   - Reads potentiometer input and scales it to the required frequency range.
5. **`switch.c` and `switch.h`**:
   - Manages the on/off switch and transitions to low-power mode.
6. **`usart.c` and `usart.h`**:
   - Handles UART communication with the Virtual Terminal.

---

## Installation and Usage

### Requirements
- **Hardware**:
  - ATmega328P microcontroller
  - Potentiometer, Sounder, LED, On/Off Switch
  - Virtual Terminal (via UART connection)
- **Software**:
  - [Atmel Studio 7](https://www.microchip.com/mplab/avr-support/atmel-studio-7) or any AVR-compatible toolchain
  - [Proteus Simulation Software](https://www.labcenter.com/)

### Setup
1. Clone this repository:
   ```bash
    git clone https://github.com/ryantra/avr_atmega328.git
