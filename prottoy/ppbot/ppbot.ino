#include <AFMotor.h>

AF_DCMotor Left(3);
AF_DCMotor Right(1);



//PID
int IMS = 180; //initial motor speed
int LMS = 180;
int RMS = 180;

int error = 0; 
float P=0,I=0,D=0,PID=0;
float prevErr = 0; //previous error
float prevI = 0; //previous integral
float kp =22 ,kd = 38, ki = 1.7;//tune it

int flag=0;


int middleValue = 300;
int sensorVal[6];
int sum = 0, searchFlag=0;

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
  pidFun(); //pid function
  
  sum = (sensorVal[0]*32)+(sensorVal[1]*16)+(sensorVal[2]*8)+(sensorVal[3]*4)+(sensorVal[4]*2)+(sensorVal[5]*1);
  pidExecute();
  logic();
  
}


void readSensor()
{
  for(int i=0; i<6; i++)
  {
    if(analogRead(i)>middleValue)
      sensorVal[5-i] = 0;
     else
      sensorVal[5-i]= 1;

    Serial.print(sensorVal[5-i]);
    Serial.print(' ');
  }
  Serial.println('\n');
  
}


void logic()
{
  if(sum == 12 || sum == 14 || sum == 24 || sum == 28 || sum == 4 || sum == 6 || sum == 8)//while black or white stripe 
  {
    Forward();
    flag=0;
  }
  else if(sum == 63)//while full black (T)
  {
    Stop();
    
  }

  else if(sum == 15)//right
  {
    softRight();
    flag=1;
  }
  else if(sum == 60) //left
  {
    softLeft();
    flag=1;
  }
  else if(sum == 13)//right angle
  {
    while(sum != 0)
    {
      Forward(); 
      
    }
    
    Stop();
    delay(500);
    
    while(sum != 12 || sum != 14 || sum != 24 || sum != 28 || sum != 4 || sum != 6 || sum != 8)
    {
      hardRight(); 
    }
  }
  else if(sum == 44)//left angle
  {
    while(sum != 0)
    {
      Forward(); 
    }
    
    Stop();
    delay(500);
    
    while(sum != 12 || sum != 14 || sum != 24 || sum != 28 || sum != 4 || sum != 6 || sum != 8)
    {
      hardLeft(); 
    }
  }
  else
  {
    ++searchFlag;
    if(searchFlag>3){
      searchFlag=0;
     Search(); 
    }
  }
}
















void pidExecute()
{
  LMS = IMS+PID;
  RMS = IMS-PID;
  constrain(LMS,0,255);
  constrain(RMS,0,255);  
  
  Left.setSpeed(LMS);
  Right.setSpeed(RMS);
}

void pidFun()
{
  if(sensorVal[0] == 1 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = -3;
    
  }
  else if(sensorVal[0] == 1 && sensorVal[1] == 1 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error =-2.4;
    
  }
  else if(sensorVal[0] == 0 && sensorVal[1] == 1 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = -1.8;
  }
    else if(sensorVal[0] == 0 && sensorVal[1] == 1 && sensorVal[2] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = -1.2;
  }
  else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = -0.6;
  }
    else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 1 && sensorVal[3] == 1 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = 0;
  }
  else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 1 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = 0.6;
  }
    else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 1 && sensorVal[4] == 1 && sensorVal[5] == 0)
  {
    error = 1.2;
  }
  else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 1 && sensorVal[5] == 0)
  {
    error = 1.8;
  }
    else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 1 && sensorVal[5] == 1)
  {
    error = 2.4;
  }
  else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 1)
  {
    error = 3;
  }
  else{
    error = 0; 
    P=0;I=0;D=0;PID=0;
    prevErr = 0; 
    prevI = 0;
  }


  P = error;
  I = I+prevI;
  D = error-prevErr;
  PID = (kp*P) + (kd*D) + (ki*I);
  prevErr = error;
  prevI = I; 
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
  Serial.println("Backward"); 
}

//INA,INB LEFT
void softRight()
{
  Left.setSpeed(IMS);
  Right.setSpeed(0);
    
  Left.run(FORWARD);
  Right.run(RELEASE);
  Serial.println("Soft Left");
}
void softLeft()
{
  Left.setSpeed(0);
  Right.setSpeed(IMS);
    
  Left.run(RELEASE);
  Right.run(FORWARD);
  Serial.println("Soft Right");
}
void hardRight()
{
  Left.setSpeed(IMS);
  Right.setSpeed(IMS);
    
  Left.run(FORWARD);
  Right.run(BACKWARD);
  Serial.println("Hard Left");
}
void hardLeft()
{
  Left.setSpeed(IMS);
  Right.setSpeed(IMS);
    
  Left.run(BACKWARD);
  Right.run(FORWARD);
  Serial.println("Hard Right");  
}
void Stop()
{
  Left.setSpeed(0);
  Right.setSpeed(0);
    
  Left.run(RELEASE);
  Right.run(RELEASE);
  Serial.println("Stop");
}
void Search()
{
  if(sum>12)
  {
    hardLeft();
  }
  else{
    hardRight();  
  }
  Serial.println("Searching");
}
