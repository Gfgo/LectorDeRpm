#define       vel 2

volatile float  contador = 0;   // Variable entera que se almacena en la RAM del Micro
int           velpot =0;
int           senalto=1023;
int           senbajo=0;
 
void setup() {
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(vel), inter, RISING);  // Interrupcion 0 (pin2) LOW, CHANGE, RISING, FALLING
  while (millis()<5000){
    velpot = analogRead (vel);
    if (velpot<senalto){
      senalto=velpot;
    }
     if (velpot>senbajo){
      senbajo=velpot;   
   }

 }

}         
 
void loop() {
  velpot=analogRead(vel);
  int pitch = map(velpot,senbajo, senalto, 80, 1000);

  
  delay(999);               // retardo de casi 1 segundo
  contador *=7.5;
  Serial.print(contador); // Como son 8 interrupciones por vuelta (contador * (60/8)=7.5)
  Serial.println(" RPM1");    //  El numero 8 depende del numero aspas de la helise del motor en prueba
  //Serial.println(velpot);
  //contador = 0;
}
 
void inter()    // Funcion que se ejecuta durante cada interrupion
{
   contador++;   // Se incrementa en uno el contador
   Serial.print(contador); 
   Serial.println(" RPM2");
}
