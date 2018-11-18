//LCD Screen Setup:
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Least Common Denominator Question and Answer variable Setups:
#define DENOM_CAP 4
int denom1 = random(1,DENOM_CAP+1);
int denom2 = random(1,DENOM_CAP+1);
int commonDenom = getLCD(denom1,denom2);
int coinIn=0;

//photosenor - led detection variables
int photoReading;
int lastReading;

//Hardware Pins:
const int button_pin = 8;
const int led_pin = 7;
const int photo_pin = 0;
const int piezo_pin = 12;

//button status:
bool button_submit;

void setup() {
  //initialize all harware inputs and ouputs:
  pinMode(photo_pin, INPUT);  
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT); 
  pinMode(piezo_pin, OUTPUT);
  lcd.begin(16, 2);
  button_submit = false;
  Serial.begin(9600);
  
  //Game welcome screen
  lcd.setCursor(0,0);
  lcd.print("FRACNITE!");
  lcd.setCursor(0,1);
  lcd.print("Press button.");
  
  while(true){
    if(digitalRead(button_pin)==LOW){
      break;
    }
  }
}

void loop() {
  //fortnite begin screen:
  digitalWrite(led_pin, HIGH);  
  
  photoReading = analogRead(photo_pin);
  Serial.println(photoReading);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("What is the LCD?");
  lcd.setCursor(0,1);
  lcd.print(String(denom1) + " and "+ String(denom2) + ": " + String(coinIn));
  delay(500);
    
  if(photoReading - lastReading > 30)
  {
    if(button_submit == false)
    {
      coinIn++;
      delay(500);
    }
  }
  
  lastReading = photoReading;
    
  if(digitalRead(button_pin)==LOW)
  {
    button_submit = true;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Checking Answer.");
  }
}

//Method that finds the LCD of two numbers.
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

//Method that checks if answer is true
bool checkAns(int correct, int coinIn){
  return correct==coinIn;
}
