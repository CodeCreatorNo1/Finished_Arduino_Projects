
#include "SD.h" //Lib to read SD card
#include "TMRpcm.h" //Lib to play auido
#include "SPI.h" //SPI lib for SD card

#define Volume 7 // between 0-7
#define longest_recording_duration 2000 // change value to the duration of the longest recording to avoid overlap

//connect pin 9 to high for eng and to low for hindi

//format sd card as fat32
//all files should be in wav format
//  -en is english and  -hn is hindi

/*keep the following files in the sd card -
 * SlightRigth-en.wav
 * TurnRigth-en.wav
 * TurnAround-en.wav
 * SlightLeft-en.wav
 * TurnLeft-en.wav
 * PleaseTurn-en.wav
 * SlightRigth-hn.wav
 * TurnRigth-hn.wav
 * TurnAround-hn.wav
 * SlightLeft-hn.wav
 * TurnLeft-hn.wav
 * PleaseTurn-hn.wav
 */

/*connections -
 * 13 ->SCK
 * 12 ->MISO
 * 11 ->MOSI
 * 10 ->Speakerpin
 * 9  ->language
 * 8  ->right trig
 * 7  ->right echo
 * 6  ->center trig
 * 5  ->center echo
 * 4  ->CS
 * 3  ->left trig
 * 2  ->left echo
 */

TMRpcm Sound;

int echoPin[3]={2,5,7};
int trigPin[3]={3,6,8};
bool objAt[3]={false,false,false};

int getDistance(int trig, int echo){

  int distance,duration;
  
  digitalWrite(trig, LOW);
    
  delay(2);

  digitalWrite(trig, HIGH);
  
  delayMicroseconds(10);
  
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH);
  distance = duration / 58.2;

  return distance;
  
}

void playSound(){
  if(!(objAt[0]&&objAt[1]&&objAt[2])){
      return;
  }
  if(digitalRead(9)){
    if((objAt[0]==1)&&(objAt[0]==0)&&(objAt[0]==0)){
      Sound.play("SlightRigth-en.wav");
    }else if((objAt[0]==1)&&(objAt[0]==1)&&(objAt[0]==0)){
      Sound.play("TurnRigth-en.wav");
    }else if((objAt[0]==1)&&(objAt[0]==1)&&(objAt[0]==1)){
      Sound.play("TurnAround-en.wav");
    }else if((objAt[0]==0)&&(objAt[0]==0)&&(objAt[0]==1)){
      Sound.play("SlightLeft-en.wav");
    }else if((objAt[0]==0)&&(objAt[0]==1)&&(objAt[0]==1)){
      Sound.play("TurnLeft-en.wav");
    }else if((objAt[0]==0)&&(objAt[0]==1)&&(objAt[0]==0)){
      Sound.play("PleaseTurn-en.wav");
    }else{
      digitalWrite(10, HIGH);
    }
  }else{
    if((objAt[0]==1)&&(objAt[0]==0)&&(objAt[0]==0)){
      Sound.play("SlightRigth-hn.wav");
    }else if((objAt[0]==1)&&(objAt[0]==1)&&(objAt[0]==0)){
      Sound.play("TurnRigth-hn.wav");
    }else if((objAt[0]==1)&&(objAt[0]==1)&&(objAt[0]==1)){
      Sound.play("TurnAround-hn.wav");
    }else if((objAt[0]==0)&&(objAt[0]==0)&&(objAt[0]==1)){
      Sound.play("SlightLeft-hn.wav");
    }else if((objAt[0]==0)&&(objAt[0]==1)&&(objAt[0]==1)){
      Sound.play("TurnLeft-hn.wav");
    }else if((objAt[0]==0)&&(objAt[0]==1)&&(objAt[0]==0)){
      Sound.play("PleaseTurn-hn.wav");
    }else{
      digitalWrite(10, HIGH);
    }
  }
  
}

void setup() {
  
  Sound.speakerPin = 10;
  
  if (!SD.begin(4)) {
    while(true);
  }
  
  Sound.setVolume(Volume);
  Sound.quality(0);
}

void loop()
{
  delay(longest_recording_duration);
  int dist;
  for(int i = 0;i!=3;i++){
    dist = getDistance[i];
    if ( dist > 0 && dist < 18 ) {
      objAt[i] = true;
    }else{
      objAt[i] = false;
    }
  }
  
  playSound();
}
