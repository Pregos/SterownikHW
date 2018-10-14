#include <ESP8266WiFi.h>

#include "Private.h"

//const char* ssid = "**************";
//const char* password = "*****************";

IPAddress staticIP(192,168,80,80);
IPAddress gateway(192,168,80,1);
IPAddress subnet(255,255,255,0);

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress().c_str());
}

void loop() {}

