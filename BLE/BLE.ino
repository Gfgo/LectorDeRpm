#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
String dato = "";                         // un string para guardar la info
bool findato = false;                     // whether the string is complete
int a=0;                                  //Seleccion de opcion

void setup() {
  Serial.begin(115200);                   // inicio serial
  SerialBT.begin(115200);                 // inicio bluetooth
  SerialBT.println("Conexion disponible");
  Serial.println("Conexion disponible");
  dato.reserve(200);                      //Guardo 200 bytes para datos de llegada
}
void loop() {
  SerialBT.println("hola opcion 1 o 2 -----");      //Pregunta po opcion
  Serial.println("hola opcion 1 o 2------");
  Serial.println(a);
  a=dato.toInt();

switch (a) {                                //seleccion de caso segun usuaio
    case 1:
    SerialBT.print("hola opcion");
    Serial.print("hola opcion");
    for (int i=0;i<=10;i++){
        SerialBT.print(i);
        Serial.print(i);
        delay(500);
        }
    a=0;  
    break;
    case 2:
      SerialBT.print("No valida 22");
      Serial.print("No valida 22");
      delay(2000);
      a=0;
      break;
    default:
      SerialBT.print("No valida 33");
      Serial.print("No valida 33");
      delay(2000);
      a=0;
      break;
      }
if (findato) {
    SerialBT.println(dato);
    dato = "";          //limpiar el dato
    findato = false;
  }
}

void serialEvent() {                        // Funcion para esperar datos entrados por usuario
  while (Serial.available()) {              //Espera por el buffer de datos
    char inChar = (char)Serial.read();    //Almacena dato entrante (serial normal)
    dato += inChar;                         //Almacena el dato local en variable global
    if (inChar == '\n') {                   //Si el dato que viene es nueva linea lo pone en variable para el loop
      findato = true;
    }
  }
}
