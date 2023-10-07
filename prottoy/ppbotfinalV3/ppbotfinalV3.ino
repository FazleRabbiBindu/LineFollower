#include <AFMotor.h>

AF_DCMotor Left(3);
AF_DCMotor Right(4);



//PID
int IMS = 170; //initial motor speed
int LMS = 180;
int RMS = 180;

int error = 0; 
float P=0,I=0,D=0,PID=0;
float prevErr = 0; //previous error
float prevI = 0; //previous integral
float kp =22 ,kd = 38, ki = 1.7;//tune it

int flag=0,tlag=0;


int middleValue = 300;
int sensorVal[6];
int sum = 0, searchFlag=0,sumTemp=12;

void readSensor();
void Forward();
void Back();
void Stop();
void Search();
void softRight();
void softLeft();
void hardRight();
void hardLeft();
void logic();
void pidFun(); //pid function
void pidExecute(); // analog write via pid upadate





void setup() {
  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);

  Serial.begin(9600);
}

void loop() {
  
  readSensor();
  pidExecute();
  
  logic();
  Serial.print("LMS ");
  Serial.print(LMS);
  Serial.print("    ");
  Serial.print("RMS");
  Serial.print(RMS);
  
  Serial.println();
  Serial.println();
  Serial.println();
  
}


void readSensor()
{
  for(int i=0; i<6; i++)
  {
    if(analogRead(5-i)>middleValue)
      sensorVal[5-i] = 0;
     else
      sensorVal[5-i]= 1;

    Serial.print(sensorVal[5-i]);
    Serial.print(' ');
  }
  Serial.println('\n');
  sum = (sensorVal[0]*32)+(sensorVal[1]*16)+(sensorVal[2]*8)+(sensorVal[3]*4)+(sensorVal[4]*2)+(sensorVal[5]*1);
  
  pidFun(); //pid function
}


void logic()
{
if(sum == 12 || sum == 24 || sum == 4 || sum == 6 || sum == 8 || sum==2 || sum==16 || sum==14 || sum==28)//while black or white stripe 
  {
    Serial.println('Condition Forward');
    Forward();
  }
  else if(sum == 63)//while full black (T)
  {
    Forward();
    delay(100);
    Serial.println('Condition Stop');
    Stop();   
    readSensor();
    if(sum==63){
      Stop();
      delay(3000); 
    }
    else if(sum==0){
      Search();
    }
    else{
      readSensor();
      Forward();
    }
  }
else if(sum == 7 || sum == 11 || sum == 13 || sum == 19 || sum == 25 || sum == 49)//right 30d
{
//  while(sum != 0)
//  {
//    readSensor();
//    Left.run(FORWARD);    
//    Right.run(FORWARD);    
//  }
//  
//  Left.run(RELEASE);    
//  Right.run(RELEASE);    
//  delay(1000);
//  
  hardRight();
  delay(200);
  readSensor();
  Stabilizer();
}
else if(sum == 35 || sum == 36 || sum == 38 || sum == 44 || sum == 50 || sum == 52 || sum == 56)//left 30d
{
//  while(sum != 0)
//  {
//    readSensor();
//    Left.run(FORWARD);    
//    Right.run(FORWARD);    
//  }
//
//  Left.run(RELEASE);    
//  Right.run(RELEASE);    
//  delay(1000);
  
  hardLeft();
  delay(200);
  readSensor();
  Stabilizer();
}
  else
  {
//    sumTemp= sum;
//    Serial.println("Condition Else");
//    ++searchFlag;
//    if(searchFlag>3){
//      searchFlag=0;
     Search(); 
//    }
  }
}
















void pidExecute()
{
//  change insign 

  P = error;
  I = I+prevI;
  D = error-prevErr;
  PID = (kp*P) + (kd*D) + (ki*I);
  prevErr = error;
  prevI = I; 
  
  LMS = IMS+PID;
  RMS = IMS-PID;
  constrain(LMS,0,255);
  constrain(RMS,0,255);  
  
  Left.setSpeed(LMS);
  Right.setSpeed(RMS);
}

void pidFun()
{
//  if(sensorVal[0] == 1 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
//  {
//    error = -5;
//    
//  }
  if(sensorVal[0] == 1 && sensorVal[1] == 1 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error =-4;
    
  }
  else if(sensorVal[0] == 0 && sensorVal[1] == 1 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = -3;
  }
    else if(sensorVal[0] == 0 && sensorVal[1] == 1 && sensorVal[2] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = -2;
  }
  else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = -1;
  }
    else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 1 && sensorVal[3] == 1 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = 0;
  }
  else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 1 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = 1;
  }
    else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 1 && sensorVal[4] == 1 && sensorVal[5] == 0)
  {
    error = 2;
  }
  else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 1 && sensorVal[5] == 0)
  {
    error = 3;
  }
    else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 1 && sensorVal[5] == 1)
  {
    error = 4;
  }
//  else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 1)
//  {
//    error = 5;
//  }
  else{
    error = 0; 
    P=0;I=0;D=0;PID=0;
    prevErr = 0; 
    prevI = 0;
  }
}

void Forward()
{
  Left.run(FORWARD);
  Right.run(FORWARD);
  Serial.println("Forward"); 
}

void Back()
{
  Left.setSpeed(IMS);
  Right.setSpeed(IMS);
    
  Left.run(BACKWARD);
  Right.run(BACKWARD);
  Stabilizer();
  Serial.println("Backward"); 
}

//INA,INB LEFT
void softRight()
{
  Left.setSpeed(IMS);
  Right.setSpeed(0);
    
  Left.run(FORWARD);
  Right.run(RELEASE);
  flag=1;
  Serial.println("Soft Left");
}
void softLeft()
{
  Left.setSpeed(0);
  Right.setSpeed(IMS);
    
  Left.run(RELEASE);
  Right.run(FORWARD);
  tlag=1;
  Serial.println("Soft Right");
}
void hardRight()
{
  Left.setSpeed(IMS);
  Right.setSpeed(IMS);
    
  Left.run(FORWARD);
  Right.run(BACKWARD);
  flag=1;
  Serial.println("Hard Left");
}
void hardLeft()
{
  Left.setSpeed(IMS);
  Right.setSpeed(IMS);
    
  Left.run(BACKWARD);
  Right.run(FORWARD);
  tlag=1;

  Serial.println("Hard Right");  
}
void Stop()
{
  Left.setSpeed(0);
  Right.setSpeed(0);
    
  Left.run(RELEASE);
  Right.run(RELEASE);
//  Stabilizer();
  Serial.println("Stop");
}
void Search()
{
  readSensor();
//  Stop();
  if(sum>12)
  {
    softLeft();
      Stabilizer();
  }
  else if(sum<8){
    softRight(); 
      Stabilizer(); 
  }
  else if(sum == 12)
  {
    Forward();
  }
  else
  {
    Stop();
    delay(500);
  }
  Serial.println("Searching");
}

void Stabilizer()
{
  while(1)
  {
    readSensor();
    
    if(sum == 12)
    {
      if(flag==1 && tlag==0)
      {
        hardLeft();
        delay(10);
        flag=0;
        tlag=0;
        readSensor();
      }
      else if(flag==0 && tlag==1)
      {
        hardRight();
        delay(10);
        flag=0;
        tlag=0;
        readSensor();
      }
      Stop();
      delay(100);
      break;
    }
  }
  readSensor();
  pidExecute();
  
  Forward();
}
