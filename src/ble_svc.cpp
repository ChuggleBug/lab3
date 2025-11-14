#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "main.h"
#include "ble_svc.h"

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer *pServer = NULL;
BLEService *pService = NULL;
BLEAdvertising *pAdvertising = NULL;
BLECharacteristic *pCharacteristic = NULL;

void AppBLECharCallbacks::onRead(BLECharacteristic *pCharacteristic) {
  String value = "Step count: " + String(stepCount);
  pCharacteristic->setValue(value.c_str());
}

void AppBLESrvCallbacks::onConnect(BLEServer *pServer) {
  Serial.println("Client connected");
}

void AppBLESrvCallbacks::onDisconnect(BLEServer *pServer) {
  Serial.println("Client disconnected");
  pServer->getAdvertising()->start();
}

void app_ble_svc_init() {
  BLEDevice::init("CS147Group5");

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new AppBLESrvCallbacks());

  pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ);
  pCharacteristic->setCallbacks(new AppBLECharCallbacks());
  pCharacteristic->setValue("Hello World");

  pService->start();

  pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}