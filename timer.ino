/*
  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   LCD VO to ground

   BUTTON to digital pin 8
*/
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int buttonPin = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int potPin = A3;
int potVal = 0;
int buttonState = 0;
bool screenCleared = false;
void setup()
{
  pinMode(buttonPin, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Set Timer:");
}

void stop()
{
  while (1)
    ;
}

void message()
{
  lcd.autoscroll();
  lcd.setCursor(4, 0);
  lcd.print("Timer up!");
  lcd.setCursor(4, 1);
  lcd.print("ha ha ha!");
}

void timer(int secs)
{
  while (secs >= 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("Countdown:");
    lcd.setCursor(10, 0);
    lcd.print(secs);
    secs = secs - 1;
    delay(1000);

    if (secs < 10)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(secs);
    }
    if (secs == 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      while (true)
      {
        message();
        delay(250);
      }
    }
  }
}

int setTimer()
{
  potVal = analogRead(potPin);
  if (potVal <= 1023)
  {
    potVal = (potVal * 3) / 51;
    lcd.setCursor(0, 1);
    lcd.print(potVal);
    if (potVal < 10)
    {
      if (screenCleared != true)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Set Timer:");
        screenCleared = true;
      }
      lcd.setCursor(0, 1);
    }
    if (potVal >= 10)
    {
      screenCleared = false;
    }

    if (buttonState == HIGH)
    {
      return potVal;
    }
  }
}

void debugScreen()
{
  lcd.setCursor(0, 0);
  int y = 9;
  if (y <= 10)
  {
    lcd.print("0,0");
    lcd.setCursor(0, 1);
    lcd.print("0,1");
  }
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  int input = setTimer();
  if (buttonState == HIGH)
  {
    lcd.clear();
    timer(input);
    setTimer();
  }
}
