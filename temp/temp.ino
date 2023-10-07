#define IRl A0
#define IRr A1


void setup() {
  pinMode(IRl, INPUT);
  pinMode(IRr, INPUT);
  Serial.begin(9600);
}
//white 1
//black 0
void loop() {
//  delay(2000);
  int LEFT = analogRead(IRl);
  int RIGHT = analogRead(IRr);
  Serial.print("IR left: ");
  Serial.println(LEFT);
  Serial.print("IR right: ");
  Serial.println(RIGHT);
}
