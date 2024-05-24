//ubidots 
//cont(Porcentaje de humedad)
//bomb(activar la bomba)
//bombilla(iluminar y dar calor al terrario)



#define sen 2
#define bomb 32
float vSen = 0;
int cont = 0;


void setup() {

  pinMode(bomb, OUTPUT);
  digitalWrite(bomb, HIGH);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(bomb, HIGH);
  vSen = analogRead(sen);
  cont = 100-((vSen / 4092) * 100);
  Serial.println(cont);
  delay(100);
}
