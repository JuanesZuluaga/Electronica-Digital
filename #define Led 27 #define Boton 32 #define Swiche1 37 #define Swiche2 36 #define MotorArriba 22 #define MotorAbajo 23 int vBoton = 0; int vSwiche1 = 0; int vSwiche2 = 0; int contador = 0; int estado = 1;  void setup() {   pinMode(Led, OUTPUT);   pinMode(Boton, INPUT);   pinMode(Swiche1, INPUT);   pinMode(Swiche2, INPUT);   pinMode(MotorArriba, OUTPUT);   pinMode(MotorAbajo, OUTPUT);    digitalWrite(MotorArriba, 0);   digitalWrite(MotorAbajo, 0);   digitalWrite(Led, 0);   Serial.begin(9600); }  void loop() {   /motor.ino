#define Led 27
#define Boton 32
#define Swiche1 37
#define Swiche2 36
#define MotorArriba 22
#define MotorAbajo 23
int vBoton = 0;
int vSwiche1 = 0;
int vSwiche2 = 0;
int contador = 0;
int estado = 1;

void setup() {
  pinMode(Led, OUTPUT);
  pinMode(Boton, INPUT);
  pinMode(Swiche1, INPUT);
  pinMode(Swiche2, INPUT);
  pinMode(MotorArriba, OUTPUT);
  pinMode(MotorAbajo, OUTPUT);

  digitalWrite(MotorArriba, 0);
  digitalWrite(MotorAbajo, 0);
  digitalWrite(Led, 0);
  Serial.begin(9600);
}

void loop() {
  //Serial.println(vPotenciometro);
  vBoton = digitalRead(Boton);
  vSwiche1 = digitalRead(Swiche1);
  vSwiche2 = digitalRead(Swiche2);

Serial.println(estado);

  switch (estado) {
    case 1:
      digitalWrite(MotorAbajo, 1);
      digitalWrite(MotorArriba, 0);
      digitalWrite(Led, 0);
      if (vSwiche2 == HIGH) {
        estado = 2;
      }
      break;
    case 2:
      digitalWrite(MotorAbajo, 0);
      digitalWrite(MotorArriba, 1);
      digitalWrite(Led, 0);
      if (vSwiche1 == HIGH) {
        estado = 1;
        contador++;
      }
      if (contador == 3) {
        estado = 3;
        contador=0;
      }
      break;
    case 3:
      digitalWrite(MotorAbajo, 0);
      digitalWrite(MotorArriba, 0);
      digitalWrite(Led, 1);
      delay(500);
      digitalWrite(Led, 0);
      delay(500);
      if (vBoton == HIGH) {
        estado = 1;
        contador = 0;
      }
      break;
  }
}
