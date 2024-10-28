#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "IoT-B19";
const char* password = "lcontrol2020*";

WebServer server(80);
const int pinLed = 4;
const int pinLed1 = 15;
const int motorControl = 19;
int motorVelocity = 55;
void start(){
  if (server.hasArg("led1") && server.arg("led1") == "on"){
    digitalWrite(pinLed, HIGH);
  }
  else if (server.hasArg("led1") && server.arg("led1") == "off"){
    digitalWrite(pinLed, LOW);
  }
  if (server.hasArg("led2") && server.arg("led2") == "on"){
    digitalWrite(pinLed1, HIGH);
  }
  else if (server.hasArg("led2") && server.arg("led2") == "off"){
    digitalWrite(pinLed1, LOW);
  }
  String html = "<html><body>";
  html += "<head><meta name=\"viweport\" content=\"width=device-width, initial-scale=1.0, user-scaleable=no\">\n";
  html += "<title>Controlador Web por ESP-32</title>\n";
  html += "<h2>izquierda</h2>";
  html += "<form method='get'>";
  html += "<button type='submit' name='led1' value='on'>Prendido</button>";
  html += "<button type='submit' name='led1' value='off'>Apagado</button>";
  html += "</form>";

  html += "<h2>derecha</h2>";
  html += "<form method='get'>";
  html += "<button type='submit' name='led2' value='on'>Prendido</button>";
  html += "<button type='submit' name='led2' value='off'>Apagado</button>";
  html += "</form>";

  html += "<h2>velocidad del motor</h2>";
  html += "<input type='range' min='50' max='255' value='" + String(motorVelocity) + "' id='velocitySlider' onchange='updateMotorV(this.value)'>\n";
  html += "<p>velocidad: <span id='VelocityLevel'>" + String(motorVelocity-53) + "</span></p>";

  html += "<script>\n";
  html += "function updateMotorV(value) {\n";
  html += "  fetch('/updateVelocity?value=' + value);\n";
  html += "  document.getElementById('VelocityLevel').innerText = value;\n";
  html += "}\n";
  html += "</script>\n";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void updateVelocity() {
  if (server.hasArg("value")) {
    motorVelocity = server.arg("value").toInt();
    analogWrite(motorControl, motorVelocity);
  }
  server.send(200, "text/plain", "Current velocity: " + String(motorVelocity));
}

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinLed1, OUTPUT);
  pinMode(motorControl, OUTPUT);

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
  server.on("/updateVelocity", updateVelocity);
  server.begin();
  
}

void loop() {
  server.handleClient();

}
