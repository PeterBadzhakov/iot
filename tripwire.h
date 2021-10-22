struct tripwire
{
    static const int tripwire_pin = A0;
    int connected = 0;
} tw;

void tripwire_init()
{
    tw.connected = 0;
}

int tripwire_check()
{
    tw.connected = analogRead(tripwire::tripwire_pin);
    return tw.connected;
}
