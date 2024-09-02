#define Ledg 24
#define Ledb 23
#define Ledr 22
#define control 37
int vControl = 0;

void setup() {
  pinMode(Ledg, OUTPUT);
  pinMode(Ledb, OUTPUT);
  pinMode(Ledr, OUTPUT);
  //vControl = digitalRead(control);
}

void tmp(int x){
  unsigned int tinicial=millis();
  unsigned int tactual=millis();
  while((tactual - tinicial) < x && digitalRead(control)==1){
    tactual=millis();
  }
}
void tmp2(int x){
  unsigned int tinicial=millis();
  unsigned int tactual=millis();
  while((tactual - tinicial) < x && digitalRead(control)==0){
    tactual=millis();
  }
}

void loop() { 
    digitalWrite(Ledg, 1);
    tmp(3000);
    digitalWrite(Ledg, 0);
    tmp(500);
    digitalWrite(Ledg, 1);
    tmp(500);
    digitalWrite(Ledg, 0);
    tmp(500);
    digitalWrite(Ledg, 1);
    tmp(500);
    digitalWrite(Ledg, 0);
    tmp(500);
    digitalWrite(Ledg, 1);
    tmp(500);
    digitalWrite(Ledg, 0);
    digitalWrite(Ledb, 1);
    tmp(1000);
    digitalWrite(Ledb, 0);
    digitalWrite(Ledr, 1);
    tmp(2000);
    digitalWrite(Ledr, 0);
  
    tmp2(500);
    digitalWrite(Ledr, 1);
    tmp2(500);
    digitalWrite(Ledr, 0);
  
}
