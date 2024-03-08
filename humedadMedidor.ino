#define pA 27
#define pB 26
#define pC 25
#define pD 32
#define pE 33
#define pF 14
#define pG 12
#define Led_r 18
#define Led_g 19
#define Led_b 21
#define sen 2
float vSen = 0;
int cont = 0;

void int2bcd(unsigned int num)  //Función que toma un numero entero y lo convierte a BCD
{
  switch (num) {
    case 0:
      digitalWrite(pA, HIGH);
      digitalWrite(pB, HIGH);
      digitalWrite(pC, HIGH);
      digitalWrite(pD, HIGH);
      digitalWrite(pE, HIGH);
      digitalWrite(pF, HIGH);
      digitalWrite(pG, LOW);
      break;

    case 1:
      digitalWrite(pA, LOW);
      digitalWrite(pB, HIGH);
      digitalWrite(pC, HIGH);
      digitalWrite(pD, LOW);
      digitalWrite(pE, LOW);
      digitalWrite(pF, LOW);
      digitalWrite(pG, LOW);
      break;

    case 2:
      digitalWrite(pA, HIGH);
      digitalWrite(pB, HIGH);
      digitalWrite(pC, LOW);
      digitalWrite(pD, HIGH);
      digitalWrite(pE, HIGH);
      digitalWrite(pF, LOW);
      digitalWrite(pG, HIGH);
      break;

    case 3:
      digitalWrite(pA, HIGH);
      digitalWrite(pB, HIGH);
      digitalWrite(pC, HIGH);
      digitalWrite(pD, HIGH);
      digitalWrite(pE, LOW);
      digitalWrite(pF, LOW);
      digitalWrite(pG, HIGH);
      break;

    case 4:
      digitalWrite(pA, LOW);
      digitalWrite(pB, HIGH);
      digitalWrite(pC, HIGH);
      digitalWrite(pD, LOW);
      digitalWrite(pE, LOW);
      digitalWrite(pF, HIGH);
      digitalWrite(pG, HIGH);
      break;

    case 5:
      digitalWrite(pA, HIGH);
      digitalWrite(pB, LOW);
      digitalWrite(pC, HIGH);
      digitalWrite(pD, HIGH);
      digitalWrite(pE, LOW);
      digitalWrite(pF, HIGH);
      digitalWrite(pG, HIGH);
      break;

    case 6:
      digitalWrite(pA, HIGH);
      digitalWrite(pB, LOW);
      digitalWrite(pC, HIGH);
      digitalWrite(pD, HIGH);
      digitalWrite(pE, HIGH);
      digitalWrite(pF, HIGH);
      digitalWrite(pG, HIGH);
      break;

    case 7:
      digitalWrite(pA, HIGH);
      digitalWrite(pB, HIGH);
      digitalWrite(pC, HIGH);
      digitalWrite(pD, LOW);
      digitalWrite(pE, LOW);
      digitalWrite(pF, LOW);
      digitalWrite(pG, LOW);
      break;

    case 8:
      digitalWrite(pA, HIGH);
      digitalWrite(pB, HIGH);
      digitalWrite(pC, HIGH);
      digitalWrite(pD, HIGH);
      digitalWrite(pE, HIGH);
      digitalWrite(pF, HIGH);
      digitalWrite(pG, HIGH);
      break;

    case 9:
      digitalWrite(pA, HIGH);
      digitalWrite(pB, HIGH);
      digitalWrite(pC, HIGH);
      digitalWrite(pD, HIGH);
      digitalWrite(pE, LOW);
      digitalWrite(pF, HIGH);
      digitalWrite(pG, HIGH);
      break;
  }
}

void setup() {
  pinMode(pA, OUTPUT);
  pinMode(pB, OUTPUT);
  pinMode(pC, OUTPUT);
  pinMode(pD, OUTPUT);
  pinMode(pE, OUTPUT);
  pinMode(pF, OUTPUT);
  pinMode(pG, OUTPUT);
  digitalWrite(pA, LOW);
  digitalWrite(pB, LOW);
  digitalWrite(pC, LOW);
  digitalWrite(pD, LOW);
  digitalWrite(pE, LOW);
  digitalWrite(pF, LOW);
  digitalWrite(pG, LOW);
  analogWrite(Led_r, 0);
  analogWrite(Led_g, 0);
  analogWrite(Led_b, 0);
  Serial.begin(9600);
}

void loop() {
  int2bcd(cont);
  vSen = analogRead(sen);
  cont = (vSen / 4092) * 10;
  Serial.println(cont);
  if (cont < 2) {
    analogWrite(Led_r, 255);
    analogWrite(Led_g, 0);
    analogWrite(Led_b, 0);
    Serial.println("Rojo");
  }

  if (cont <= 4 && cont > 2) {
    analogWrite(Led_r, 255);
    analogWrite(Led_g, 128);
    analogWrite(Led_b, 0);
    Serial.println("Naranja");
  }
  if (cont <= 6 && cont > 4) {
    analogWrite(Led_r, 255);
    analogWrite(Led_g, 201);
    analogWrite(Led_b, 14);
    Serial.println("Amarillo");
  }
  if (cont > 6) {
    analogWrite(Led_r, 0);
    analogWrite(Led_g, 255);
    analogWrite(Led_b, 0);
    Serial.println("Verde");
  }
  delay(1000);
}
