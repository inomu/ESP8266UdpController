/*
2017/03/05　Client Program
PICからシリアルデータを受け取り，本ClientからServerに受け取ったデータを飛ばすプログラムである．
サーバからの受信は行わない．区別するのがめんどくさかったら両方できるようにしたほうがいいかも？

1.ESP Serverにアクセスする．
2.PICからのデータを送る．
3.Serverとの通信がロストすると，通信を回復するように再アクセスを行う．
*/

//atom testttt

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//Access Point Setting
const char *APSSID = "ESP_WROOM_02";
const char *APPASS = "raspberrypi";
IPAddress HostIP(192,168,4,1);
IPAddress myIP(192,168,4,2);
unsigned int localPort = 8888;

WiFiUDP UDP;
char SendData;
char packetBuffer[255];

void connectWiFi(){
  Serial.println("connectiong WiFi");
  WiFi.disconnect();
  WiFi.begin(APSSID,APPASS);
  WiFi.config(myIP, WiFi.gatewayIP(), WiFi.subnetMask());

  int cnt = 0;
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    yield();
    delay(100);
    cnt++;
    if(cnt == 50) break;
  }
  
  
}

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
  WiFi.disconnect();
  connectWiFi();
}

void loop() {

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("connection lost");
    WiFi.disconnect();
    connectWiFi();
  }else{
    Serial.print("send");
    SendData = 'E';
    SendUdp();
  }
}
