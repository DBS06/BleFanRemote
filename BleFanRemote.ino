#include <ArduinoBLE.h>

#include "FanControl.h"

FanControl fanControl;

size_t keepAlivePrevMs     = 0;
size_t keepAliveIntervalMs = 500;

size_t blePrevMs     = 0;
size_t bleIntervalMs = 200;

bool isIntervalOver(size_t prevMs, const size_t interval);

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    pinMode(LED_BUILTIN, OUTPUT);

    if (!BLE.begin())
    {
        Serial.println("starting BLE failed!");
        while (1)
            ;
    }

    BLE.setLocalName("FanControl");
    fanControl.init();
    BLE.advertise();
    Serial.println("Bluetooth device active, waiting for connections...");
}

void loop()
{
    BLEDevice central = BLE.central();

    if (central)
    {
        Serial.print("Connected to central: ");
        Serial.println(central.address());
        digitalWrite(LED_BUILTIN, HIGH);

        while (central.connected())
        {
            fanControl.process();
        }
        if (isIntervalOver(keepAlivePrevMs, keepAliveIntervalMs))
        {
            Serial.print("Disconnected from central: ");
            Serial.println(central.address());
        }
    }
}

bool isIntervalOver(size_t prevMs, const size_t interval)
{
    bool ret     = false;
    size_t curMs = millis();

    if (curMs - prevMs >= interval)
    {
        prevMs = curMs;
        ret    = true;
    }

    return ret;
}