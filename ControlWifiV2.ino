#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "IoT-B19";
const char* password = "lcontrol2020*";

WebServer server(80);
const int pinLed = 4;     
const int pinLed1 = 15; 
const int motorControl = 19; 
const int buttonPin1 = 12;  
const int buttonPin2 = 13;  
int motorVelocity = 55;   
int buttonState1 = HIGH; 
int buttonState2 = HIGH;

void start() {
  if (server.hasArg("led1")) {
    digitalWrite(pinLed, server.arg("led1") == "on" ? HIGH : LOW);
  }
  if (server.hasArg("led2")) {
    digitalWrite(pinLed1, server.arg("led2") == "on" ? HIGH : LOW);
  }

  String html = "<html><head>";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scaleable=no\">";
  html += "<title>Controlador Web por ESP-32</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; background-color: #f4f4f4; color: #333; margin: 0; padding: 20px; }";
  html += "h2 { color: #007BFF; }";
  html += "form { margin: 10px 0; }";
  html += "button { background-color: #007BFF; color: white; border: none; padding: 10px 20px; margin: 5px; cursor: pointer; border-radius: 5px; }";
  html += "button:hover { background-color: #0056b3; }";
  html += "input[type='range'] { width: 100%; }";
  html += "p { font-size: 1.1em; }";
  html += ".status { font-weight: bold; }";
  html += "</style>";
  html += "</head><body>";

  html += "<h2>Izquierda</h2>";
  html += "<form method='get'>";
  html += "<button type='submit' name='led1' value='on'>Prendido</button>";
  html += "<button type='submit' name='led1' value='off'>Apagado</button>";
  html += "</form>";

  html += "<h2>Derecha</h2>";
  html += "<form method='get'>";
  html += "<button type='submit' name='led2' value='on'>Prendido</button>";
  html += "<button type='submit' name='led2' value='off'>Apagado</button>";
  html += "</form>";

  html += "<h2>Velocidad del motor</h2>";
  html += "<input type='range' min='50' max='255' value='" + String(motorVelocity) + "' id='velocitySlider' onchange='updateMotorV(this.value)'>";
  html += "<p>Velocidad: <span id='VelocityLevel'>" + String(motorVelocity - 53) + "</span></p>";

  html += "<script>";
  html += "function updateMotorV(value) {";
  html += "  fetch('/updateVelocity?value=' + value);";
  html += "  document.getElementById('VelocityLevel').innerText = value;";
  html += "}";
  html += "</script>";

  html += "<h2>Estado del Boton 1</h2>";
  html += "<p>Estado: <span id='Button1' class='status'>" + String(buttonState1 == HIGH ? "OFF" : "ON") + "</span></p>";

  html += "<h2>Estado del Boton 2</h2>";
  html += "<p>Estado: <span id='Button2' class='status'>" + String(buttonState2 == HIGH ? "OFF" : "ON") + "</span></p>";

  html += "<script>";
  html += "function updateButtonStates() {";
  html += "  fetch('/updateButtons').then(response => response.json()).then(data => {";
  html += "    document.getElementById('Button1').innerText = data.button1;";
  html += "    document.getElementById('Button2').innerText = data.button2;";
  html += "  });";
  html += "}";
  html += "setInterval(updateButtonStates, 1000); // Actualiza el estado de los botones cada segundo";
  html += "</script>";
  
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void updateButtons() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  server.send(200, "application/json", "{\"button1\": \"" + String(buttonState1 == LOW ? "OFF" : "ON") + "\", \"button2\": \"" + String(buttonState2 == LOW ? "OFF" : "ON" ) + "\"}");
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
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("Conectando...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a ");
  Serial.println(ssid);
  Serial.println("IP: " + WiFi.localIP().toString());

  server.on("/", start);
  server.on("/updateButtons", updateButtons); 
  server.on("/updateVelocity", updateVelocity);
  server.begin();
}

void loop() {
  server.handleClient();
}
