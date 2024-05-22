#define sen A12
float vSen = 0;
int cont = 0;

void int2bcd(unsigned int num)  //Función que toma un numero entero y lo convierte a BCD
{
  
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  int2bcd(cont);
  vSen = analogRead(sen);
  cont = (vSen / 4092) * 10;
  Serial.println(cont);
}
