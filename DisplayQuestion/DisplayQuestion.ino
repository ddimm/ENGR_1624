// include the library code:
#include <LiquidCrystal.h>
#include <math.h>

//define pin constants
#define BUTTON_PIN 8 //place holder for now
#define LED_PIN 7 //place holder as 0 for now
#define DENOM_CAP 4
#define LIGHT_SENSOR_PIN 0
#define BUZZER_PIN 9


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void(* resetFunc)(void)=0;
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

int denom1;
int denom2;;
int commonDenom;
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
  denom1=random(1,DENOM_CAP+1);
  denom2=random(1, DENOM_CAP+1);
  commonDenom=getLCD(denom1, denom2);
  lcd.begin(16, 2);
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
  
  lcd.clear();
  digitalWrite(LED_PIN, HIGH);
  incorrect: lcd.setCursor(0,0);
  lcd.print("What is the LCD?");
  lcd.setCursor(0,1);
  lcd.print((String)denom1+" and "+(String)denom2+": "+(String)coinIn);
  delay(100);
  
  int photocellReading=analogRead(LIGHT_SENSOR_PIN);
  Serial.println(photocellReading);

  if(digitalRead(BUTTON_PIN)==LOW){
    if(checkAns(commonDenom,coinIn)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Correct!");
      delay(500);
      lcd.clear();
      resetFunc();
    }
    else if (!checkAns(commonDenom, coinIn)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Try Again!");
      delay(500);
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
