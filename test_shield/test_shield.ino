#include <AFMotor.h>

AF_DCMotor Left(3);
AF_DCMotor Right(4);


void setup() {
Serial.begin(9600);
}

void loop() {
  Left.setSpeed(160);
  Right.setSpeed(160);
  Left.run(FORWARD);
  Right.run(FORWARD);
  delay(100);

  Left.run(RELEASE);
  Right.run(RELEASE);
  delay(1000);

  Left.run(BACKWARD);
  Right.run(BACKWARD);
  delay(100);

}
