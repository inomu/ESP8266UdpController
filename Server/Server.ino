#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//Access Point Setting
const char *APSSID = "ESP_WROOM_02";
const char *APPASS = "raspberrypi";
unsigned int localPort = 8888;

WiFiUDP UDP;
char packetBuffer[255];

static const char *udpReturnAddr = "192.168.4.2";
static const int udpReturnPort = 8889;

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.softAPdisconnect(true);
  //引数でssidを隠すことができる
  WiFi.softAP(APSSID, APPASS);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  UDP.begin(localPort);
}

void loop() {
  
  Serial.println(WiFi.softAPgetStationNum());
  delay(500);

  int packetSize = UDP.parsePacket();

  if (packetSize) {
    int len = UDP.read(packetBuffer, packetSize);
    //終端文字設定
    if (len > 0) packetBuffer[len] = '\0';
    //Serial.print(UDP.remoteIP());
    //Serial.print(" / ");
    Serial.println(packetBuffer);

    //UDP.beginPacket(udpReturnAddr, udpReturnPort);
    //UDP.write("ok");
    //UDP.endPacket();
  }

}
