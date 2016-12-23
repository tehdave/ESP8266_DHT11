#include <Arduino.h>
#include <WiFiEngine.h>

WiFiEngine* engine;

void setup(void) {
  Serial.begin(115200);           // Start the serial I/O so we can locally debug
}

void loop (void) {
  engine->handleTraffic();
}
