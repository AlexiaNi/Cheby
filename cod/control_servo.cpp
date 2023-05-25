// Import librarii
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>

const char* ssid = "Nume retea";
const char* password = "Parola";

// Conectare la webserver prin portul 80
AsyncWebServer server(80);

Servo servo_1;
Servo servo_2;

void setup() {
  // Conectare Wi-fi
  WiFi.begin(ssid, password);
  
  // Request HTTP penttru pagina html
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body style='display:flex;justify-content:center;align-items:center;font-family:fantasy;'>";
    html += "<h1>Cheby automated linkage car</h1>";
    html += "<button style='font-family:fantasy;padding:10px 20px;margin:10px;' onclick='moveServo(1)'>Forward</button>";
    html += "<button style='font-family:fantasy;padding:10px 20px;margin:10px;' onclick='moveServo(2)'>Circle</button>";
    html += "<button style='font-family:fantasy;padding:10px 20px;margin:10px;' onclick='moveServo(0)'>Stop</button>";
    html += "<script>";
    html += "function moveServo(servoId) {";
    html += "  var xhr = new XMLHttpRequest();";
    html += "  xhr.open('GET', '/move?servo=' + servoId, true);";
    html += "  xhr.send();";
    html += "}";
    html += "</script>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  // Control servo
  server.on("/move", HTTP_GET, [](AsyncWebServerRequest *request){
    int servoId = request->getParam("servo")->value().toInt();
    if (servoId == 1) {
      servo_1.attach(12);  
      servo_2.attach(14);
      servo_1.write(0);
      servo_2.write(90);
    } else if (servoId == 2) {
      servo_1.attach(12);  
      servo_2.attach(14);
      servo_1.write(90);
      servo_2.write(180);
    } else if (servoId == 0) {
      servo_1.detach();
      servo_2.detach();
    }
    request->send(200, "text/plain", "OK");
  });

  // Start server
  server.begin();
}

void loop() {
  
}
