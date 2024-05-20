
#define LDR 35
int vLDR;

void setup() {
  pinMode(LDR, INPUT);
  Serial.begin(9600);
}

void loop() {
  //Leo entradas y almaceno en variables
  vLDR = analogRead(LDR);
  Serial.print("vLDR:  ");
  Serial.println(vLDR);
}
