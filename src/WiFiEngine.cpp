#include <WiFiEngine.h>

#define DHTTYPE DHT11
#define DHTPIN  2

ESP8266WebServer server(80);
DHT dht(DHTPIN, DHTTYPE, 11);

WiFiEngine::WiFiEngine() {
  // While we're here, build the majority of the html
  htmlHeader = "<!DOCTYPE html>\n";
  htmlHeader+= "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n";
  htmlHeader+= "    <head>\n";
  htmlHeader+= "        <title>title</title>\n";
  htmlHeader+= "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\n";
  htmlHeader+= "        <script src=\"http://code.jquery.com/jquery-1.11.1.min.js\"></script>\n";
  htmlHeader+= "        <script src=\"http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js\"></script>\n";
  htmlHeader+= "        <link href=\"http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css\" rel=\"stylesheet\"/>\n";
  htmlHeader+= "    </head>\n";

  htmlBodyStart = "    <body>\n";
  htmlBodyStart+= "        <div data-role=\"page\" id=\"page1\">\n";
  htmlBodyStart+= "            <div data-role=\"header\" id=\"hdrSiteHeader\">\n";
  htmlBodyStart+= "                <h1>ESP8266 WebServer</h1>\n";
  htmlBodyStart+= "            </div>\n";
  htmlBodyStart+= "            <div data-role=\"content\">\n";

  htmlBodyEnd = "            </div>\n";
  htmlBodyEnd+= "        </div>\n";
  htmlBodyEnd+= "    </body>\n";
  htmlBodyEnd+= "</html>";

  htmlFooter += "";
 }

void WiFiEngine::StartWiFiEngine(void) {
  // Set the ESP8266 to STATION MODE.
  WiFi.mode(WIFI_STA);

  // Connect as soon as we are created.
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print out some info on the Serial Line if we're connected.
  Serial.println("");
  Serial.println("WiFi connected to WIFI AP: "+(String)ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Setting endpoint handlers...");
  // Handlers for endpoints.
  server.on("/", std::bind(&WiFiEngine::handleRoot, this));             // Handle /
  server.on("/dht", std::bind(&WiFiEngine::handleDHTRoot, this));
  server.on("/dht/temp", std::bind(&WiFiEngine::handleDHTTemp, this));         // Handle /temp
  server.on("/dht/humi", std::bind(&WiFiEngine::handleDHTHumidity, this));     // Handle /humi
  server.on("/help", std::bind(&WiFiEngine::handleHelp, this));         // Handle /help
  Serial.println("Endpoint handlers set...");
  server.begin();
}

void WiFiEngine::handleRoot(void) {
  htmlBody = "                <div class=\"ui-grid-a\">\n";
  htmlBody+= "                </div>\n";

  server.send(200, mimeHTML, htmlHeader+htmlBodyStart+htmlBody+htmlBodyEnd+htmlFooter);
}

void WiFiEngine::handleDHTRoot(void) {
    getDHT11Data();

    htmlBody = "                <div class=\"ui-grid-a\">\n";
    htmlBody+= "                    <div class=\"ui-block-a\">\n";
    htmlBody+= "                        <span id=\"lblTemperature\">Current Temperature:</span>\n";
    htmlBody+= "                    </div>\n";
    htmlBody+= "                    <div class=\"ui-block-b\">\n";
    htmlBody+= "                        <span id=\"txtTemperature\">"+(String)temp_f+" F</span>\n";
    htmlBody+= "                    </div>\n";
    htmlBody+= "                    <div class=\"ui-block-a\">\n";
    htmlBody+= "                        <span id=\"lblHumidity\">Current Humidity:</span>\n";
    htmlBody+= "                    </div>\n";
    htmlBody+= "                    <div class=\"ui-block-b\">\n";
    htmlBody+= "                        <span id=\"txtHumidity\">"+(String)humidity+" %</span>\n";
    htmlBody+= "                    </div>\n";
    htmlBody+= "                </div>\n";

    server.send(200, mimeHTML, htmlHeader+htmlBodyStart+htmlBody+htmlBodyEnd+htmlFooter);
}

void WiFiEngine::handleDHTTemp(void) {
  getDHT11Data();

  htmlBody = "                <div class=\"ui-grid-a\">\n";
  htmlBody+= "                    <div class=\"ui-block-a\">\n";
  htmlBody+= "                        <span id=\"lblTemperature\">Current Temperature:</span>\n";
  htmlBody+= "                    </div>\n";
  htmlBody+= "                    <div class=\"ui-block-b\">\n";
  htmlBody+= "                        <span id=\"txtTemperature\">"+(String)temp_f+" F</span>\n";
  htmlBody+= "                    </div>\n";
  htmlBody+= "                </div>\n";

  server.send(200, mimeHTML, htmlHeader+htmlBodyStart+htmlBody+htmlBodyEnd+htmlFooter);
}

void WiFiEngine::handleDHTHumidity(void) {
  getDHT11Data();

  htmlBody = "                <div class=\"ui-grid-a\">\n";
  htmlBody+= "                    <div class=\"ui-block-a\">\n";
  htmlBody+= "                        <span id=\"lblHumidity\">Current Humidity:</span>\n";
  htmlBody+= "                    </div>\n";
  htmlBody+= "                    <div class=\"ui-block-b\">\n";
  htmlBody+= "                        <span id=\"txtHumidity\">"+(String)humidity+" %</span>\n";
  htmlBody+= "                    </div>\n";
  htmlBody+= "                </div>\n";

  server.send(200, mimeHTML, htmlHeader+htmlBodyStart+htmlBody+htmlBodyEnd+htmlFooter);
}

void WiFiEngine::handleHelp(void) {
  getDHT11Data();

  server.send(200, mimeTEXT, "Help Goes Here.");
}

void WiFiEngine::getDHT11Data(void) {
  // Wait at least 2 seconds seconds between measurements.
  // if the difference between the current time and last time you read
  // the sensor is bigger than the interval you set, read the sensor
  // Works better than delay for things happening elsewhere also
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor
    previousMillis = currentMillis;

    // Reading temperature for humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    humidity = dht.readHumidity();          // Read humidity (percent)
    temp_f = dht.readTemperature(true);     // Read temperature as Fahrenheit
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temp_f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}

void WiFiEngine::handleTraffic(void) {
  server.handleClient();
}
