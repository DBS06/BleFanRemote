#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include <Arduino.h>
#include <ArduinoBLE.h>

class FanControl
{
public:
    FanControl();
    FanControl(FanControl &&) = default;
    FanControl(const FanControl &) = default;
    FanControl &operator=(FanControl &&) = default;
    FanControl &operator=(const FanControl &) = default;
    ~FanControl();

    void init(void);

private:
    BLEService mFanCtrlService;
    BLEBooleanCharacteristic mFanPower;

    bool mPower;
    uint8_t mSpeed;
    bool mTurn;
    uint8_t mTimerState;
};

#endif // !FAN_CONTROL_H