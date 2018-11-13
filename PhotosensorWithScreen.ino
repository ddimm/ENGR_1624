/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int denom;
String bottom;
int photocellPin = 0;
int photocellReading;
int lastReading;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(8, INPUT_PULLUP);
  denom = 0;
  bottom = "";
  Serial.begin(9600);
  
}


void loop() {

  if (digitalRead(8) == LOW) {
        if(denom == 2){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Correct!");
          delay(3000);
        }
        delay(200);
  }
 
  lcd.setCursor(0, 0);
  lcd.print("1    1       ");
  lcd.setCursor(0, 1);
  bottom = "4 +  3   =  ";
  bottom.concat((String)denom);
  lcd.print(bottom);

  photocellReading = analogRead(photocellPin);  
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);
  
  delay(100);
  if(abs(photocellReading - lastReading) > 50){
    denom++;
    delay(1500);
  }
  lastReading = photocellReading;

  //delay(3000);
  //lcd.setCursor(0, 0);
  //lcd.print("1    2       ");
  //delay(3000);
  
  //lcd.clear();
}
