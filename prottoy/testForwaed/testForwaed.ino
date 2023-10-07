#include <AFMotor.h>

AF_DCMotor Left(3);
AF_DCMotor Right(1);

int left[6] = {255,0,0,255,140,255}; 
int right[6] = {255,0,255,0,255,140}; 

void setup() {
  Left.setSpeed(255);
  Right.setSpeed(255);
}

void loop() {
  for(int i=0; i<6; i++){
    
    Left.setSpeed(left[i]);
    Right.setSpeed(right[i]);
    Left.run(FORWARD);
    Right.run(FORWARD);
    delay(1000); 
    Left.run(RELEASE);
    Right.run(RELEASE);
    delay(1000);
  }
  
}
