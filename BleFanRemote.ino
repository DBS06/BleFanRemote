#include <ArduinoBLE.h>

#include "FanControl.h"

constexpr uint32_t pulseLengthMs = 200;
FanControl fanControl(pulseLengthMs);

size_t keepAlivePrevMs     = 0;
size_t keepAliveIntervalMs = 500;

pin_size_t powerPin      = 2;
pin_size_t speedPin      = 3;
pin_size_t turnPin       = 4;
pin_size_t timerStatePin = 5;
pin_size_t wavePin       = 6;

int ledState = LOW;

bool isIntervalOver(size_t &prevMs, const size_t interval);

static void PowerCharacteristicWrittenCb(BLEDevice central, BLECharacteristic characteristic)
{
    fanControl.setValue(fanControl.getBleCharacteristicPower(), powerPin);
    Serial.println("Power");
}

static void SpeedCharacteristicWrittenCb(BLEDevice central, BLECharacteristic characteristic)
{
    fanControl.setValue(fanControl.getBleCharacteristicSpeed(), speedPin);
    Serial.println("Speed");
}

static void TurnCharacteristicWrittenCb(BLEDevice central, BLECharacteristic characteristic)
{
    fanControl.setValue(fanControl.getBleCharacteristicTurn(), turnPin);
    Serial.println("Turn");
}

static void TimerCharacteristicWrittenCb(BLEDevice central, BLECharacteristic characteristic)
{
    fanControl.setValue(fanControl.getBleCharacteristicTimerState(), timerStatePin);
    Serial.println("Timer");
}

static void WaveCharacteristicWrittenCb(BLEDevice central, BLECharacteristic characteristic)
{
    fanControl.setValue(fanControl.getBleCharacteristicWave(), wavePin);
    Serial.println("Wave");
}

void setup()
{
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(powerPin, OUTPUT);
    pinMode(speedPin, OUTPUT);
    pinMode(turnPin, OUTPUT);
    pinMode(timerStatePin, OUTPUT);
    pinMode(wavePin, OUTPUT);

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
    fanControl.setEventHandlerWave(WaveCharacteristicWrittenCb);

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
            digitalWrite(LED_BUILTIN, HIGH);
        }

        Serial.print("Disconnected from central: ");
        Serial.println(central.address());
        digitalWrite(LED_BUILTIN, LOW);
    }

    if (isIntervalOver(keepAlivePrevMs, keepAliveIntervalMs))
    {
        if (ledState == LOW)
        {
            ledState = HIGH;
        }
        else
        {
            ledState = LOW;
        }
        digitalWrite(LED_BUILTIN, ledState);
    }
}

bool isIntervalOver(size_t &prevMs, const size_t interval)
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
