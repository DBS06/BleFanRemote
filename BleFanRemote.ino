#include <ArduinoBLE.h>
BLEService batteryService("1101");
BLEUnsignedCharCharacteristic batteryLevelChar("2101", BLERead | BLENotify);

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

    BLE.setLocalName("BatteryMonitor");
    BLE.setAdvertisedService(batteryService);
    batteryService.addCharacteristic(batteryLevelChar);
    BLE.addService(batteryService);

    BLE.advertise();
    Serial.println("Bluetooth device active, waiting for connections...");
}

void loop()
{
    BLEDevice central = BLE.central();

    if (central)
    {
        uint8_t battery = 0;
        Serial.print("Connected to central: ");
        Serial.println(central.address());
        digitalWrite(LED_BUILTIN, HIGH);

        while (central.connected())
        {

            battery++;
            int batteryLevel = map(battery, 0, 255, 0, 100);
            Serial.print("Battery Level % is now: ");
            Serial.println(batteryLevel);
            batteryLevelChar.writeValue(batteryLevel);
            delay(200);
        }
    }
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
}