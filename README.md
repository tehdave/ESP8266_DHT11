## Example of using an ESP8266-01 as a web server with a DHT11 Humitity / Temperature Sensor.
This is just a basic example of using the ESP8266-01 in conjunction with a DHT11 Temperature and Humidity Sensor.

## Setup
This source code project is configured to work with PlatformIO.

1: After loading the project in PlatformIO, re-initialize the project using the ESP8266 Board.  This will download and install the proper toolchain into PlatformIO  
2: Open the Library Manager and install the following libraries:  
-- pio lib install 18  
This will install the Adafruit DHT Library required to interface with the DHT11 Sensor.
