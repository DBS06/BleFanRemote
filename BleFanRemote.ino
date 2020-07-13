#include <ArduinoBLE.h>

#include "FanControl.h"

FanControl fanControl;

size_t keepAlivePrevMs     = 0;
size_t keepAliveIntervalMs = 500;

size_t blePrevMs     = 0;
size_t bleIntervalMs = 200;

pin_size_t powerPin      = 2;
pin_size_t speedPin      = 3;
pin_size_t turnPin       = 4;
pin_size_t timerStatePin = 5;

bool isIntervalOver(size_t prevMs, const size_t interval);

static void PowerCharacteristicWrittenCb(BLEDevice central, BLECharacteristic characteristic)
{
    fanControl.setPin(fanControl.getBleCharacteristicPower(), powerPin);
    if (fanControl.getBleCharacteristicPower().value())
    {
        Serial.println("Power On");
    }
    else
    {
        Serial.println("Power Off");
    }
}

static void SpeedCharacteristicWrittenCb(BLEDevice central, BLECharacteristic characteristic)
{
    fanControl.setPin(fanControl.getBleCharacteristicSpeed(), speedPin);
    if (fanControl.getBleCharacteristicSpeed().value())
    {
        Serial.println("Speed On");
    }
    else
    {
        Serial.println("Speed Off");
    }
}

static void TurnCharacteristicWrittenCb(BLEDevice central, BLECharacteristic characteristic)
{
    fanControl.setPin(fanControl.getBleCharacteristicTurn(), turnPin);
    if (fanControl.getBleCharacteristicTurn().value())
    {
        Serial.println("Turn On");
    }
    else
    {
        Serial.println("Turn Off");
    }
}

static void TimerCharacteristicWrittenCb(BLEDevice central, BLECharacteristic characteristic)
{
    fanControl.setPin(fanControl.getBleCharacteristicTimerState(), timerStatePin);
    if (fanControl.getBleCharacteristicTimerState().value())
    {
        Serial.println("Timer On");
    }
    else
    {
        Serial.println("Timer Off");
    }
}

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(powerPin, OUTPUT);
    pinMode(speedPin, OUTPUT);
    pinMode(turnPin, OUTPUT);
    pinMode(timerStatePin, OUTPUT);

    if (!BLE.begin())
    {
        Serial.println("starting BLE failed!");
        while (1)
            ;
    }

    BLE.setLocalName("FanControl");
    fanControl.init();
    fanControl.setEventHandlerPower(PowerCharacteristicWrittenCb);
    fanControl.setEventHandlerSpeed(SpeedCharacteristicWrittenCb);
    fanControl.setEventHandlerTurn(TurnCharacteristicWrittenCb);
    fanControl.setEventHandlerTimerState(TimerCharacteristicWrittenCb);

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

        while (central.connected())
        {
            // fanControl.process();
            digitalWrite(LED_BUILTIN, HIGH);
            // delay(10);
        }

        if (isIntervalOver(keepAlivePrevMs, keepAliveIntervalMs))
        {
            Serial.print("Disconnected from central: ");
            Serial.println(central.address());
        }
        digitalWrite(LED_BUILTIN, LOW);
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
