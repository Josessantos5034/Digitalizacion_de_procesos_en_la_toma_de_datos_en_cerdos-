#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Q2HX711.h>
LiquidCrystal_I2C lcd(0x3f, 20, 4);
//pines//
const byte hx711_data_pin = 3;
const byte hx711_clock_pin = 2;
int tara_button = 8;
int mode_button = 11;
Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);
// variables //
float y1 = 2831.0; //la mediada que tenga el objeto//
long x1 = 0L;
long x0 = 0L;
float avg_size = 10.0;
float tara = 0;
bool tara_pushed = false;
bool mode_pushed = false;
int mode = 0;
float oz_conversion = 0.035274;
void setup() {
  Serial.begin(9600);
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT3);
  pinMode(tara_button, INPUT_PULLUP);
  pinMode(mode_button, INPUT_PULLUP);

  //iniciar pantalla lcd//
  lcd.init();
  lcd.backlight();
  delay (1000);


  for (int ii = 0; ii < int(avg_size); ii++) {
    delay(10);
    x0 += hx711.read();
  }
  x0 /= long(avg_size);
  Serial.println("Add Calibrated Mass");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Add Calibrated ");
  lcd.setCursor(0, 1);
  lcd.print("      Mass      ");
  //calibracion//
  int ii = 1;
  while (true) {
    if (hx711.read() < x0 + 10000)
    {

    }
    else
    {
      ii++;
      delay(2000);
      for (int jj = 0; jj < int(avg_size); jj++) {
        x1 += hx711.read();
      }
      x1 /= long(avg_size);
      break;
    }
  }
  Serial.println("Calibration Complete");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Calibration   ");
  lcd.setCursor(0, 1);
  lcd.print("    Complete    ");
}

void loop() {
  //lectura promedio//
  long reading = 0;
  for (int jj = 0; jj < int(avg_size); jj++)
  {
    reading += hx711.read();
  }
  reading /= long(avg_size);

  // calculo para calibracion //

  float ratio_1 = (float) (reading - x0);
  float ratio_2 = (float) (x1 - x0);
  float ratio = ratio_1 / ratio_2;
  float mass = y1 * ratio;
  if (tara_pushed)
  {
    tara = mass;
    tara_pushed = false;
    Serial.print("TARA");
    Serial.print(".");
    lcd.setCursor(0, 0);
    lcd.print("      TARA      ");
    lcd.setCursor(0, 1);
    lcd.print("      .         ");
    delay(300);
    Serial.print(".");
    lcd.setCursor(0, 0);
    lcd.print("      TARA      ");
    lcd.setCursor(0, 1);
    lcd.print("      ..        ");
    delay(300);
    Serial.println(".");
    lcd.setCursor(0, 0);
    lcd.print("      TARA      ");
    lcd.setCursor(0, 1);
    lcd.print("      ...       ");
    delay(300);
  }
  if (mode_pushed)
  {
    mode = mode + 1;
    mode_pushed = false;
    if (mode > 2) {
      mode = 0;
    }
  }
  if (mode == 0)
  {
    Serial.print(mass - tara);
    Serial.println(" g");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     SCALE!     ");
    lcd.setCursor(0, 1);
    lcd.print(mass - tara);
    lcd.print(" g");
  }
  else if (mode == 1)
  {
    Serial.print(mass - tara);
    Serial.println(" ml");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     SCALE!     ");
    lcd.setCursor(0, 1);
    lcd.print(mass - tara);
    lcd.print(" ml");
  }
  else
  {
    Serial.print((mass - tara)*oz_conversion);
    Serial.println(" oz");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     SCALE!     ");
    lcd.setCursor(0, 1);
    lcd.print((mass - tara)*oz_conversion);
    lcd.print(" oz");
  }
}
// interruptores//
ISR(PCINT0_vect)
{
  if (!(PINB & B00000001))
  {
    tara_pushed = true;           //Tara button was pushed
  }

  if (!(PINB & B00001000))
  {
    mode_pushed = true;           //Mode button was pushed
  }
}