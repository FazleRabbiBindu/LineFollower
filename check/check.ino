
#define inA 4
#define inB 5
#define inC 6
#define inD 7
#define enA 3
#define enB 9

int sValues[6];

void readSensor();

void readSensor()
{
  for(int i=0; i<6; i++)
  {
    if(analogRead(i)>500)
      sValues[i] = 1;
     else
      sValues[i]= 0;

    Serial.print(sValues[i]);
    Serial.print(' ');
  }
  Serial.println('\n');
  
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  readSensor();
}
