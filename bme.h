#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // use I2C interface
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();

void bme_init()
{
    Wire.begin(21, 22);
    bool status = bme.begin(0x76); 
}

float bme_check()
{
    sensors_event_t pressure_event;
    bme_pressure->getEvent(&pressure_event);

    return pressure_event.pressure;
}
