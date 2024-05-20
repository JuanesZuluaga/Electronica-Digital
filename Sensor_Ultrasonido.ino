//Autores Pedro y Laura

//Sensor de ultrasonido - Ejemplo18
const int ECHOPIN = 13; // Pin para recibir el pulso del Echo
const int TRIGPIN = 14; // Pin para enviar la accion de Trigger
int distance = 0; //Variable para almacenar la distancia
void setup()
{
pinMode(ECHOPIN, INPUT);
pinMode(TRIGPIN, OUTPUT);
Serial.begin(9600);
}
void loop()
{
digitalWrite(TRIGPIN, LOW); //Apago el TRIGPIN por 2 uS
delayMicroseconds(2);
digitalWrite(TRIGPIN, HIGH); //Envio un pulso 10 uS en alto para accionar el sensor ultrasonico (realizar el trigger)
delayMicroseconds(10);
digitalWrite(TRIGPIN, LOW); //Vuelvo a apagar el pin de trigger
distance = pulseIn(ECHOPIN, HIGH); //Leo cuanto tiempo tardo en ir y volver la señal (en microsegundos)
distance = distance/58; //Calculo la distancia a la que se encuentra el objeto en cm
Serial.print("Distancia: ");
Serial.print(distance); //Imprimo serialmente la distancia a la que se encuentra el objeto
Serial.println(" cm");
delay(500);
}

