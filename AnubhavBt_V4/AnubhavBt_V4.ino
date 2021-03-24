#include <AFMotor.h>

#define frntlght A0//front light on A5
#define bcklght 2//back light on 2
#define buzzer A1//buzzer on A4
#define mf A2
#define mb A3
#define ml A4
#define mr A5

AF_DCMotor mfb(2, MOTOR12_1KHZ); 
AF_DCMotor mlr(1, MOTOR12_1KHZ); 

int Speed= 255;
static bool radio = false;

char command; 

void setup() 
{       
  pinMode(frntlght, OUTPUT);
  pinMode(bcklght, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(mf, INPUT);
  pinMode(mb, INPUT);
  pinMode(mr, INPUT);
  pinMode(ml, INPUT);
  Serial.begin(9600);  
}

void loop(){
  if(Serial.available() > 0){ 
    command = Serial.read();
    Stop(); 
    switch(command){
    case 'F':  
      forward();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
    case 'G' :
      FWDleft();
      break;
    case 'I' :
      FWDright();
      break;
    case 'H' :
      BCKleft();
      break;
    case 'J' :
      BCKright();
      break;
    case 'W' :
      frntLightOn(true);
      break;
    case 'w' :
      frntLightOn(false);
      break;
    case 'U' :
      bckLightsOn(true);
      break;
    case 'u' :
      bckLightsOn(false);
      break;
    case 'V' :
      horn(true);
      break;
    case 'v' :
      horn(false);
      break;
    case 'X' :
      radio = true;
      break;
    case 'x' :
      radio = false;
      break;
    }
    for(int i = 0; i != 9;i++){
      if(Speed = i){
        SetSpeed(i*10);
      }
    }
    if(Speed = 'q'){
      SetSpeed(100);
    }
  }else{
    radio = true;
  }
  radioCntrl(radio);
}


int SetSpeed(int Speed){
  return map(Speed, 0, 100, 0,255);
}
int SetRadioSpeed(int Speed){
  return map(Speed, 0, 1023, 0,255);
}
void forward()
{
  mfb.setSpeed(Speed);
  mfb.run(FORWARD);
}

void back()
{
  mfb.setSpeed(Speed);
  mfb.run(BACKWARD);
}

void left()
{
  mlr.setSpeed(Speed);
  mlr.run(FORWARD);
}

void right()
{
  mlr.setSpeed(Speed);
  mlr.run(BACKWARD);
} 

void Stop()
{
  mfb.setSpeed(0);
  mfb.run(RELEASE);
  mlr.setSpeed(0);
  mlr.run(RELEASE);
}
void FWDleft()
{
  mfb.setSpeed(Speed);
  mfb.run(FORWARD);
  mlr.setSpeed(Speed);
  mlr.run(FORWARD);
}
void BCKleft()
{
  mfb.setSpeed(Speed);
  mfb.run(BACKWARD);
  mlr.setSpeed(Speed);
  mlr.run(FORWARD);
}
void FWDright()
{
  mfb.setSpeed(Speed);
  mfb.run(FORWARD);
  mlr.setSpeed(Speed);
  mlr.run(BACKWARD);
}
void BCKright()
{
  mlr.setSpeed(Speed);
  mlr.run(BACKWARD);
  mfb.setSpeed(Speed);
  mfb.run(BACKWARD);
}
void frntLightOn(bool state){
  if(state){
    digitalWrite(frntlght, HIGH);
  }else{
    digitalWrite(frntlght, LOW);
  }
}
void bckLightsOn(bool state){
  if(state){
    digitalWrite(bcklght, HIGH);
  }else{
    digitalWrite(bcklght, LOW);
  }
}
void horn(bool state){
  if(state){
    tone(buzzer, 1000);
  }else{
    noTone(buzzer);
  }
}
void radioCntrl(bool state){
  if(state){
    if(digitalRead(mf) == HIGH){
      Speed = SetRadioSpeed(digitalRead(mf));
      mfb.setSpeed(Speed);
      mfb.run(FORWARD);
    }else if(digitalRead(mb) == HIGH){
      Speed = SetRadioSpeed(digitalRead(mb));
      mfb.setSpeed(Speed);
      mfb.run(FORWARD);
    }
    if(digitalRead(mr) == HIGH){
      mfb.setSpeed(255);
      mfb.run(FORWARD);
    }else if(digitalRead(ml) == HIGH){
      mfb.setSpeed(255);
      mfb.run(FORWARD);
    }
  }
}
