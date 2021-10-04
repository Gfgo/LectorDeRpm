#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int a=0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("EntrenadorBMX");            //nombre de dispositivo
  Serial.println("Conexion disponible");
}

void loop() {

if (SerialBT.available()) {
    SerialBT.print("Bienvenido al sistema de monitorización de entrenamiento, desea iniciar 1=si: ");
     a=Serial.write(SerialBT.read());      //recepcion de información
}  
     if (a==1){
//  if (Serial.available()) {
    //SerialBT.write(Serial.read());          //envio de informacion
    for (int i=48; i<=250; i++){
      SerialBT.write(i);
      Serial.println(i);
      delay(1000);
//      }
    }
  }
  

  delay(20);
}
