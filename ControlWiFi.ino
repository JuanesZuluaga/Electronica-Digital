#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "IoT-B19";
const char* password = "lcontrol2020*";

WebServer server(80);
const int pinLed = 4;      // LED izquierda
const int pinLed1 = 15;    // LED derecha
const int motorControl = 19; // Pin de control del motor
const int buttonPin1 = 12;  // Pin del Botón 1
const int buttonPin2 = 13;  // Pin del Botón 2
int motorVelocity = 55;      // Velocidad del motor
int buttonState1 = HIGH;     // Estado inicial del Botón 1 (OFF)
int buttonState2 = HIGH;     // Estado inicial del Botón 2 (OFF)

void start() {
  // Control de LEDs
  if (server.hasArg("led1")) {
    digitalWrite(pinLed, server.arg("led1") == "on" ? HIGH : LOW);
  }
  if (server.hasArg("led2")) {
    digitalWrite(pinLed1, server.arg("led2") == "on" ? HIGH : LOW);
  }

  // Crear la interfaz HTML
  String html = "<html><body>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scaleable=no\">\n";
  html += "<title>Controlador Web por ESP-32</title>\n";

  // Control de LEDs
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

  // Velocidad del motor
  html += "<h2>Velocidad del motor</h2>";
  html += "<input type='range' min='50' max='255' value='" + String(motorVelocity) + "' id='velocitySlider' onchange='updateMotorV(this.value)'>\n";
  html += "<p>Velocidad: <span id='VelocityLevel'>" + String(motorVelocity - 53) + "</span></p>";

  html += "<script>\n";
  html += "function updateMotorV(value) {\n";
  html += "  fetch('/updateVelocity?value=' + value);\n";
  html += "  document.getElementById('VelocityLevel').innerText = value;\n";
  html += "}\n";
  html += "</script>\n";

  // Estado del Botón 1
  html += "<h2>Estado del Boton 1</h2>";
  html += "<p>Estado: <span id='Button1'>" + String(buttonState1 == HIGH ? "OFF" : "ON") + "</span></p>";

  // Estado del Botón 2
  html += "<h2>Estado del Boton 2</h2>";
  html += "<p>Estado: <span id='Button2'>" + String(buttonState2 == HIGH ? "OFF" : "ON") + "</span></p>";

  html += "<script>\n";
  html += "function updateButtonStates() {\n";
  html += "  fetch('/updateButtons').then(response => response.json()).then(data => {\n";
  html += "    document.getElementById('Button1').innerText = data.button1;\n";
  html += "    document.getElementById('Button2').innerText = data.button2;\n";
  html += "  });\n";
  html += "}\n";
  html += "setInterval(updateButtonStates, 1000); // Actualiza el estado de los botones cada segundo\n";
  html += "</script>\n";
  
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void updateButtons() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  server.send(200, "application/json", "{\"button1\": \"" + String(buttonState1 == LOW ? "ON" : "OFF") + "\", \"button2\": \"" + String(buttonState2 == LOW ? "ON" : "OFF") + "\"}");
}

void updateVelocity() {
  if (server.hasArg("value")) {
    motorVelocity = server.arg("value").toInt();
    analogWrite(motorControl, motorVelocity); // Ajusta la velocidad del motor
  }
  server.send(200, "text/plain", "Current velocity: " + String(motorVelocity));
}

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinLed1, OUTPUT);
  pinMode(motorControl, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP); // Configurar el botón 1 con resistencia pull-up
  pinMode(buttonPin2, INPUT_PULLUP); // Configurar el botón 2 con resistencia pull-up

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
  server.on("/updateButtons", updateButtons); // Ruta para actualizar el estado de los botones
  server.on("/updateVelocity", updateVelocity); // Ruta para actualizar la velocidad
  server.begin();
}

void loop() {
  server.handleClient();
}
