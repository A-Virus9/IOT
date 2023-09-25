#include <ESP8266WiFi.h>
//void setup(){
//  Serial.begin(115200);
//  Serial.println();
//  Serial.println(WiFi.macAddress());   //print Mac Adderess
//}
// void loop(){
//}
#include <espnow.h>
uint8_t broadcastAddress[] = {0X2C,0X3A,0XE8,0X06,0XD8,0X37};
float iData1;
float iData2;
typedef struct struct_message {
    float data1;
    float data2;
} struct_message;
struct_message SendData;
struct_message RecvData;
void Send(uint8_t *a, uint8_t b) {
}
void Recv(uint8_t * c, uint8_t *d, uint8_t e) {
  memcpy(&RecvData, d, sizeof(RecvData));
  iData1 = RecvData.data1;
  iData2 = RecvData.data2;
}
void setup() {
  Serial.begin(115200);
  pinMode(D5,INPUT);
  pinMode(D8,OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  esp_now_init();
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_send_cb(Send);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_register_recv_cb(Recv);
}
 void loop() {
    SendData.data1 = digitalRead(D5);
    SendData.data2 = 1;
    esp_now_send(broadcastAddress, (uint8_t *) &SendData, sizeof(SendData));
    Serial.println(iData1);
    if(iData1==1){
      digitalWrite(D8,HIGH);
    }
    else{
      digitalWrite(D8,LOW);
    }
}
