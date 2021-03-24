#include <LiquidCrystal.h>

int whiteMins = 5;
int blackMins = 5;
int whiteSecs = 0;
int blackSecs = 0;

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  newGame();
  lcd.begin(16,2);
  pinMode(13, INPUT);
  pinMode(6, INPUT);

}

void loop() {
  if( !(whiteMins == -1 || blackMins == -1)){
    
   if(digitalRead(13)){
     whiteSecs--;
     if(whiteSecs == -1){
        whiteMins --;
        whiteSecs = 59;
      }
   }
   if(!digitalRead(13)){
     blackSecs--;
     if(blackSecs == -1){
       blackMins --;
       blackSecs = 59;
     }
   }
    
   lcd.setCursor(0,0);
   lcd.print(whiteMins);
   lcd.print(":");
   lcd.print(whiteSecs);
   lcd.setCursor(12,0);
   lcd.print(blackMins);
   lcd.print(":");
   lcd.print(blackSecs);
  
  }else{
    newGame();
  }
  if(digitalRead(6)){
    newGame();
  }

  delay(1000);

}
void newGame(){
  whiteMins = 5;
  blackMins = 5;
  whiteSecs = 0;
  blackSecs = 0;
}
