#define vel 2

int seg=0;
volatile int  cont = 0;

void inter(){                     // Funcion que se ejecuta durante cada interrupion
  cont ++;
  
  }

void setup() {
  Serial.begin(115200);

  pinMode(vel, INPUT);
  attachInterrupt(digitalPinToInterrupt(vel), inter, RISING);
}

void loop() {
  Serial.println(seg);
  seg++;
  delay(999);
  cont*=7.5;                      // Como son 8 interrupciones por vuelta (contador * (60/8)=7.5)
  Serial.print(cont);             //  El numero 8 depende del numero aspas de la helise del motor en prueba
  Serial.println(" interrup");
  cont=0;
}
