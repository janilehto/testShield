#include <LiquidCrystal.h>
#include "Button.h"
#define backLight 13
#define rs 12
#define en 11
#define d4  10
#define d5 9
#define d6 8
#define d7 7
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Buttons
Button S1 (2); //button up
Button S2 (1); //button enter/back
Button S3 (0); //button down

//Outputs
#define D0 3
#define D1 4
#define D2 5
#define D3 6

// MenuItems shown on LCD
String menuItems[] = {"ANALOG Menu", "DIGITAL Menu"};
int menuPage = 0;
int cursorPosition = 0;

//custom cursor for menu
byte menuCursor[8] = {
  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};

byte downArrow[8] = {
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b10101, // * * *
  0b01110, //  ***
  0b00100  //   *
};

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH);

  lcd.begin(16, 2);
  lcd.createChar(0, menuCursor);
  lcd.createChar(1, downArrow);
  
  Serial.begin(9600);
}

void loop() {
mainMenu();
Buttons();
}

void mainMenu() {
if (menuPage == 0) {
  drawCursor();
  lcd.setCursor(1,0);
  lcd.print(menuItems[menuPage]); //Analog menu
  lcd.setCursor(1,1);
  lcd.print(menuItems[menuPage +1]);//Digital menu
} if (menuPage == 1 && cursorPosition == 0) {
  lcd.setCursor(15,2);
      lcd.write(byte(1));
      subMenu1();
      } if (menuPage == 1 && cursorPosition == 1) {   
       // subMenu2();
        }

  }

void drawCursor() {
  for (int cursorPos = 0; cursorPos < 1; cursorPos++) {     // Erases current cursor
    lcd.setCursor(0, cursorPos);
    lcd.print(" ");
  } 
 if(menuPage == 0) {
    if (cursorPosition == 0) { //shows cursor 1st line
     lcd.setCursor(0,0);
     lcd.write(byte(0));
    }
    if(cursorPosition == 1 ) { //shows cursor 2nd line
      lcd.setCursor(0,1);
      lcd.write(byte(0));
    }
 }
}

// S3 moves custom cursor down, increase cursor position value // S1 moves cursor up, decrease cursor position value 
void Buttons() {
  if (cursorPosition == 0 && S3.pressed()) { // moves cursor to position 0,0
         lcd.clear();
         cursorPosition ++;
        }
         if (cursorPosition == 1 && S1.pressed()) { // moves cursor to position 0,1         
         lcd.clear();
         cursorPosition --;         
        }

    //TODO S2 enter menu, erase cursor, wipe out mainmenu
    if (cursorPosition == 0 && S2.pressed()) {
      lcd.clear();
      menuPage = 1;
    }
    if (cursorPosition == 1 && S2.pressed()) {
      lcd.clear();
      
      }
}
// TODO if cursor points analog menu and enter button pushed, moves to this screen
// TODO extra submenu
void subMenu1() { // Analog
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
  }

// TODO if cursor points digital menu and enter button pushed, moves to this screen
// TODO extra submenu
/*void subMenu2() {  //Digital
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
}*/
