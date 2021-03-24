#include <Servo.h>

Servo myservo;

int pos = 0;
int input;

void setup() {
  myservo.attach(A0);
  pinMode(A5, INPUT);

  Serial.begin (9600);
}

void loop() {
  input = map(analogRead(A5),0,255,0,100);
  Serial.println(input);
  if(input <= 10){
    myservo.write(130);
    delay(100);
    myservo.write(180);
  }else{
    myservo.write(180);
  }
  delay(100);
}
