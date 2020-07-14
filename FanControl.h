#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include <Arduino.h>
#include <ArduinoBLE.h>

class FanControl
{
public:
    FanControl(uint32_t pulseLengthMs);
    FanControl(FanControl &&)      = default;
    FanControl(const FanControl &) = default;
    FanControl &operator=(FanControl &&) = default;
    FanControl &operator=(const FanControl &) = default;
    ~FanControl();

    void init(void);
    void setEventHandlerPower(BLECharacteristicEventHandler eventHandler);
    void setEventHandlerSpeed(BLECharacteristicEventHandler eventHandler);
    void setEventHandlerTurn(BLECharacteristicEventHandler eventHandler);
    void setEventHandlerTimerState(BLECharacteristicEventHandler eventHandler);
    void setEventHandlerWave(BLECharacteristicEventHandler eventHandler);
    BLEBooleanCharacteristic &getBleCharacteristicPower(void);
    BLEBooleanCharacteristic &getBleCharacteristicSpeed(void);
    BLEBooleanCharacteristic &getBleCharacteristicTurn(void);
    BLEBooleanCharacteristic &getBleCharacteristicTimerState(void);
    BLEBooleanCharacteristic &getBleCharacteristicWave(void);
    void setValue(BLEBooleanCharacteristic &characteristic, pin_size_t pin);

private:
    BLEService mFanCtrlService;
    BLEBooleanCharacteristic mPower;
    BLEBooleanCharacteristic mSpeed;
    BLEBooleanCharacteristic mTurn;
    BLEBooleanCharacteristic mTimerState;
    BLEBooleanCharacteristic mWave;
    const uint32_t mPulseLengthMs;
};

#endif  // !FAN_CONTROL_H