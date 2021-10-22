#include "WiFi.h"
#include "AsyncUDP.h"

const char * ssid = "router";
const char * password = "14fc5kz7bbb105";

AsyncUDP udp;

void wifi_init()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
        }
    }
}
