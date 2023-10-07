#define inA 4
#define inB 5
#define inC 7
#define inD 6
#define enA 3  //speed control
#define enB 9

int middleValue = 500;
int sensorVal[6];
int sum = 0;

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
  sum = (sensorVal[0]*32)+(sensorVal[1]*16)+(sensorVal[2]*8)+(sensorVal[3]*4)+(sensorVal[4]*2)+(sensorVal[5]*1);
}


void readSensor()
{
    for(int i = 0; i<6; i++)
  {
    if(analogRead(i)>middleValue)
      sensorVal[i]=1;
    else
      sensorVal[i]=0;

    Serial.print(sensorVal[i]);
    Serial.print('=');
    Serial.print(analogRead(i));
    Serial.print(' ');    
  }
  Serial.println();
}


void logic()
{
  if(sum == 12|| sum == 51)//while black or white stripe 
  {
    Forward();
  }
  else if(sum == 63)//while full black (T)
  {
    Stop();
    
  }
  else if(sum == 0) //while full white
  {
    Search();
  }
  else if(sum == 15)//right
  {
    softRight();
  }
  else if(sum == 60) //left
  {
    softLeft();
  }
  else if(sum == 13)//right angle
  {
    while(sum != 0)
    {
      Forward(); 
    }
    
    Stop();
    delay(500);
    
    while(sum == 0)
    {
      softRight(); 
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
    
    while(sum == 0)
    {
      softLeft(); 
    }
  }
  else
  {
    Stop();
  }
}


void Forward()
{
    analogWrite(enA,200);
    analogWrite(enB,200);

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
    analogWrite(enA,255);
    analogWrite(enB,255);

    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);
    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW);  
    Serial.println("Soft Left");
}
void softLeft()
{
    analogWrite(enA,255);
    analogWrite(enB,255);

    digitalWrite(inA, HIGH);
    digitalWrite(inB, LOW);
    digitalWrite(inC, LOW);
    digitalWrite(inD, LOW);  
    Serial.println("Soft Right");
}
void hardRight()
{
    analogWrite(enA,255);
    analogWrite(enB,255);

    digitalWrite(inA, LOW);
    digitalWrite(inB, HIGH);
    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW);  
    Serial.println("Hard Left");
}
void hardLeft()
{
    analogWrite(enA,255);
    analogWrite(enB,255);

    digitalWrite(inA, HIGH);
    digitalWrite(inB, LOW);
    digitalWrite(inC, LOW);
    digitalWrite(inD, HIGH);
    Serial.println("Hard Right");  
}
void Stop()
{
    analogWrite(enA,255);
    analogWrite(enB,255);

    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);
    digitalWrite(inC, LOW);
    digitalWrite(inD, LOW);  
    Serial.println("Stop");
}
void Search()
{
  Serial.println("Searching");
}
