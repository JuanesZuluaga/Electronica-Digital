#define Potenciometro A0
#define Led_r 28
#define Led_a 27
#define Led_az 26
#define Led_v 25
float vPotenciometro = 0;
int vSuiche = 0;

void setup() {
  pinMode(Led_r, OUTPUT);
  pinMode(Led_a, OUTPUT);
  pinMode(Led_az, OUTPUT);
  pinMode(Led_v, OUTPUT);
  digitalWrite(Led_r, 0);
  digitalWrite(Led_a, 0);
  digitalWrite(Led_az, 0);
  digitalWrite(Led_v, 0);
  Serial.begin(9600);
}

void loop() {
  vPotenciometro = analogRead(Potenciometro);
  //Serial.println(vPotenciometro);
  if (vPotenciometro > 1 ){digitalWrite(Led_r, 1);}
  else{digitalWrite(Led_r,0);}
  if (vPotenciometro > 255 ){digitalWrite(Led_a, 1);}
  else{digitalWrite(Led_a,0);}
  if (vPotenciometro > 510 ){digitalWrite(Led_az, 1);}
  else{digitalWrite(Led_az,0);}
  if (vPotenciometro > 715 ){digitalWrite(Led_v, 1);}
  else{digitalWrite(Led_v,0);}
}
