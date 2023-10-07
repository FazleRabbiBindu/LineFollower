#include <AFMotor.h>

AF_DCMotor Left(3);
AF_DCMotor Right(4);

void setup() {
Left.setSpeed(255);
Right.setSpeed(255);
}

void loop() {
  Left.run(FORWARD);
  Right.run(FORWARD);

}
