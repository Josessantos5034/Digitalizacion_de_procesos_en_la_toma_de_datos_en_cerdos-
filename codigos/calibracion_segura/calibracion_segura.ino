#include "HX711.h"

#include <Wire.h>      // libreria de comunicacion por I2C
#include <LCD_I2C.h>
//#include <LiquidCrystal_I2C.h>  // libreria para LCD por I2C

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

HX711 scale;
//LiquidCrystal_I2C lcd(0x20,16,2);
LCD_I2C lcd(0x27); // Default address of most PCF8574 modules, change according

float calibration_factor = -4034.09091; //-7050 worked for my 440lb max scale setup

void setup() {

  lcd.backlight();
  //lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  //lcd.print ("Reading: ");
  lcd.print ("Reading: ");
  lcd.setCursor(11, 0);
  lcd.print(scale.get_units(), 1);
  Serial.print(scale.get_units(), 1);
  delay(500);
  //lcd.setCursor(0, 0);
  //lcd.print(scale.get_units(), 1);
  Serial.print(" lbs"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.println();

  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
}
