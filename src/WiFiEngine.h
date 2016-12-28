#ifndef _WIFIENGINE_H
#define _WIFIENGINE_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

class WiFiEngine {
private:
  const char* ssid     = "SSID";
  const char* password = "PASSWORD";
  const char* mimeTEXT = "text/plain";
  const char* mimeHTML = "text/html";

  float humidity, temp_f;                 // Values read from sensor
  String htmlHeader="";                   // String to display
  String htmlBodyStart="";
  String htmlBodyEnd="";
  String htmlBody="";
  String htmlFooter="";

  unsigned long previousMillis = 0;       // will store last temp was read
  const long interval = 2000;             // interval at which to read sensor

  // Private Methods
  void getDHT11Data(void);

  void handleRoot();

  void handleDHTRoot();
  void handleDHTTemp();
  void handleDHTHumidity();

  void handleHelp();

public:
  WiFiEngine();
  void StartWiFiEngine();
  void StopWiFiEngine();
  void handleTraffic();
};
#endif
