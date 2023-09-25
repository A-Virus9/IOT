#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "IOT_DEVICES"; // Replace with your Wi-Fi SSID
const char* password = "iot_lab_devices"; // Replace with your Wi-Fi password

ESP8266WebServer server(80);
void handleRoot() {
  server.send(200, "text/plain", "Hello, World!");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
