#include <LiquidCrystal.h>

// Initialize the library with the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte manJumpRight[8] = {
  B01110,
  B01110,
  B00100,
  B11111,
  B01110,
  B01110,
  B11010,
  B00000
};  

byte manJumpLeft[8] = {
  B01110,
  B01110,
  B00100,
  B11111,
  B01110,
  B01110,
  B01011,
  B00000
};  

byte manRunRightOne[8] = {
  B01110,
  B01110,
  B00101,
  B11111,
  B10100,
  B00111,
  B11101,
  B00001
};
byte manRunRightTwo[8] = {
  B01110,
  B01110,
  B10100,
  B11111,
  B00100,
  B00111,
  B11101,
  B00001
};  

int spacer = 0;

void setup() {
// set up the LCD's number of columns and rows
lcd.begin(16, 2);
//lcd.createChar(0, manJumpRight);
//lcd.createChar(1, manJumpLeft);
lcd.createChar(0, manRunRightOne);
lcd.createChar(1, manRunRightTwo);
}


void loop() {
// Print a message to the LCD
  lcd.setCursor(spacer,1);
  lcd.write(byte(spacer%2));
  delay(200);
  lcd.clear();
  spacer++;
  if(spacer>16){
    spacer = 0;
  }
}
