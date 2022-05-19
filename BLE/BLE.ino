#include "BluetoothSerial.h"                      //Envio por BLE de RPM --> Km/h 
#define vel 32                                    //D2 Wroom =IO32 mini Wroom sensor detector de las interrupciones D2 con Res=1k
#define pi 0.37699111843077518861551720599354     //pi*3/25
#define radio 0.072                               //radio de circunferencia
                                  

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define led        33  //GPIO33 Control led
Adafruit_NeoPixel pixel(1, led, NEO_GRB + NEO_KHZ800);

BluetoothSerial SerialBT;

//Variables
const float volt25=25; //GPIO25 Lectura de voltaje
float       volt=0;
float       volt2=0;

byte        rojo=0;
byte        verde=0;
byte        azul=0;

double      velo=0;
volatile int  cont = 0; /* 
int b=3;
int minu=2;              
String dato2 = "";                        // un string para guardar la info
bool findato2 = false;                                                          */
String dato = "";  
bool findato = false;                     // si el string esta completo

int a=0;                                  //Seleccion de opcion

void setup() {
  SerialBT.begin(115200);   Serial.begin(115200);        // inicio bluetooth // inicio serial
  SerialBT.begin("EntrenadorBMX");          // Nombre dispositivo
  SerialBT.println("Conexion disponible");  //Serial.println("Conexion disponible");
  //dato2.reserve(200);
  dato.reserve(200);                      //Guardo 200 bytes para datos de llegada
  pinMode(vel, INPUT);                                              //RPM
  attachInterrupt(digitalPinToInterrupt(vel), inter, RISING);
}
void loop() {
  pixel.setBrightness(10);
  SerialBT.println("Durante cuanto tiempo se va a realizar la medición ");      //Pregunta por tiempo
  //Serial.println("Durante cuanto tiempo se va a realizar la medición ");
  SerialBT.setTimeout(100);
  
  volt=analogRead(volt25);                                                      //Medicion de voltaje
  volt2=map(volt, 0, 4095, 0, 33);
  volt2/=10;
  Serial.print(volt);Serial.print('\t'); Serial.println(volt2);
  if(volt2<2.5) {
  rojo=255;
  pixel.setPixelColor(0, rojo, verde,  azul);//rojo,verde,azul 0-255
  pixel.show();
  }
   if((volt2>=2.6)&&(volt2<=2.8)) {
  rojo=255;
  verde=128;
  pixel.setPixelColor(0, rojo, verde,  azul);//rojo,verde,azul 0-255
  pixel.show();
  }
   if(volt2>=2.9) {
  verde=255;
  pixel.setPixelColor(0, rojo, verde,  azul);//rojo,verde,azul 0-255
  pixel.show();
  } 
       
  delay(500); 
  //serialEvent();
 if(SerialBT.available()){
  dato = SerialBT.readString();
  a=dato.toInt();
//  Serial.println(a);
//  Serial.println(dato);
    if(a>0){
    SerialBT.println("Inicia en: " );     //Serial.println("Inicia en: " );
    for (int i=10;i>=0;i--){            //Cuenta atras
                SerialBT.println(i);    //Serial.println(i);
                delay(999);
            }
    for (int i=0;i<=a;i++){                //AQUI ------>>>>>>>>>Hago monitoreo por a segundos<<<<<<---------72mm*0.072m
//--------------------------------------------------------------------------
            delay(999);
            cont*=7.5;                          // Como son 8 interrupciones por vuelta (contador * (60/8)=7.5)
            velo=pi*radio*cont;                     // Conversion de rpm a km/h
            velo;
            SerialBT.print(velo);    //Serial.print(velo);             //velocidad km/h BLE
            SerialBT.println(" Km/h");  //Serial.println(" Km/h");
            cont=0;
//-----------------------------------------------------------------------------          
            }
          SerialBT.println("Fin de medición.");
          a=0;
          dato="";          //limpiar el dato
          findato = false;
       }
 } 
}//Fin loop
//
//void serialEvent() {                              // Funcion para esperar datos entrados por usuario
//  while (SerialBT.available()) {                  //Espera por el buffer de datos
//    dato = SerialBT.readString();
//  }
//}
//---------------------------------------------------------------------------------
void inter(){                     // Funcion que se ejecuta durante cada interrupion
  cont ++;
}
//------------------------------------------------------------------------------------
/*
// despues de voidloop
//  SerialBT.println("Seleccione opcion (1) Medición velocidad o (2) Vacio");      //Pregunta por opcion
//  //Serial.println("Seleccione opcion (1) Medición velocidad o (2) Vacio");
//  serialEvent();
//  a=dato.toInt();
//  //Serial.println(dato);
//  switch (a) {                                //seleccion de caso segun usuaio
//      case 1:/*
//        SerialBT.println("hola durante cuantos minutos desea medir: ");
//        Serial.println("hola durante cuantos minutos desea medir: ");
//        if (Serial.available()){
//      char inCh = (char)SerialBT.read();    //Almacena dato entrante (serial normal)
//          dato2=inCh;                         //Almacena el dato local en variable global
//          if (inCh == '\n') {                   //Si el dato que viene es nueva linea lo pone en variable para el loop
//            findato2 = true;
//            }
//        }
//        b=dato2.toInt();   
//        minu=b*2;
//        delay(5000);
//        Serial.print(b);
//        Serial.print(minu);
//        SerialBT.println("Cargando configuración ");
//        Serial.println("Cargando configuración ");
//        delay(5000);
//        SerialBT.println("Inicia en: " );
//        Serial.println("Inicia en: " );
//        for (int i=10;i>=0;i--){
//            SerialBT.println(i);
//            //Serial.println(i);
//            delay(999);
//        }
//        for (int i=0;i<=20;i++){                //AQUI ------>>>>>>>>>Hago monitoreo por 10 segundos<<<<<<---------72mm*0.072m
////--------------------------------------------------------------------------
//            delay(999);
//            cont*=7.5;                        // Como son 8 interrupciones por vuelta (contador * (60/8)=7.5)
//            velo=pi*r*cont;                   // Conversion de rpm a km/h
//            velo;
//            SerialBT.print(velo);               //velocidad km/h BLE
//            SerialBT.println(" Km/h");/*
//            SerialBT.print(cont);             //  El numero 8 depende del numero aspas de la helise del motor en prueba
//            SerialBT.println(" RPM");                        
//            Serial.print(cont);
//            Serial.println(" RPM");
//            Serial.print(velo);               //velocidad km/h SERIAL
//            Serial.print("\t");
//            cont=0;
////-----------------------------------------------------------------------------          
//            }
//          a=0;
//          dato="";          //limpiar el dato
//          findato = false;
//          SerialBT.println("Fin de medición.");
//          break;
//      case 2:
//        SerialBT.print("Seleccion vacia");
//        delay(2000);
//        a=0;
//        dato="";          //limpiar el dato
//        findato = false;
//        break;
//      default:
//        SerialBT.print("Seleccion no valida");
//        delay(2000);
//        a=0;
//        dato="";          //limpiar el dato
//        findato = false;
//        break;
//  }//Fin switch*/

//void serialEvent() {                        // Funcion para esperar datos entrados por usuario
//  while (SerialBT.available()) {              //Espera por el buffer de datos
//    char inChar = (char)SerialBT.read();    //Almacena dato entrante (serial normal)
//    dato=inChar;                         //Almacena el dato local en variable global
//    if (inChar == '\n') {                   //Si el dato que viene es nueva linea lo pone en variable para el loop
//      findato = true;
//    }
//  }
//}
