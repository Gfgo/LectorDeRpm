#include "BluetoothSerial.h"
#define vel 2

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

//Variables
int seg=0;
int b=3;
int minu=2;
volatile int  cont = 0; /*               
String dato2 = "";                        // un string para guardar la info
bool findato2 = false;                                                          */
String dato = "";  
bool findato = false;                     // si el string esta completo

int a=0;                                  //Seleccion de opcion

void setup() {
  SerialBT.begin(115200);                   // inicio bluetooth
  SerialBT.begin("EntrenadorBMX");
  SerialBT.println("Conexion disponible");/*
  Serial.begin(115200);                     // inicio serial
  Serial.println("Conexion disponible");
  dato2.reserve(200);*/
  dato.reserve(200);                      //Guardo 200 bytes para datos de llegada
  
  pinMode(vel, INPUT);                                              //RPM
  attachInterrupt(digitalPinToInterrupt(vel), inter, RISING);
  
}
void loop() {
  SerialBT.println("Seleccione opcion (1) Medición velocidad o (2) Vacio");      //Pregunta por opcion
  //Serial.println("Seleccione opcion (1) Medición velocidad o (2) Vacio");
  serialEvent();
  a=dato.toInt();
  //Serial.println(dato);
  switch (a) {                                //seleccion de caso segun usuaio
      case 1:/*
        SerialBT.println("hola durante cuantos minutos desea medir: ");
        Serial.println("hola durante cuantos minutos desea medir: ");
        if (Serial.available()){
      char inCh = (char)SerialBT.read();    //Almacena dato entrante (serial normal)
          dato2=inCh;                         //Almacena el dato local en variable global
          if (inCh == '\n') {                   //Si el dato que viene es nueva linea lo pone en variable para el loop
            findato2 = true;
            }
        }
        b=dato2.toInt();   
        minu=b*2;
        delay(5000);
        Serial.print(b);
        Serial.print(minu);
        SerialBT.println("Cargando configuración ");
        Serial.println("Cargando configuración ");
        delay(5000);*/
        SerialBT.println("Inicia en: " );
        Serial.println("Inicia en: " );
        for (int i=10;i>=0;i--){
            SerialBT.println(i);
            Serial.println(i);
            delay(999);
        }
        for (int i=0;i<=20;i++){                //AQUI ------>>>>>>>>>Hago monitoreo por 10 segundos<<<<<<---------
//----------------------------------------------------------------------------
            SerialBT.print(seg);            //segundos
            SerialBT.print("\t");
            seg++;
            delay(999);
            cont*=7.5;                        // Como son 8 interrupciones por vuelta (contador * (60/8)=7.5)
            SerialBT.print(cont);             //  El numero 8 depende del numero aspas de la helise del motor en prueba
            SerialBT.println(" RPM");
            Serial.print(cont);
            Serial.println(" RPM");
            cont=0;
//-----------------------------------------------------------------------------          
            }
          a=0;
          dato="";          //limpiar el dato
          findato = false;
          SerialBT.println("Fin de medición.");
          break;
      case 2:
        SerialBT.print("Seleccion vacia");
        delay(2000);
        a=0;
        dato="";          //limpiar el dato
        findato = false;
        break;
      default:
        SerialBT.print("Seleccion no valida");
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
