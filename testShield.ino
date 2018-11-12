#include <LiquidCrystal.h>

#define rs 12
#define en 11
#define d4  10
#define d5 9
#define d6 8
#define d7 7
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Buttons
#define S1 2
#define S2 1
#define S3 0

//Outputs
#define D0 3
#define D1 4
#define D2 5
#define D3 6

void setup() {
  lcd.begin(16, 2);

  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);
  pinMode(S3, INPUT_PULLUP);
  
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
}

void loop() {
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(analogRead(A0));
  lcd.setCursor(8,0);
  lcd.print(analogRead(A1));
  lcd.setCursor(0,1);
  lcd.print(analogRead(A2));
  lcd.setCursor(8,1);
  lcd.print(analogRead(A3));

  if(!digitalRead(S1) || !digitalRead(S2) || !digitalRead(S3)){
    digitalWrite(D0, HIGH);
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);  
    digitalWrite(D3, HIGH);  
  }else{
    digitalWrite(D0, LOW);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);  
    digitalWrite(D3, LOW);  
  }
}
