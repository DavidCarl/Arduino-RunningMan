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

byte manJumpOnPlace[8] = {
  B01110,
  B01110,
  B00100,
  B11111,
  B00100,
  B11111,
  B00000,
  B00000
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

struct position{
  int layer = 1;
  int pile = 0;
};
typedef struct position Position;

Position aRec;

int left = 8;
int jumpBtn = 9;
int right = 10;

void setup() {
// set up the LCD's number of columns and rows
Serial.begin(9600);

lcd.begin(16, 2);
pinMode(left, INPUT_PULLUP);
pinMode(jumpBtn, INPUT_PULLUP);
pinMode(right, INPUT_PULLUP);
pinMode(6, OUTPUT);
//lcd.createChar(0, manJumpRight);
//lcd.createChar(1, manJumpLeft);
lcd.createChar(0, manRunRightOne);
lcd.createChar(1, manRunRightTwo);
lcd.createChar(2, manRunLeftOne);
lcd.createChar(3, manRunLeftTwo);
lcd.createChar(4, manStand);
lcd.createChar(5, manJumpLeft);
lcd.createChar(6, manJumpOnPlace);
lcd.createChar(7, manJumpRight);
title();
loading();
}

void title() {
  lcd.setCursor(3,0);
  lcd.print("Runner Man");
  lcd.setCursor(6,1);
  lcd.print("RUN!");
  int tones[4]={800,600,800,1200};
  int tonesCount = sizeof(tones)/2;
  Serial.print(tonesCount);
  for (int i=0;i<tonesCount;i++){
    tone(6,tones[i],150);
    delay(250);
  }
  delay(3000);
  lcd.clear();
}

void loading(){
  lcd.setCursor(0,0);
  tone(6,500,50);
  lcd.write("Loading");
  for (int i=0;i<3;i++){
    delay(1000);
    tone(6,500,50);
    lcd.write("."); 
  }
  delay(1000);
  lcd.clear();
}


void loop() {
  int leftValue = digitalRead(left);
  int jumpValue = digitalRead(jumpBtn);
  int rightValue = digitalRead(right);
  if(leftValue == 0 && rightValue == 1){
    if(jumpValue == 0){
      jump(-1);
    }else{
      run(-1,2);
    }
  }
  if(leftValue == 1 && rightValue == 0) {
    if(jumpValue == 0){
      jump(1);
    }else{
      run(1,0);
    }
  } 
  if((leftValue == 1 && rightValue == 1) || (leftValue == 0 && rightValue == 0)){
      if(jumpValue == 0){
        jump(0);
      }else{
        stand();
      }
  }
    
}
bool inTheAir(){
  return (aRec.layer == 0);
}
void stand(){
  lcd.setCursor(aRec.pile,1);
  lcd.write(byte(4));
}
void adjustCurrentLayer(){
  if(aRec.layer == 0){
    aRec.layer = 1;
    delay(150);
    eraseCurrentFrame();  
  }
}
void run(int pile,int add) {
  printFrame(aRec.pile%2+add);
  tone(6,150,100);
  delay(150);
  eraseCurrentFrame();
  aRec.pile += pile;
  adjustCurrentPosition();
}
void jump(int pile) {
  eraseCurrentFrame();
  aRec.pile += pile;
  aRec.layer = 0;
  printFrame(6+pile);
  tone(6,250,125);
  delay(125);
  tone(6,500,125);
  delay(125);
  eraseCurrentFrame();
  adjustCurrentPosition();
  fall(pile);
}
void fall(int pile){
  aRec.pile += pile;
  aRec.layer = 1;
  printFrame(4);
  delay(150);
  eraseCurrentFrame();
  adjustCurrentPosition();      
}
void printFrame(int animation){
  lcd.setCursor(aRec.pile,aRec.layer);
  lcd.write(byte(animation));
}
void eraseCurrentFrame(){
  lcd.setCursor(aRec.pile,aRec.layer);
  lcd.write(' ');  
}
void adjustCurrentPosition(){
  if(aRec.pile>15){
    aRec.pile = 0;
  }else if(aRec.pile<0){
    aRec.pile = 15;
  }  
}
