volatile int  contador = 0;   // Variable entera que se almacena en la RAM del Micro
int           velpot =0;
const int     ledcal=13;
int           senalto=1023;
int           senbajo=0;

 
void setup() {
  Serial.begin(57600);
  pinMode(ledcal, OUTPUT);
  digitalWrite(ledcal,HIGH);
  attachInterrupt(0,interrupcion0,RISING);  // Interrupcion 0 (pin2) LOW, CHANGE, RISING, FALLING
  while (millis()<5000){
    velpot = analogRead (A0);
    if (velpot<senalto){
      senalto=velpot;
    }
     if (velpot>senbajo){
      senbajo=velpot;   
   }
 }
digitalWrite(ledcal,LOW);
}         
 
void loop() {
  velpot=analogRead(A0);
  int pitch = map(velpot,senbajo, senalto, 80, 1000);
 // analogWrite(9, pitch);
  
  delay(999);               // retardo de casi 1 segundo
  Serial.print(contador*(60/8)); // Como son 8 interrupciones por vuelta (contador * (60/8))
  Serial.println(" RPM");    //  El numero 8 depende del numero aspas de la helise del motor en prueba
  Serial.println(velpot);
  contador = 0;
}
 
void interrupcion0()    // Funcion que se ejecuta durante cada interrupion
{
  contador++;           // Se incrementa en uno el contador
}
