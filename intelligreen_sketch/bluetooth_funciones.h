#ifndef BLUETOOTH_FUNCIONES
#define BLUETOOTH_FUNCIONES
#include <BluetoothSerial.h>
#include <Arduino.h>
#include "WifiData.h"
#include "wifi_funciones.h"
#include "led_funciones.h"

void inicializarBT();
void obtenerInternet();
void pingId();

#endif