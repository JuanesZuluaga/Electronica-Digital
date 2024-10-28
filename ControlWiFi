#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "IoT-B19";
const char* password = "lcontrol2020*";

WebServer server(80);
const int pinLed = 2;

void start(){
  if (server.hasArg("led1") && server.arg("led1") == "on"){
    digitalWrite(pinLed, HIGH);
  }
  else if (server.hasArg("led1") && server.arg("led1") == "off"){
    digitalWrite(pinLed, LOW);
  }
  String html = "<html><body>";
  html =+ "<head><meta name=\"viweport\" content=\"width=device-width, initial-scale=1.0, user-scaleable=no\">\n";
  html =+ "<title>Controlador Web por ESP-32</title>\n";
  html =+ "<from method='get'>";
  html =+ "<button type='submit' name='led1' value='on'>Prendido</button>";
  html =+ "<button type='submit' name='led1' value='off'>Apagado</button>";
  html =+ "</form>";
  html =+ "</body></html>";
  server.send(200, "text/html", html);
}
void setup() {
  pinMode(pinLed, OUTPUT);

  Serial.begin(115200);
  Serial.println("conectando...");
  Serial.print(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("conectado a ");
  Serial.println(ssid);
  Serial.println("Conectado a "+ WiFi.localIP().toString());
  server.on("/", start);
  server.begin();
  
}

void loop() {
  server.handleClient();

}
