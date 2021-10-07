#include "BluetoothSerial.h"
#define vel 2

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

//Variables
int seg=0;
volatile int  cont = 0;

String dato = "";                         // un string para guardar la info
bool findato = false;                     // whether the string is complete
int a=0;                                  //Seleccion de opcion

void setup() {
  //Serial.begin(115200);                   // inicio serial
  SerialBT.begin(115200);                 // inicio bluetooth
  SerialBT.println("Conexion disponible");
 // Serial.println("Conexion disponible");
  dato.reserve(200);                      //Guardo 200 bytes para datos de llegada

  pinMode(vel, INPUT);                                              //RPM
  attachInterrupt(digitalPinToInterrupt(vel), inter, RISING);
  
}
void loop() {
  SerialBT.println("hola opcion 1 o 2 -----");      //Pregunta por opcion
  //Serial.println("hola opcion 1 o 2------");
  serialEvent();
 // Serial.println(a);
  a=dato.toInt();
//Serial.println(dato);
  switch (a) {                                //seleccion de caso segun usuaio
      case 1:
        SerialBT.print("hola opcion");
        //Serial.print("hola opcion");
        for (int i=0;i<=10;i++){
//----------------------------------------------------------------------------
  SerialBT.print(seg);            //segundos
  SerialBT.print("\t");
  seg++;
  delay(999);
  cont*=7.5;                      // Como son 8 interrupciones por vuelta (contador * (60/8)=7.5)
  SerialBT.print(cont);             //  El numero 8 depende del numero aspas de la helise del motor en prueba
  SerialBT.println(" RPM");
  cont=0;
//-----------------------------------------------------------------------------          
            /*SerialBT.print(i);
            //Serial.print(i);
            delay(500);*/
            }
          a=0;
          dato="";          //limpiar el dato
          findato = false;  
          break;
      case 2:
        SerialBT.print("No valida 22");
        //Serial.print("No valida 22");
        delay(2000);
        a=0;
        dato="";          //limpiar el dato
        findato = false;
        break;
      default:
        SerialBT.print("No valida 33");
        //Serial.print("No valida 33");
        delay(2000);
        a=0;
        dato="";          //limpiar el dato
        findato = false;
        break;
  }
}

void serialEvent() {                        // Funcion para esperar datos entrados por usuario
  while (SerialBT.available()) {              //Espera por el buffer de datos
    char inChar = (char)SerialBT.read();    //Almacena dato entrante (serial normal)
    dato=inChar;                         //Almacena el dato local en variable global
    if (inChar == '\n') {                   //Si el dato que viene es nueva linea lo pone en variable para el loop
      findato = true;
    }
  }
}
//---------------------------------------------------------------------------------
void inter(){                     // Funcion que se ejecuta durante cada interrupion
  cont ++;
}
//------------------------------------------------------------------------------------
