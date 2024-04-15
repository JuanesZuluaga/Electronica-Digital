/*  Nombre: recibirAnalogoRGBUbidotsMQTTESP32
    Autor: David Velasquez
    Fecha: 1/9/2023
    Versión: 1.0
    Descripción: Este programa recibe el valor de brillo de un led RGB
    (R: pin 27, G: pin 26, B: pin 25) desde Ubidots mediante una conexión WiFi
    y el protocolo MQTT
*/

// Librerías
#include "UbidotsEsp32Mqtt.h"  // Se requiere liberia pubsubclient https://github.com/knolleary/pubsubclient

// Etiquetado de pines de I/O
#define LEDR 27  // Etiqueto el pin 27 como LEDR
#define LEDG 26  // Etiqueto el pin 26 como LEDG
#define LEDB 25  // Etiqueto el pin 25 como LEDB

// Constantes
const char *UBIDOTS_TOKEN = "BBUS-arBhx4YEmVvAOKkqyyYskuHT4iwisy";  // Put here your Ubidots TOKEN
const char* UBIDOTS_DEVICE_LABEL = "esp32";
const char* UBIDOTS_VARIABLE1_LABEL = "led-red";
const char* UBIDOTS_VARIABLE2_LABEL = "led-g";
const char* UBIDOTS_VARIABLE3_LABEL = "led-blue";
const char *WIFI_SSID = "Redmi 10C";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "jvane704";      // Put here your Wi-Fi password

// Variables
unsigned int ledBrightnessRed = 0;    // Variable entera sin signo ledBrightnessRed para el brillo del LED rojo
unsigned int ledBrightnessGreen = 0;  // Variable entera sin signo ledBrightnessGreen para el brillo del LED verde
unsigned int ledBrightnessBlue = 0;   // Variable entera sin signo ledBrightnessBlue para el brillo del LED azul
Ubidots ubidots(UBIDOTS_TOKEN);       // Variable para enviar a Ubidots

// Subroutines and functions
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String payloadStr = (char*)payload;  // Convertir de un arreglo de bytes a un String (arreglo de chars)
  Serial.println(payloadStr);
  String topicStr = topic;
  if (topicStr.indexOf(UBIDOTS_VARIABLE1_LABEL) != -1) {
    ledBrightnessRed = payloadStr.toFloat();  // Convertir de String a Float y Mapear de 0 a 255 los valores para el PWM
    analogWrite(LEDR, ledBrightnessRed);
  } else if (topicStr.indexOf(UBIDOTS_VARIABLE2_LABEL) != -1) {
    ledBrightnessGreen = payloadStr.toFloat();  // Convertir de String a Float y Mapear de 0 a 255 los valores para el PWM
    analogWrite(LEDG, ledBrightnessGreen);
  } else if (topicStr.indexOf(UBIDOTS_VARIABLE3_LABEL) != -1) {
    ledBrightnessBlue = payloadStr.toFloat();  // Convertir de String a Float y Mapear de 0 a 255 los valores para el PWM
    analogWrite(LEDB, ledBrightnessBlue);
  }
}

void setup() {
  // Configuración de I/O
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // Limpieza de salidas
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);

  // Comunicaciones
  Serial.begin(115200);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  ubidots.subscribeLastValue(UBIDOTS_DEVICE_LABEL, UBIDOTS_VARIABLE1_LABEL);  // Suscribirse al valor de la variable 1 del device
  ubidots.subscribeLastValue(UBIDOTS_DEVICE_LABEL, UBIDOTS_VARIABLE2_LABEL);  // Suscribirse al valor de la variable 2 del device
  ubidots.subscribeLastValue(UBIDOTS_DEVICE_LABEL, UBIDOTS_VARIABLE3_LABEL);  // Suscribirse al valor de la variable 3 del device
}

void loop() {
  if (!ubidots.connected()) {  // Preguntar si se cayó la conexión y reconectar
    ubidots.reconnect();
    ubidots.subscribeLastValue(UBIDOTS_DEVICE_LABEL, UBIDOTS_VARIABLE1_LABEL);  // Suscribirse al valor de la variable 1 del device
    ubidots.subscribeLastValue(UBIDOTS_DEVICE_LABEL, UBIDOTS_VARIABLE2_LABEL);  // Suscribirse al valor de la variable 2 del device
    ubidots.subscribeLastValue(UBIDOTS_DEVICE_LABEL, UBIDOTS_VARIABLE3_LABEL);  // Suscribirse al valor de la variable 3 del device
  }
  ubidots.loop();
}
