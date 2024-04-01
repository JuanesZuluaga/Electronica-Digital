#define Mode1 37
#define Mode2 36
#define Mode3 35
#define Led 22
#define Motor 7
int vMode1 = 0;
int vMode2 = 0;
int vMode3 = 0;

  void setup() {
  pinMode(Mode1, INPUT);
  pinMode(Mode2, INPUT);
  pinMode(Mode3, INPUT);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, 0);
  analogWrite(Motor, 0);
  Serial.begin(9600);
}

void loop() {
  vMode1 = digitalRead(Mode1);
  vMode2 = digitalRead(Mode2);
  vMode3 = digitalRead(Mode3);   
  if (vMode1 == 1 && vMode2 == 0 && vMode3 == 0) {
    analogWrite(Motor, 85);
    Serial.println("Motor  1/3");
  } else {
    if (vMode1 == 0 && vMode2 == 1 && vMode3 == 0) {
      analogWrite(Motor, 170);
      Serial.println("Motor  2/3");
    } else {
      if (vMode1 == 0 && vMode2 == 0 && vMode3 == 1) {
        analogWrite(Motor, 255);
        Serial.println("Motor  full");

      } else {
        analogWrite(Motor, 0);
        Serial.println("Motor  apagado");
        digitalWrite(Led, 1);
        Serial.println("Led on");
        delay(1000);
        digitalWrite(Led, 0);
        Serial.println("Led off");
        delay(1000);
      }
    }
  }
}
