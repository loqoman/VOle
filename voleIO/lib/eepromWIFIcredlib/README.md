### Consolodating some features / Functions that will be used throught multiple projects


#### EEPROM wifi credential managment

*Obj:*
    Storing wifi credentials in plain text on a public open-source website such as Github is a really, really bad idea. Insead, EEPROM can be used with build flags to set the SSID and password on certain builds when it needs to be changed.

*Psudocode:*

build flag -D BURN_WIFI 

    #ifdef BURN_WIFI

    EEPROM.read(addressSSID)
    EEPROM.read(addressPASS)

void writeWifiCred(WPA_SSID, WPA_PASSWD) {
    EEPROM.clear
    EEPROM.put(dataInProperPositions)


}