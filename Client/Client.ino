/*
2017/03/05　Client Program
PICからシリアルデータを受け取り，本ClientからServerに受け取ったデータを飛ばすプログラムである．
サーバからの受信は行わない．区別するのがめんどくさかったら両方できるようにしたほうがいいかも？

1.ESP Serverにアクセスする．
2.PICからのデータを送る．
3.Serverとの通信がロストすると，通信を回復するように再アクセスを行う．
*/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//WiFi Settings
IPAddress HostIP(192,168,4,1);
IPAddress myIP(192,168,4,2);
const char *SSID = "ESP_WROOM_02";
const char *PASS = "raspberrypi";
unsigned int localPort = 8888;

//UDP settings
WiFiUDP UDP;
char SendData;

void connectWiFi(){
  WiFi.begin(SSID,PASS);
  WiFi.config(myIP,WiFi.gatewayIP(),WiFi.subnetMask());
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("connecting WiFi");
    delay(3000);
  }
  Serial.println("connected WiFi");
}

//引数型にすること．
void SendUdp(){
  if(UDP.beginPacket(HostIP,localPort) ){
    UDP.write(SendData);
    UDP.endPacket();
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  UDP.begin(localPort);
  connectWiFi();
}

void loop() {

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("connection lost");
    WiFi.disconnect();
    connectWiFi();
  }

  SendData = 'E';
  SendUdp();
}
