#include <Arduino.h>
#include <WiFiEngine.h>

WiFiEngine engine;

void setup(void) {
  Serial.begin(115200);           // Start the serial I/O so we can locally debug
  engine.StartWiFiEngine();
}

void loop (void) {
  delay(10);
  engine.handleTraffic();
}
