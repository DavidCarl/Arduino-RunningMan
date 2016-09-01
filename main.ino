#include <LiquidCrystal.h>

// Initialize the library with the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte manStand[8] = {
  B01110,
  B01110,
  B00100,
  B11111,
  B00100,
  B00100,
  B01010,
  B10001
};

byte manJumpRight[8] = {
  B01100,
  B01110,
  B00100,
  B11111,
  B01110,
  B01110,
  B11010,
  B00000
};  

byte manJumpLeft[8] = {
  B00110,
  B01110,
  B00100,
  B11111,
  B01110,
  B01110,
  B01011,
  B00000
};  

byte manRunRightOne[8] = {
  B01100,
  B01110,
  B00101,
  B11111,
  B10100,
  B00111,
  B11101,
  B00001
};
byte manRunRightTwo[8] = {
  B01100,
  B01110,
  B10100,
  B11111,
  B00100,
  B00100,
  B01010,
  B10001
};

byte manRunLeftOne[8] = {
  B00110,
  B01110,
  B10100,
  B11111,
  B00101,
  B11100,
  B10111,
  B10000
};
byte manRunLeftTwo[8] = {
  B00110,
  B01110,
  B00101,
  B11111,
  B00100,
  B00100,
  B01010,
  B10001
};

int spacer = 0;
int left = 8;
int jump = 9;
int right = 10;


void setup() {
// set up the LCD's number of columns and rows
Serial.begin(9600);


lcd.begin(16, 2);
pinMode(left, INPUT_PULLUP);
pinMode(jump, INPUT_PULLUP);
pinMode(right, INPUT_PULLUP);
//lcd.createChar(0, manJumpRight);
//lcd.createChar(1, manJumpLeft);
lcd.createChar(0, manRunRightOne);
lcd.createChar(1, manRunRightTwo);
lcd.createChar(2, manRunLeftOne);
lcd.createChar(3, manRunLeftTwo);
lcd.createChar(4, manStand);
}


void loop() {
  int leftValue = digitalRead(left);
  int jumpValue = digitalRead(jump);
  int rightValue = digitalRead(right);
  if(leftValue == 0 && rightValue == 1){
  move(-1,2);
  }
  if(leftValue == 1 && rightValue == 0) {
    move(1,0);
    } 
    if((leftValue == 1 && rightValue == 1) || (leftValue == 0 && rightValue == 0)){
      stand();
      }
}

void stand(){
  lcd.setCursor(spacer,1);
  lcd.write(byte(4));
}

void move(int into,int add) {
  Serial.print(into);
  lcd.setCursor(spacer,1);
  lcd.write(byte(spacer%2+add));
  delay(150);
  lcd.setCursor(spacer,1);
  lcd.write(' ');
  spacer+= into;
  if(spacer>=16){
    spacer = 0;
  }else if(spacer<=0){
    spacer = 16;
}
}
