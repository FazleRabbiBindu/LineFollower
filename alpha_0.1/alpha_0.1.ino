//motor parameter

#define inA 4
#define inB 5
#define inC 6
#define inD 7
#define enA 3
#define enB 9

int leftBaseSpeed = 170;
int rigntBaseSpeed = 170;
int MaxSpeed = 255;

//sensor parameter 

#define NUM_SENSORS 5

int centralValue[NUM_SENSORS]={500,500,500,500,500};
int sValues[NUM_SENSORS],lastSensor

//PID PARAMETER

float kp = 5;
float kd = 5;
int prevError;

void initialize();
void lineFollow();
int readSensor();
void wheel();

void initialize()
{
  pinMode(inA,OUTPUT);
  pinMode(inB,OUTPUT);
  pinMode(inC,OUTPUT);
  pinMode(inD,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);

  digitalWrite(inA, LOW);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, LOW);

  lastSensor = 0;
  prevError = 0;
  Serial.begin(9600);
  Serial.println("Initialization activeted");
}

int readSensor()
{
  for(int i=0; i<NUM_SENSORS; i++)
  {
    if(analogRead(i)>centralValue[i])
      sValues[i] = 0;
     else
      sValues[i]= 1;

    Serial.print(analogRead(i));
    Serial.print(' ');
  }
  Serial.println('\n');
  
  int error, sumS, sumWS, linePos;
  sumS = sValues[0]+sValues[1]+sValues[2]+sValues[3]+sValues[4];
}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
