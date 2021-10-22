#include <NeoPixelBus.h>

const uint16_t PixelCount = 6; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 2;  // make sure to set this to the correct pin, ignored for Esp8266
const uint32_t switch_freq = 10000;
uint32_t tick = 0;

#define colorSaturation 128

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor black(0);

void pixelbar_init()
{
    strip.Begin();
    for(uint16_t i = 0; i < PixelCount; i+=2)
    {
      strip.SetPixelColor(i, red);
      strip.SetPixelColor(i+1, blue);
    }
}

void pixelbar_on()
{
    if(tick++ == switch_freq)
    {
        strip.RotateRight(1);
        strip.Show();

        tick = 0;
    }
}

void pixelbar_off()
{
    for(uint16_t i = 0; i < PixelCount; ++i)
    {
        strip.SetPixelColor(i, black);
    }
    strip.Show();
}
