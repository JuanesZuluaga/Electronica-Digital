#define MotorDerecha 29
#define MotorIzquierda 28
#define Sensor1 33
#define Sensor2 32
#define Sensor3 31
#define Sensor4 30

int vMotorDerecha = 0;
int vMotorIzquierda = 0;
int vSensor1 = 0;
int vSensor2 = 0;
int vSensor3 = 0;
int vSensor4 = 0;
int estado = 1;
int contador = 0;

void setup() {
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);
  pinMode(Sensor4, INPUT);
  pinMode(MotorDerecha, OUTPUT);
  pinMode(MotorIzquierda, OUTPUT);

  digitalWrite(MotorDerecha, 0);
  digitalWrite(MotorIzquierda, 0);
  Serial.begin(9600);
}

void loop() {
  //Serial.println(vPotenciometro);
  vSensor1 = digitalRead(Sensor1);
  vSensor2 = digitalRead(Sensor2);
  vSensor3 = digitalRead(Sensor3);
  vSensor4 = digitalRead(Sensor4);

  Serial.println(estado);

  switch (estado) {
    case 1:
      digitalWrite(MotorDerecha, 1);
      digitalWrite(MotorIzquierda, 0);

      if (vSensor1 == 1){
        estado = 2;
        digitalWrite(MotorDerecha, 0);
        digitalWrite(MotorIzquierda, 0);
        delay(3000);
      }
      break;

    case 2:
      digitalWrite(MotorDerecha, 0);
      digitalWrite(MotorIzquierda, 1);
      if (vSensor4 == 1) {
          estado = 3;
        }
      break;

    case 3 : 
      digitalWrite(MotorIzquierda, 0);
      digitalWrite(MotorDerecha, 1);
      if (vSensor2 == 1) {
          estado = 4;
        }
      break;

      case 4:
      digitalWrite(MotorIzquierda, 1);
      digitalWrite(MotorDerecha, 0);

      if (vSensor4 == 1) {
        estado = 7;
      }
      break;

    case 5:
      digitalWrite(MotorDerecha, 0);
      digitalWrite(MotorIzquierda, 1);

      if (vSensor3 == 1) {
        estado = 6;
      }
      break;

    case 6:
      digitalWrite(MotorDerecha, 0);
      digitalWrite(MotorIzquierda, 0);

      break;
    
    case 7:
      digitalWrite(MotorIzquierda, 0);
      digitalWrite(MotorDerecha, 1);

      if(vSensor2 == 1){
        estado = 4;
        contador++;
      }
      if(contador == 3){
        estado = 5;
      }
    break;
  }
}
