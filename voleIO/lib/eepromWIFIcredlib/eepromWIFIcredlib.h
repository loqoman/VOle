// Headerfile for writing wifi authentication into EEPROM.
// TODO: Change how this is done, can also be posted as public-private encryption with the MAC accress of
// the physical board as the key.

// The encryped WPA2 pass can be posted to github, and decripted using the MAC address of my specific ESP.
// Main drawback is the limited use for multiple microcrontrollers which - ironically - is the main 
// ace-in-the-hole for PlatformIO. 

// I hate .h files

#define SSIDADDRESS 0
#define WPA2ADDRESS 32

#define EEPROMSIZE 96

bool writeWIFIcredEEPROM(char* SSID, char* PASSWD);

char* readWIFIssidEEPROM();

char* readWIFIpassEEPROM();