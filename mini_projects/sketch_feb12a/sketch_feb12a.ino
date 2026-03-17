#include <SPI.h>
#include <AD9833.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define FSYNC 10

AD9833 gen(FSYNC);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  gen.begin();
  gen.setWave(AD9833_SINE);
  gen.setFrequency(1.0);   // 1 Hz heart rate

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("ECG Generator");
}

void loop() {

  int signal = analogRead(A0);

  static int counter = 0;
  counter++;

  // Add QRS spike
  if(counter % 200 == 0){
    signal = signal + 300;
  }

  Serial.println(signal);

  lcd.setCursor(0,1);
  lcd.print("Signal:");
  lcd.print(signal);
  lcd.print("   ");

  delay(50);
}
