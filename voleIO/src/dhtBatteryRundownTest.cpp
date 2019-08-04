#ifdef RUNDOWN_TEST
#include <Arduino.h>
// ESP Webserver libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// MQTT Libraries
#include <PubSubClient.h>

// DHT sensor libraries
#include <DHT.h>

// Defines 
#define DHTPIN 4
#define DHTTYPE DHT22

/************************* WiFi Access Point *********************************/ 
#define WLAN_SSID       "Your_SSID" 
#define WLAN_PASS       "Your_Pass" 
#define MQTT_SERVER      "192.168.0.42"  // give static address
#define MQTT_PORT         1883                    
#define MQTT_USERNAME    "" 
#define MQTT_PASSWORD         "" 
// Create an ESP8266 WiFiClient class to connect to the MQTT server. 
WiFiClient espClient; 
PubSubClient client(espClient);
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
/*************************** Sketch Code ************************************/ 

// DHT objects + varibles
DHT dht(DHTPIN, DHTTYPE,15);

// Varibles 
float humidity;
float temperature;
char strTmp[100];

void setup(void){
  // starting DHT sensor
  dht.begin();

  Serial.begin(115200); 
  delay(10); 
  Serial.println(F("RPi-ESP-MQTT")); 
  // Connect to WiFi access point. 
  Serial.println(); Serial.println(); 
  Serial.print("Connecting to "); 
  Serial.println(WLAN_SSID); 
  WiFi.begin(WLAN_SSID, WLAN_PASS); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  } 
  Serial.println(); 
  Serial.println("WiFi connected"); 
  Serial.println("IP address: "); Serial.println(WiFi.localIP()); 
  // Setup MQTT subscription for esp8266_led feed. 

}

void loop(void){
  // Ensure the connection to the MQTT server is alive (this will make the first 
  // connection and automatically reconnect when disconnected).  See the MQTT_connect 

}

#endif