#ifndef __BLE_SVC_H
#define __BLE_SVC_H

#include <Arduino.h>
#include <BLEDevice.h> 
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class AppBLECharCallbacks : public BLECharacteristicCallbacks {
   public:
    void onRead(BLECharacteristic *pCharacteristic) override;
};

class AppBLESrvCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) override;

    void onDisconnect(BLEServer* pServer) override;
};

void app_ble_svc_init();

#endif // __BLE_SVC_H