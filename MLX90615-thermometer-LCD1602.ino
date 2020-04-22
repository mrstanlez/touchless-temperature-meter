/* Author: Stanislav Petrek
 * Date: 20.4.2020
 * 
 * Project: Touchless temperature meter with LCD
 * 
 * Nano MLX90615
 * GND  GND
 * +3.3V  Vin
 * D2   SDA
 * D3   SCL
 * 
 *      LCD 1602 / PCF8754 I2C
 * GND  GND
 * +5V  +5V
 * A4   SDA
 * A5   SCL
 * 
 * COVID-19 / SARS-CoV-2:
 * 35 - 36 normal temperature
 * 36 - 38 higher temp ready for home quarantine
 * 38 - >  higher temp ready for hospital quarantine 
 * 
 * Factory calibrated in wide temperature range: -20 to 85°C for sensor temperature 
 * and -40 to 115°C for object temperature. High accuracy of 0.5°C over wide temperature 
 * range (0..+50 C for both Ta and To). Medical accuracy of 0.2°C in a limited temperature range
 * Measurement resolution of 0.02°C, SMBus compatible digital interface for fast temperature 
 * readings and building sensor networks, Customizable PWM output for continuous reading
 */

#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

LiquidCrystal_PCF8574 lcd(0x27);
int show = -1;
#include "MLX90615.h"
#include <I2cMaster.h>

#define SDA_PIN 2   //define the SDA pin
#define SCL_PIN 3   //define the SCL pin

SoftI2cMaster i2c(SDA_PIN, SCL_PIN);
MLX90615 mlx90615(DEVICE_ADDR, &i2c);


void setup()
{
  Serial.begin(9600);
  Serial.println("Setup...");

  //mlx90615.writeEEPROM(Default_Emissivity); //write data into EEPROM when you need to adjust emissivity.
  //mlx90615.readEEPROM(); //read EEPROM data to check whether it's a default one.
  
  // lcd
  int error;
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  if (error == 0) {
    Serial.println(": LCD found.");
    show = 0;
    lcd.begin(16, 2); // initialize the lcd

    lcd.setBacklight(255);
    lcd.clear();

  } else {
    Serial.println(": LCD not found.");
  } // if
}

void loop()
{
  Serial.print("Ambient temp: ");
  Serial.print(mlx90615.getTemperature(MLX90615_AMBIENT_TEMPERATURE));
  Serial.print(" , Object temp: ");
  Serial.println(mlx90615.getTemperature(MLX90615_OBJECT_TEMPERATURE));  

  //lcd
  lcd.setCursor(0, 0);
  lcd.print("Amb.temp:");
  lcd.print(mlx90615.getTemperature(MLX90615_AMBIENT_TEMPERATURE));
  lcd.println(" C");
  lcd.setCursor(0, 1);
  lcd.print("Meas.tmp:");
  lcd.print(mlx90615.getTemperature(MLX90615_OBJECT_TEMPERATURE));
  lcd.println(" C");

  delay(500);
}
