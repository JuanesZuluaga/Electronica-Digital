#define Potenciometro A0
#define Suiche 37
#define Led 28
float vPotenciometro = 0;
int vSuiche = 0;
float VoltajePot; 

void setup() {
  pinMode(Suiche, INPUT);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, 0);
  Serial.begin(9600);
}

void loop() {
  vPotenciometro = analogRead(Potenciometro);
  vSuiche= digitalRead(Suiche); 
  Serial.print("Potenciometro: ");
  Serial.print(vPotenciometro);
  VoltajePot = vPotenciometro / 1023 * 5;
  Serial.print("  VoltajePot: ");
  Serial.println(VoltajePot);
  delay(200);
  if (vSuiche == 1 ){digitalWrite(Led, 1);}
  else{digitalWrite(Led,0);}
}
