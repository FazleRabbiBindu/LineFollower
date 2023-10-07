//motor parameter

#define inA 4
#define inB 5
#define inC 7
#define inD 6
#define enA 3
#define enB 9

int middleValue = 500;
int sensorVal[5];

void readSensor();
void ini();
void speedControl();

void speedControl()
{
  
  for(int i=50; i<256; i=i+10)
  {      
    analogWrite(enA,i);
    analogWrite(enB,i);

    digitalWrite(inA, HIGH);
    digitalWrite(inB, LOW);
    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW);  
    delay(1000);
    
    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);
    digitalWrite(inC, LOW);
    digitalWrite(inD, LOW);  
    delay(1000);
  }
}

void ini()
{
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

void readSensor()
{
  for(int i = 0; i<5; i++)
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
void Forward()
{
    analogWrite(enA,255);
    analogWrite(enB,255);

    digitalWrite(inA, HIGH);
    digitalWrite(inB, LOW);
    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW);  
//    delay(100); 
}
void Stop()
{
    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);
    digitalWrite(inC, LOW);
    digitalWrite(inD, LOW);  
//    delay(100); 
}
void Back()
{
    analogWrite(enA,100);
    analogWrite(enB,100);

    digitalWrite(inA, LOW);
    digitalWrite(inB, HIGH);
    digitalWrite(inC, LOW);
    digitalWrite(inD, HIGH);  
//    delay(100); 
}
void check()
{
  
}
void logic()
{
//  int sum= (sensorVal[0]*10)+(sensorVal[1]*20)+(sensorVal[2]*30)+(sensorVal[3]*40)+(sensorVal[4]*50);
  if(sensorVal[2])
  {
    Forward();
  }
  else
  {
    Stop();
    check();
  }
}

void setup() {
  ini();
}

void loop() {
  readSensor();
//  speedControl();
logic();
  
}
