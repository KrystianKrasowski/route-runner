# Route Runner

Route runner is a name of the line following robot project. It is built using the following components:
* STM32 NUCLEO-F303 board as a microcontroller
* 2 DC motors driven by simple L293D component
* Pololu's QTR-HD-06A line sensor
* Dualshock2 remote control
* 1 status indicator LED
* Two LM2596 step-down voltage converters with the following settings:
    * 6V for the motors
    * 5V for the MCU and L293D logic

For the power details visit the [Power supply](#power-supply) section

## Usage
* Turn on the device using ON/OFF switch. State indicator displays MANUAL CONTROL state.
* Place the vehicle on the black line so that it aligns with its vertical axis. State indicator displays LINE DETECTED state. 
* Start line following by issuing START FOLLOWING command. State indicator displays LINE FOLLOWING state.

### Command reference
* MANUAL CONTROL - control vehicle freely with remote control
* START FOLLOWING - vehicle follows the line with PID control

### Command - dualshock2 remote mapping
* MANUAL CONTROL - CIRCLE
* START FOLLOWING - CROSS

### State reference
* MANUAL CONTROL
* LINE DETECTED
* LINE FOLLOWING

### State - LED indicator mapping
* MANUAL CONTROL - single short blink per second
* LINE DETECTED - LED constant on
* LINE FOLLOWING - 4 short blinks per second
* ERROR - single long blink per second

short blink is a sequence `on -> off` with 250ms duration
long blink is a sequence `on -> off` with 1s duration

## Technical info
* The line sensor is positioned at 4mm above the surface and the calibration is hardcoded.


### Power supply
The device is powered by two 18650 Li-ion 2500mAh 20A baterries of total voltage equal to 7.4V (3.7V each). The power buses are distributed as follows:
* 6V power bus provided by one of the LM2596 voltage converter. Used by L293D for DC motor inputs.
* 5V power bus provided by the second LM2596 voltage converter. Used by L293D logic and the MCU
* 3.3V power bus provided by MCU. Used by the Dualshock2 receiver and state indicator
* 3.3V analog power bus provided by MCU. Used by line sensor
* Common GND bus for all components

### Pin usage summary
* Motion:
    * **PB0** (D3) - PWM (tim3, ch3) for left motor
    * PB6 (D5) - A1 for right motor
    * PB7 (D4) - A2 for right motor
    * **PB1** (D6) - PWM (tim3, ch4) for right motor
    * PA10 (D0) - A2 for left motor
    * PA12 (D2) - A1 for left motor
* Remote control:
    * **PB5** (D11) - MOSI
    * **PB4** (D12) - MISO
    * **PB3** (D13) - SCK
    * PF0 (D7) - CS
* Line sensing:
    * *PA1* (A1) - channel 1
    * *PA3* (A2) - channel 2
    * *PA4* (A3) - channel 3
    * *PA5* (A4) - channel 4
    * *PA6* (A5) - channel 5
    * *PA7* (A6) - channel 6
* Status indicator
    * **PA8** (D9)

### Peripherals usage summary
* TIM2 channel 1 - timer for (dualshock2) MANUAL CONTROL communication trigger
* TIM3 channel 4 - timer for PWM signal for left motor (PB1)
* TIM3 channel 3 - timer for PWM signal for right motor (PB0)
* TIM1 channel 1 - timer for (LED) status indicator (by toggle on compare)
* TIM6 - timer trigger for ADC conversion by TRGO, every 1ms
* TIM15 - off route guard

Pins in **bold** are unchangeable. *Italic* pin change may implicate other changes.

### Electrical wiring diagram
![schematic](./doc/img/schematic.png)

## Development

```bash
# build

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi-gcc.cmake -B build/Debug
cmake --build build/Debug

# flash
st-flash write build/Debug/app/route-runner.bin 0x08000000


```