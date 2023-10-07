#define inA 4
#define inB 5
#define inC 6
#define inD 7
#define enA 3  //speed control
#define enB 9

//PID
int IMS = 150; //initial motor speed
int LMS = 100;
int RMS = 100;

int error = 0; 
float P=0,I=0,D=0,PID=0;
float prevErr = 0; //previous error
float prevI = 0; //previous integral
float kp = 70,kd = 120, ki = 0;//tune it

int flag=0;


int middleValue = 500;
int sensorVal[6];
int sum = 0,searchFlag=0;

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

  Serial.begin(9600);
}

void loop() {
  readSensor();
  pidFun(); //pid function
  
  sum = (sensorVal[0]*32)+(sensorVal[1]*16)+(sensorVal[2]*8)+(sensorVal[3]*4)+(sensorVal[4]*2)+(sensorVal[5]*1);
  Serial.println(sum);
  Serial.println();
  Serial.println();
  Serial.println();
  pidExecute();
  logic();
  
}


void readSensor()
{
    for(int i = 0; i<6; i++)
  {
    if(analogRead(i)>middleValue)
      sensorVal[i]=1;
    else
      sensorVal[i]=0;

    Serial.print(i);
    Serial.print('=');
    Serial.print(analogRead(i));
    Serial.print(' ');    
  }
  Serial.println();
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
  constrain(LMS,0,255);

  analogWrite(enA,RMS);
  analogWrite(enB,LMS);
}

void pidFun()
{
  if(sensorVal[0] == 1 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
  {
    error = -5;
    
  }
  else if(sensorVal[0] == 1 && sensorVal[1] == 1 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 0)
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
  else if(sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[2] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0 && sensorVal[5] == 1)
  {
    error = 5;
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
    digitalWrite(inA, HIGH);
    digitalWrite(inB, LOW);
    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW); 
    Serial.println("Forward"); 
}

void Back()
{
    analogWrite(enA,100);
    analogWrite(enB,100);

    digitalWrite(inA, LOW);
    digitalWrite(inB, HIGH);
    digitalWrite(inC, LOW);
    digitalWrite(inD, HIGH); 
    Serial.println("Backward"); 
}

//INA,INB LEFT
void softRight()
{
    analogWrite(enA,0);
    analogWrite(enB,100);

    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);
    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW);  
    Serial.println("Soft Left");
}
void softLeft()
{
    analogWrite(enA,100);
    analogWrite(enB,0);

    digitalWrite(inA, HIGH);
    digitalWrite(inB, LOW);
    digitalWrite(inC, LOW);
    digitalWrite(inD, LOW);  
    Serial.println("Soft Right");
}
void hardRight()
{
    analogWrite(enA,50);
    analogWrite(enB,50);

    digitalWrite(inA, LOW);
    digitalWrite(inB, HIGH);
    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW);  
    Serial.println("Hard Left");
}
void hardLeft()
{
    analogWrite(enA,50);
    analogWrite(enB,50);

    digitalWrite(inA, HIGH);
    digitalWrite(inB, LOW);
    digitalWrite(inC, LOW);
    digitalWrite(inD, HIGH);
    Serial.println("Hard Right");  
}
void Stop()
{
    analogWrite(enA,100);
    analogWrite(enB,100);

    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);
    digitalWrite(inC, LOW);
    digitalWrite(inD, LOW);  
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
