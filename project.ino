#include "pixelbar.h"
#include "udp.h"
#include "tripwire.h"
#include "bme.h"

struct sensor_data
{
    enum SENSOR_TYPE : uint8_t
    {
        WIRE = 1,
        LASER = 2
        //, CAMERA = 4
        //, ALTITUDE = 8
    };
    uint8_t tripped = 0;

} sd;

void setup()
{
    Serial.begin(115200);

    pixelbar_init();
    wifi_init();
    tripwire_init();
    //bme_init();

    if (udp.listen(9999))
    {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        udp.onPacket([](AsyncUDPPacket packet)
                     {
                         if (sd.tripped == false)
                         {
                             packet.println("No alarms.");
                         }
                         else
                         {
                             if (sd.tripped & sensor_data::SENSOR_TYPE::WIRE)
                             {
                                 packet.println("Wire tripped!");
                             }
                         }
                     });
    }
}

uint8_t check_sensors()
{
    if (tripwire_check() < 100)
    {
        sd.tripped |= sensor_data::SENSOR_TYPE::WIRE;
    }

    return sd.tripped;
}

void loop()
{
    if (check_sensors())
    {
        pixelbar_on();
    }
}
