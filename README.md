# Hybrid-Hardware-Software-Waveform-System.
Wi-Fi enabled embedded waveform visualization system using Arduino, ESP8266, NE555 and 74LS90.
## Features

- Wi-Fi webpage control
- Touch sensor interface
- Multiple waveform modes
- 74LS90 synchronized counting
- Real-time speed control
- 10 LED waveform visualization
- UART communication between Arduino and ESP8266

## System Architecture

NE555 Timer  
↓  
74LS90 Counter  
↓  
Arduino Uno (Waveform Engine)  
↓  
10 LED Display  

ESP8266 NodeMCU (Web + Touch Control)  
↓  
UART Communication  
↓  
Arduino Uno  

## Components Used

- Arduino Uno
- ESP8266 NodeMCU
- NE555 Timer IC
- 74LS90 Counter IC
- 10 LEDs
- TTP223 Touch Sensors
- Resistors
- Breadboard

## Waveform Modes

- Staircase
- Running
- Binary
- Triangle
- Ping Pong
- Random

## Touch Sensor Functions

| Touch Sensor | Function |
|---|---|
| T1 | Change Modes |
| T2 | Increase Speed |
| T3 | Decrease Speed |
| T4 | Stop Waveform |

## Technologies Used

- Embedded Systems
- Digital Electronics
- IoT Communication
- UART Serial Communication
- Hardware-Software Synchronization

## Future Improvements

- LCD integration
- Interrupt-based firmware
- PCB implementation
