#ifndef WIFI_FUNCIONES
#define WIFI_FUNCIONES
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "WifiData.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "humedad_tierra.h"
#include "dht_funciones.h"
#include "led_funciones.h"

//void conectarInternet();
void conectarInternet(WifiData wifiData);
void configurarMQTT();
void conectarMQTT();
void reconectarMQTT();
void callback(char* topic, byte* message, unsigned int length);
void dataLoop();

#endif