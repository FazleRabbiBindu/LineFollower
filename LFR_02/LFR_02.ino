 #define LS1  2   
#define LS2 3            // left sensor
#define RS1  4
#define RS2 5            // right sensor


/*-------definning Outputs------*/
#define LM1 11    // left motor
#define LM2 10    // left motor
#define RM1 9    // right motor
#define RM2 6     // right motor

void setup()
{
  Serial.begin(9600);
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  pinMode(RS1, INPUT);
  pinMode(RS2, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

}

void loop()
{
  int L1,L2,R1,R2,L,R;
  L1 = digitalRead(LS1);
  L2 = digitalRead(LS2);
  L= L1+L2;
  R1 = digitalRead(RS1);
  R2 = digitalRead(RS2);
  R= R1+R2;
  if(L ==0 && R == 0)
  {
    MoveForward();
    Serial.print("Up\n");
  }
  else if(L ==2 && R == 2){
    Stop();
    Serial.print("X\n");
  }
  else if(L>0){
    TurnLeft();
    Serial.print("<-\n");
  }
   else if(R>0){
    TurnRight();
   Serial.print("->\n");
  }
}



void MoveForward()
{
    analogWrite(LM1, 35);
    analogWrite(LM2, 0);
    analogWrite(RM1, 35);
    analogWrite(RM2, 0);
    delay(20);
}

void TurnRight()
{
    analogWrite(LM1, 0);
    analogWrite(LM2, 150);
    analogWrite(RM1, 150);
    analogWrite(RM2, 0);
   // delay(30); 
}

void TurnLeft()
{
    analogWrite(LM1, 150);
    analogWrite(LM2, 0);
    analogWrite(RM1, 0);  
    analogWrite(RM2, 150);
   // delay(30);
}

void Stop()
{
    analogWrite(LM1, 0);
    analogWrite(LM2, 0);
    analogWrite(RM1, 0);
    analogWrite(RM2, 0);
    delay(20);
}
