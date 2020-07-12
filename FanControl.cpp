#include "FanControl.h"

FanControl::FanControl() :
    mFanCtrlService("1101"),
    mPower("2101", BLERead | BLEWrite),
    mSpeed("2102", BLERead | BLEWrite),
    mTurn("2103", BLERead | BLEWrite),
    mTimerState("2104", BLERead | BLEWrite)
{
}

FanControl::~FanControl()
{
}

void FanControl::init(void)
{
    BLE.setAdvertisedService(mFanCtrlService);
    mFanCtrlService.addCharacteristic(mPower);
    mFanCtrlService.addCharacteristic(mSpeed);
    mFanCtrlService.addCharacteristic(mTurn);
    mFanCtrlService.addCharacteristic(mTimerState);
    BLE.addService(mFanCtrlService);
}

void FanControl::process(void)
{
    if (mPower.value())
    {
        // Serial.println("Power On");
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
        // Serial.println("Power Off");
        digitalWrite(LED_BUILTIN, LOW);
    }
}