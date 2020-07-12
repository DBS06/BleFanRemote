#include <ArduinoBLE.h>

BLEService fanCtrlService("1101");
BLEBooleanCharacteristic fanPower("2101", BLERead | BLEWrite | BLENotify);

struct FanCtrl
{
    bool power;
    uint8_t speed;
    bool turn;
    uint8_t state;
};

FanCtrl fanCtrl = {false, 0, false, 0};

size_t keepAlivePrevMs = 0;
size_t keepAliveIntervalMs = 500;

size_t blePrevMs = 0;
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
    BLE.setAdvertisedService(fanCtrlService);
    fanCtrlService.addCharacteristic(fanPower);
    BLE.addService(fanCtrlService);

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
            if (isIntervalOver(blePrevMs, bleIntervalMs))
            {
                fanCtrl.power = fanPower.value();
                // fanPower.writeValue(batteryLevel);
            }

            if (fanCtrl.power)
            {
                Serial.println("Power On");
                digitalWrite(LED_BUILTIN, HIGH);
            }
            else
            {
                Serial.println("Power Off");
                digitalWrite(LED_BUILTIN, LOW);
            }
        }
        // digitalWrite(LED_BUILTIN, LOW);
        if (isIntervalOver(keepAlivePrevMs, keepAliveIntervalMs))
        {
            Serial.print("Disconnected from central: ");
            Serial.println(central.address());
        }
    }
}

bool isIntervalOver(size_t prevMs, const size_t interval)
{
    bool ret = false;
    size_t curMs = millis();

    if (curMs - prevMs >= interval)
    {
        prevMs = curMs;
        ret = true;
    }

    return ret;
}