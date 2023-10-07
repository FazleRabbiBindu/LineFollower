//motor parameter

#define inC 4
#define inD 5
#define inA 6
#define inB 7
#define enA 9
#define enB 3

//PID
int IMS = 160; //initial motor speed
int LMS = 120;
int RMS = 120;

int error = 0; 
float P=0,I=0,D=0,PID=0;
float prevErr = 0; //previous error
float prevI = 0; //previous integral
float kp =30 ,kd = 45, ki = 1.7;//tune it

int flag=0, tlag=0;


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

  pinMode(inA,OUTPUT);
  pinMode(inB,OUTPUT);
  pinMode(inC,OUTPUT);
  pinMode(inD,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);

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
//  pidFun(); //pid function
 
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
    if(analogRead(i)>500)
      sensorVal[i] = 1;
     else
      sensorVal[i]= 0;

    Serial.print(sensorVal[i]);
    Serial.print(' ');
  }
  Serial.println('\n');
  sum = (sensorVal[0]*32)+(sensorVal[1]*16)+(sensorVal[2]*8)+(sensorVal[3]*4)+(sensorVal[4]*2)+(sensorVal[5]*1); 
  
  pidFun();
}


void logic()
{
if(sum == 12 || sum == 24 || sum == 4 || sum == 6 || sum == 8 || sum==2 || sum==16 || sum==14 || sum==28)//while black or white stripe 
  {
    Serial.println("Condition Forward");
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
      delay(1000); 
    }
    else if(sum==0){
      Search();
    }
    else{
      readSensor();
      Forward();
    }
  }
//
//  else if(sum == 15)//right
//  {
//    Serial.println("Condition Soft Right");
//    softRight();
//    flag=1;
//  }
//  else if(sum == 60) //left
//  {
//    Serial.println("Condition Soft Left");
//    softLeft();
//    flag=1;
//  }
//  else if(sum == 13)//right angle
//  {
//    Serial.println("Condition Right angle");
//    while(sum != 0)
//    {
//      Forward(); 
//      
//    }
//    
//    Stop();
//    delay(500);
//    
//    while(sum != 12 || sum != 24 || sum != 4 || sum != 6 || sum != 8)
//    {
//      hardRight(); 
//    }
//  }
//  else if(sum == 44)//left angle
//  {
//    Serial.println("Condition Left angle");
//    while(sum != 0)
//    {
//      Forward(); 
//    }
//    
//    Stop();
//    delay(500);
//    
//    while(sum != 12 ||sum != 24 || sum != 4 || sum != 6 || sum != 8)
//    {
//      hardLeft(); 
//    }
//  }
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
  

  P = error;
  I = I+prevI;
  D = error-prevErr;
  PID = (kp*P) + (kd*D) + (ki*I);
  prevErr = error;
  prevI = I; 
  
//  change insign 
  LMS = IMS+PID;
  RMS = IMS-PID;
  constrain(LMS,0,255);
  constrain(RMS,0,255); 
   
  analogWrite(enA, RMS);
  analogWrite(enB, LMS);
}

void pidFun()
{
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

  else{
    error = 0; 
    P=0;I=0;D=0;PID=0;
    prevErr = 0; 
    prevI = 0;
  }

}

void Forward()
{
  digitalWrite(inA,LOW);
  digitalWrite(inB,HIGH);
  digitalWrite(inC,LOW);
  digitalWrite(inD,HIGH);

  Serial.println("Forward"); 
}

void Back()
{
  analogWrite(enA, IMS);
  analogWrite(enB, IMS);
  
  digitalWrite(inA,HIGH);
  digitalWrite(inB,LOW);
  digitalWrite(inC,HIGH);
  digitalWrite(inD,LOW);

  Serial.println("Backward"); 
}

//INA,INB LEFT
//enA right
void softRight()
{

  analogWrite(enA, 0);
  analogWrite(enB, IMS);
  
  digitalWrite(inA,LOW);
  digitalWrite(inB,LOW);
  digitalWrite(inC,LOW);
  digitalWrite(inD,HIGH);
  flag=1;

  Serial.println("Soft Left");
}

void softLeft()
{
  analogWrite(enA, IMS);
  analogWrite(enB, 0);
  
  digitalWrite(inA,LOW);
  digitalWrite(inB,HIGH);
  digitalWrite(inC,LOW);
  digitalWrite(inD,LOW);
  tlag=1;

  Serial.println("Soft Right");
}
void hardRight()
{
  analogWrite(enA, IMS);
  analogWrite(enB, IMS);
  
  digitalWrite(inA,HIGH);
  digitalWrite(inB,LOW);
  digitalWrite(inC,LOW);
  digitalWrite(inD,HIGH);
  flag=1;

  Serial.println("Hard Left");
}
void hardLeft()
{
  analogWrite(enA, IMS);
  analogWrite(enB, IMS);
  
  digitalWrite(inA,LOW);
  digitalWrite(inB,HIGH);
  digitalWrite(inC,HIGH);
  digitalWrite(inD,LOW);

  Serial.println("Hard Right");  
  tlag=1;
}
void Stop()
{
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  
  digitalWrite(inA,LOW);
  digitalWrite(inB,LOW);
  digitalWrite(inC,LOW);
  digitalWrite(inD,LOW);

  Serial.println("Stop");
}


void Search()
{
  readSensor();
//  pidFun();
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
//    pidFun();
    
    if(sum == 12)
    {
      if(flag==1 && tlag==0)
      {
        hardLeft();
        delay(10);
        flag=0;
        tlag=0;
        readSensor();
//        pidFun();
      }
      else if(flag==0 && tlag==1)
      {
        hardRight();
        delay(10);
        flag=0;
        tlag=0;
        readSensor();
//        pidFun();
      }
      Stop();
      delay(100);
      break;
    }
    else if(sum == 63)
    {
      Stop();
//      delay(100);
      break;
    }
  }
  readSensor();
//  pidFun();
  pidExecute();
  
  Forward();
}
