#define       vel 27
int           cont=0;
int           senalto=1023;
int           senbajo=0;


void setup() {
  Serial.begin(115200);
  pinMode(vel, INPUT);
  attachInterrupt(vel, inerrupcion, RISING);
}

void loop() {
  Serial.println(cont);
 // Serial.println(vel);
  cont++;
  delay(200);
}

void inerrupcion (){
  Serial.println ("Interrupción");
  Serial.println(vel);
}
