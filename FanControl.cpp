#include "FanControl.h"

FanControl::FanControl() : mFanCtrlService("1101"),
                           mFanPower("2101", BLERead | BLEWrite | BLENotify),
                           mPower(false),
                           mSpeed(0),
                           mTurn(false),
                           mTimerState(0)

{
}

FanControl::~FanControl()
{
}

void FanControl::init(void)
{
    BLE.setAdvertisedService(mFanCtrlService);
    mFanCtrlService.addCharacteristic(mFanPower);
    BLE.addService(mFanCtrlService);
}