#include <AFMotor.h>

#define ir1 0 //left
#define ir2 1 //right
#define bckspeed 255
#define fwdspeed 255

AF_DCMotor ml(1);
AF_DCMotor mr(2);

void setup(){
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  
}

void loop(){
  if(!(digitalRead(ir1)==digitalRead(ir2))){
    if(digitalRead(ir1)){
      mr.run(BACKWARD);
      mr.setSpeed(bckspeed);
      ml.run(FORWARD);
      ml.setSpeed(fwdspeed);
    }
    if(digitalRead(ir2)){
      ml.run(BACKWARD);
      ml.setSpeed(bckspeed);
      mr.run(FORWARD);
      mr.setSpeed(fwdspeed);
    }
  }else if(digitalRead(ir1) == HIGH || digitalRead(ir2) == HIGH){
    uturn();
  }else{
    mr.run(FORWARD);
    ml.run(FORWARD);
    mr.setSpeed(fwdspeed);
    ml.setSpeed(fwdspeed);
  }
}

void uturn(){
    delay(100);
}

//either are  0
//neither are 0
//else(both are 0)
