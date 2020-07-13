#include "FanControl.h"

FanControl::FanControl() :
    mFanCtrlService("1101"),
    mPower("2101", BLERead | BLEWrite),
    mSpeed("2102", BLERead | BLEWrite),
    mTurn("2103", BLERead | BLEWrite),
    mTimerState("2104", BLERead | BLEWrite),
    mRunTimerState(false)
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

void FanControl::setEventHandlerPower(BLECharacteristicEventHandler eventHandler)
{
    mPower.setEventHandler(BLEWritten, eventHandler);
}

void FanControl::setEventHandlerSpeed(BLECharacteristicEventHandler eventHandler)
{
    mSpeed.setEventHandler(BLEWritten, eventHandler);
}

void FanControl::setEventHandlerTurn(BLECharacteristicEventHandler eventHandler)
{
    mTurn.setEventHandler(BLEWritten, eventHandler);
}

void FanControl::setEventHandlerTimerState(BLECharacteristicEventHandler eventHandler)
{
    mTimerState.setEventHandler(BLEWritten, eventHandler);
}

BLEBooleanCharacteristic &FanControl::getBleCharacteristicPower(void)
{
    return mPower;
}

BLEBooleanCharacteristic &FanControl::getBleCharacteristicSpeed(void)
{
    return mSpeed;
}

BLEBooleanCharacteristic &FanControl::getBleCharacteristicTurn(void)
{
    return mTurn;
}

BLEBooleanCharacteristic &FanControl::getBleCharacteristicTimerState(void)
{
    return mTimerState;
}

void FanControl::setPin(BLEBooleanCharacteristic &characteristic, pin_size_t pin)
{
    if (characteristic.value())
    {
        digitalWrite(pin, HIGH);
    }
    else
    {
        digitalWrite(pin, LOW);
    }
}