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
#include <math.h>

//define pin constants
#define BUTTON_PIN 8 //place holder for now
#define LED_PIN 7 //place holder as 0 for now
#define DENOM_CAP 4
#define LIGHT_SENSOR_PIN 0


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int getLCD(int num1, int num2){
  if(num1==num2){
    return num1;
  }
  else if(num1<num2 && num2%num1==0){
    return num2;
  }
  else if(num2<num1 && num1%num2==0){
    return num1;
  }
  else{
    return num1*num2;
  }
}

int denom1=random(1,DENOM_CAP+1);
int denom2=random(1,DENOM_CAP+1);
int commonDenom=getLCD(denom1,denom2);
int coinIn=0;
int lastValue;
void setup() {
  
  //cleaning up the setup portion for now

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  //random number deals
  Serial.begin(9600);
  randomSeed(analogRead(0));
//  set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Question: ");

  //lcd.print("2   1");
  //lcd.setCursor(0, 1);
  //lcd.print("3 + 4");
  
  //delay(3000);

  //lcd.setCursor(0, 0);
  //lcd.print("8    3");
  //lcd.setCursor(0, 1);  
  //lcd.print("12 + 12");

  //delay(3000);

  //lcd.setCursor(0, 0);
  //lcd.print("8    3   =  11");
  //lcd.setCursor(0, 1);  
  //lcd.print("12 + 12  =  12");

  /*
  lcd.print("1   1");
  lcd.setCursor(0, 1);
  lcd.print("3 + 2");
  
  delay(5000);

  lcd.setCursor(0, 0);
  lcd.print("3   2");
  lcd.setCursor(0, 1);  
  lcd.print("6 + 6");

  delay(5000);

  lcd.setCursor(0, 0);
  lcd.print("3   2 = 5");
  lcd.setCursor(0, 1);  
  lcd.print("6 + 6 = 6");
  */
  
  //lcd.print("2 + 3 = 6");
  //lcd.print("1/2 + 1/3");
  lcd.setCursor(0,0);
  lcd.print("FRACNITE");
  lcd.setCursor(0,1);
  lcd.print("Press Button!");
  while(true){
    if(digitalRead(BUTTON_PIN)==LOW){
      break;
    }
  }

}

bool checkAns(int correct, int coinIn){
  return correct==coinIn;
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
 

  
    //if(digitalRead(BUTTON_PIN)==LOW){
      delay(500);
      lcd.clear();
      
      lcd.clear();
      incorrect: lcd.setCursor(0,0);
      lcd.print("What is the GCD?");
      lcd.setCursor(0,1);
      int photocellReading=analogRead(LIGHT_SENSOR_PIN);
      Serial.println(photocellReading);
      
      
      lcd.print((String)denom1+"+"+(String)denom2+"="+(String)coinIn); 
      //bool quit=false;
      //while (!quit){
      if(digitalRead(BUTTON_PIN)==LOW){
        lcd.clear(); //
        lcd.print("Enter Coins"); //
        if(checkAns(commonDenom,coinIn)){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Correct!");
          delay(5000);
          lcd.clear();
          lcd.clear();
          exit;
          
       
        }
        else if (!checkAns(commonDenom, coinIn)){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Try Again!");
          delay(5000);
          lcd.clear();
          coinIn=0;
          goto incorrect;
        }
        goto incorrect;
      }
    
    else if((lastValue-photocellReading)>30){
        ++coinIn;
        lcd.setCursor(0,1);
        lcd.print((String)denom1+"+"+(String)denom2+"="+(String)coinIn);
        Serial.println(coinIn);
        delay(5);
  }
  lastValue=photocellReading;
}
