#ifdef DHT_WEB_SERVER
#include <Arduino.h>

// ESP Webserver libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   

// DHT sensor libraries
#include <DHT.h>

// EEPROM read/write lib
#include "eepromWIFIcredlib.h"
// Defines 
#define DHTPIN 4
#define DHTTYPE DHT22

// Connecting to wifi
ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();

// DHT objects + varibles
DHT dht(DHTPIN, DHTTYPE,15);

// Varibles 
float humidity;
float temperature;
char strTmp[100];

void setup(void){

  // Start the Serial communication to send messages to the computer
  Serial.begin(115200);        
  delay(10);
  Serial.println('\n');

  // If instructed, write our wifi credentials to EEPROM
  #ifdef WRITE_WIFI

  if(writeWIFIcredEEPROM("Insert_SSID","Insert_WPA2_Pass")) {
      Serial.println("EEPROM Wifi writing completed successfully!");
  }

  #endif

  // Retreiving our wifi credentials from EEPROM
  char* wifiPass = readWIFIpassEEPROM();
  char* wifiSSID = readWIFIssidEEPROM();

  // TODO: Move away from WifiMulti. On the surface level it seems unnessissary
  wifiMulti.addAP(wifiSSID, wifiPass);   // add Wi-Fi networks you want to connect to

  // Connecting to wifi
  Serial.println("\nConnecting ...");
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-F i networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  // Beginning mDNS :')
  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  // HTTP server handles
  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
  dht.begin();
  Serial.println("DHT sensor initialized");

}

void loop(void){
  server.handleClient();                    // Listen for HTTP requests from clients
}

void handleRoot() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  snprintf(strTmp, sizeof(strTmp), "Temperature in Darwin's room: %.2f C, Relative humidity in Darwin's room: %.3f percent", temperature, humidity);
  
  //void send(int code, const String& content_type, const String& content);
  server.send(200, "text/plain", strTmp);   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

#endif