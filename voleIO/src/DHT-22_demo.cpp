#ifdef DHT_SERIAL_DEMO

#include <Arduino.h>
/*
 * DHT-22 Demo
 * Reads data from a DHT-22 senor on digital pin 3,
 * and print the output to the serial monitor
 */

// Libraries
#include <DHT.h>

// Defines
#define DHTPIN 4
#define DHTTYPE DHT22

// Creating DHT Object
DHT dht(DHTPIN, DHTTYPE,15);

// Varibles 
float humidity;
float temperature;

void setup() {
  Serial.begin(115200);
  dht.begin();

}
void loop() {
     delay(2000); // Delay 2 sec.
    //Read data and store it to variables hum and temp
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Temp: ");
    Serial.println(temperature);
    Serial.print(" Celsius");
    // delay(10000);

}
#endif