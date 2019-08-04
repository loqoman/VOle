#include "eepromWIFIcredlib.h"
#include <EEPROM.h>
// Needed for delay() calls
#include <Arduino.h>

bool writeWIFIcredEEPROM(char* SSID, char* PASSWD) {
    // SSID's have a maximum length of 32 bytes
    // WPA2-PSK has a size of between 8-63 bytes
    // ESP8266 has about 80KiB for user-data RAM
    // Thus, to be 100% sure we have the proper size, we only need
    // 95 bytes of Flash to reserve for EEPROM emulation
    // Assuming the ESP8266-Nodemcu 12-e has 512 KiB of flash,
    // We only need to reserve 0.00018% of flash! That's efficient!
    EEPROM.begin(EEPROMSIZE);

    // Clear everything from EEPROM 
    for (int i = 0; i < EEPROMSIZE; i++) {
        EEPROM.write(i,0);
    }

    // Store the SSID
    EEPROM.put(SSIDADDRESS,SSID);

    // Store the password
    EEPROM.put(WPA2ADDRESS,PASSWD);
    delay(100);

    // At this point all the data is stored in RAM, a seperate
    // method is needed to write it to Flash
    // TODO: Error handling for if this fails 
    EEPROM.commit();
    EEPROM.end();

}

char* readWIFIssidEEPROM() {
    // Who doesn't love dynamic memory allocation :')
    char* out;
    EEPROM.begin(EEPROMSIZE);

    // Read the SSID from EEPROM 
    EEPROM.get(SSIDADDRESS,out);

    delay(500);
    EEPROM.commit();
    EEPROM.end();

    return out;
}


char* readWIFIpassEEPROM() {
    char* out;
    EEPROM.begin(EEPROMSIZE);


    // Read the password from EEPROM
    EEPROM.get(WPA2ADDRESS,out);
    delay(500);

    EEPROM.commit();
    EEPROM.end();
    return out;
}