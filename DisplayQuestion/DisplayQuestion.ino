// include the library code:
#include <LiquidCrystal.h>
#include <math.h>

//define pin constants
#define BUTTON_PIN 8 //place holder for now
#define LED_PIN 7 //place holder as 0 for now
#define DENOM_CAP 4
#define LIGHT_SENSOR_PIN 0
#define BUZZER_PIN 9


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


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
      delay(1000);
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
      tone(BUZZER_PIN, NOTE_C4,1000);
      delay(500);
      noTone(BUZZER_PIN);
      
      
      tone(BUZZER_PIN, NOTE_E4,1000);
      delay(500);
      noTone(BUZZER_PIN);
      tone(BUZZER_PIN, NOTE_G4,1000);
      delay(500);
      noTone(BUZZER_PIN);
      
      tone(BUZZER_PIN, NOTE_C5,1000);
      delay(500);
      lcd.clear();
      resetFunc();
    }
    else if (!checkAns(commonDenom, coinIn)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Try Again!");
      tone(BUZZER_PIN, NOTE_C4, 1000);
      delay(500);
      noTone(BUZZER_PIN);
      tone(BUZZER_PIN,NOTE_A3,1000);
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
    tone(BUZZER_PIN, NOTE_C5,500);
    tone(BUZZER_PIN,NOTE_C5, 500);
    delay(5);
  }
  lastValue=photocellReading;
}
