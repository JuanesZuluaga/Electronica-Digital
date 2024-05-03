/******************************************
 *
 * This example works for both Industrial and STEM users.
 *
 * Developed by Jose Garcia, https://github.com/jotathebest/
 *
 * ****************************************/

/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsEsp32Mqtt.h"


#define LED 2
#define POT 34

const char *UBIDOTS_TOKEN = "BBUS-arBhx4YEmVvAOKkqyyYskuHT4iwisy";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "Redmi 10C";                                // Put here your Wi-Fi SSID
const char *WIFI_PASS = "jvane704";                                 // Put here your Wi-Fi password
const char *PUBLISH_DEVICE_LABEL = "esp";                           // Put here your Device label to which data  will be published
const char *PUBLISH_VARIABLE_LABEL = "potenciometro";               // Put here your Variable label to which data  will be published
const char *SUBSCRIBE_DEVICE_LABEL = "esp";                         // Replace with the device label to subscribe to
const char *SUBSCRIBE_VARIABLE_LABEL = "led";                       // Replace with the variable label to subscribe to



const int PUBLISH_FREQUENCY = 5000;  // Update rate in millisecondsx

unsigned long timer;
uint8_t analogPin = 34;  // Pin used to read data from GPIO34 ADC_CH6.

Ubidots ubidots(UBIDOTS_TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/
void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String topicStr = topic;
  String payloadStr = (char *)payload;
  Serial.println(payloadStr);
  if (topicStr.indexOf("/esp/led") != -1) {
    analogWrite(LED, payloadStr.toInt() * 255 / 100);
  }



  /****************************************
 * Main Functions
 ****************************************/

  void setup() {
    pinMode(LED, OUTPUT);
    pinMode(POT, INPUT);
      // put your setup code here, to run once:
      Serial.begin(115200);
    // ubidots.setDebug(true);  // uncomment this to make debug messages available
    ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
    ubidots.setCallback(callback);
    ubidots.setup();
    ubidots.reconnect();
    ubidots.subscribeLastValue(SUBSCRIBE_DEVICE_LABEL, SUBSCRIBE_VARIABLE_LABEL);  // Insert the device and variable's Labels, respectively

    timer = millis();
  }

  void loop() {

    // put your main code here, to run repeatedly:
    if (!ubidots.connected()) {
      ubidots.reconnect();
      ubidots.subscribeLastValue(SUBSCRIBE_DEVICE_LABEL, SUBSCRIBE_VARIABLE_LABEL);  // Insert the device and variable's Labels, respectively
    }
    if ((millis() - timer) > PUBLISH_FREQUENCY)  // triggers the routine every 5 seconds
    {
      float value = analogRead(POT) * 100 / 4095;
      ubidots.add(PUBLISH_VARIABLE_LABEL, value);  // Insert your variable Labels and the value to be sent
      ubidots.publish(PUBLISH_DEVICE_LABEL);
      timer = millis();
    }

    ubidots.loop();
  }
