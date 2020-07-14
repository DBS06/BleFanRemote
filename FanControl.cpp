#include "FanControl.h"

FanControl::FanControl() :
    mFanCtrlService("1101"),
    mPower("2101", BLERead | BLEWrite | BLENotify),
    mSpeed("2102", BLERead | BLEWrite | BLENotify),
    mTurn("2103", BLERead | BLEWrite | BLENotify),
    mTimerState("2104", BLERead | BLEWrite | BLENotify),
    mWave("2105", BLERead | BLEWrite | BLENotify)
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
    mFanCtrlService.addCharacteristic(mWave);
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

void FanControl::setEventHandlerWave(BLECharacteristicEventHandler eventHandler)
{
    mWave.setEventHandler(BLEWritten, eventHandler);
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

BLEBooleanCharacteristic &FanControl::getBleCharacteristicWave(void)
{
    return mWave;
}

void FanControl::setValue(BLEBooleanCharacteristic &characteristic, pin_size_t pin)
{
    if (characteristic.value())
    {
        digitalWrite(pin, HIGH);
        delay(200);
        digitalWrite(pin, LOW);
        characteristic.writeValue(false);
    }
}