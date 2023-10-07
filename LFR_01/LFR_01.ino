#define IRL A0
#define IRR A1

#define EN1 9
#define EN2 10

#define MotorL1 3
#define MotorL2 4
#define MotorR1 5
#define MotorR2 6


void setup() {
  pinMode(IRL, INPUT);
  pinMode(IRR, INPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(EN1,OUTPUT);
  pinMode(EN2,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  //delay(500);
  int IRl = analogRead(IRL);
  int IRr = analogRead(IRR);
  analogWrite(EN1,100);
  analogWrite(EN2,100);
  
  if(IRr<500 && IRl>500)//Right
  {
    analogWrite(EN1,100);
    analogWrite(EN2,100);

    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorL2, HIGH);
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorR2, HIGH);
    delay(50);
    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorL2, LOW);
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorR2, LOW);
    delay(100);
    
    analogWrite(EN1,255);
    analogWrite(EN2,255);
    //go left
    Serial.println("LEFT");
    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorL2, HIGH);
    digitalWrite(MotorR1, HIGH);
    digitalWrite(MotorR2, LOW);
    delay(100);
  }
  else if(IRr>500 && IRl<500)//left
  { 
    analogWrite(EN1,100);
    analogWrite(EN2,100);

    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorL2, HIGH);
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorR2, HIGH);
    delay(50);
    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorL2, LOW);
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorR2, LOW);
    delay(100);
    
    analogWrite(EN1,255);
    analogWrite(EN2,255);
    //go right
    Serial.println("Right");
    digitalWrite(MotorL1, HIGH);
    digitalWrite(MotorL2, LOW);
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorR2, HIGH);
    delay(100);
  }
  else if(IRr<500 && IRl<500)//GO
  {
    //Forward
    Serial.println("GOING");
    digitalWrite(MotorL1, HIGH);
    digitalWrite(MotorL2, LOW);
    digitalWrite(MotorR1, HIGH);
    digitalWrite(MotorR2, LOW);
  }
  else if(IRr>500 && IRl>500)//STOP
  {
    //STOP
    Serial.println("STOP");
    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorL2, LOW);
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorR2, LOW);
  }

  else//STOP
  {
    
        //STOP
    Serial.println("Stop");
    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorL2, LOW);
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorR2, LOW);


  }
}
