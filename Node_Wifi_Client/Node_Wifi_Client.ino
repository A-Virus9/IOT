#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid = "Virus"; // Replace with your Wi-Fi SSID
const char* password = "e3r4t5y6"; // Replace with your Wi-Fi password

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello, World!");
}

void handleStatus(){
  String message = "POST request received";
//  if(server.hasArg("status")){
//    message += "\nData: " + server.arg("status");
//    }
String response = http.getString();
 StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, response);
String postbody = server.arg("plain");
message += "\nData: " + postbody;

    server.send(200, "text/plain", message);
    Serial.println(message);
    
    
//     digitalWrite(D4,HIGH);
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

  server.on("/",HTTP_GET, handleRoot);
  server.on("/status",HTTP_POST, handleStatus);
  server.begin();
}

void loop() {
  server.handleClient();
 
}
