#define Temperatura A0
float vTemperatura = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {
  vTemperatura = analogRead(Temperatura); 
  Serial.print("Temperatura: ");
  Serial.println(vTemperatura);
  delay(200);
}
