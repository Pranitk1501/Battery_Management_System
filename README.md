# Battery Management System

![License](https://img.shields.io/badge/license-MIT-green.svg)

A Battery Management System (BMS) for a 24-volt Li-Po battery, implemented using an Arduino-compatible microcontroller. This BMS monitors battery voltage, current, temperature, and controls an electric motor based on defined thresholds.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
- [Usage](#usage)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The Battery Management System (BMS) presented here is designed for a 24-volt Li-Po battery application. It is built using an Arduino-compatible microcontroller and provides essential battery monitoring and control functions. The system monitors battery voltage, current, and temperature, and it can control an electric motor based on predefined thresholds for these parameters.

## Features

- Real-time monitoring of battery voltage, current, and temperature.
- Adjustable motor speed control using a potentiometer.
- Automatic motor shutdown based on user-defined voltage, current, and temperature thresholds.
- Supports easy configuration and customization for different battery systems.

## Getting Started

### Prerequisites

To run this Battery Management System, you will need:

- An Arduino-compatible microcontroller board (e.g., Arduino UNO).
- Necessary sensors and components (voltage, current, temperature sensors).
- A motor driver for controlling the electric motor.
- Arduino IDE installed on your computer.
- Basic knowledge of Arduino programming.

## Usage

1. Connect the necessary sensors and components to your microcontroller as per your hardware setup.

2. Configure the threshold values for voltage, current, and temperature in the code to match your specific battery system requirements.

3. Upload the modified code to your microcontroller.

4. Monitor the system through the serial monitor in the Arduino IDE to observe battery parameters and motor speed.

5. The motor will automatically stop if any of the monitored parameters exceed the defined thresholds.

## Configuration

You can customize the system by adjusting the following parameters in the code:

- `volt_threshold`: Voltage threshold for motor shutdown.
- `curr_threshold`: Current threshold for motor shutdown.
- `temp_threshold`: Temperature threshold for motor shutdown.


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
