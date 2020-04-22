# touchless-temperature-meter
Touchless temperature meter with lcd build around Arduino nano, MLX90615 IR sensor and LCD1602 with PCF8574

Author: Stanislav Petrek
Country: Slovakia
Date: 20.4.2020

This is a simple device, maybe handheld with powerbank 5V for measuring ambient temperature + object temperature with MLX90615 sensor. Values are displayed on LCD1602 I2C with converter PCF8574

Used libraries:
- Digital Infrared Temperature Sensor MLX90615
- LiquidCrystal_PCF8574

Used hardware:
- Arduino Nano or any else
- IR sensor MLX90615
- LCD1602 lcd with backlight
- PCF8754 parallel to serial I2C converter
- 5V battery
- Micro USB cable
