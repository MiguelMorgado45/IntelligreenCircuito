#ifndef WIFI_FUNCIONES
#define WIFI_FUNCIONES
#include <Arduino.h>
#include <WiFi.h>
#include "WifiData.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "humedad_tierra.h"
#include "dht_funciones.h"
#include <FastLED.h>

void conectarInternet();
void conectarInternet(WifiData wifiData);
void configurarMQTT();
void conectarMQTT();
void reconectarMQTT();
void callback(char* topic, byte* message, unsigned int length);
void dataLoop();
void configurarLeds();
void encenderLeds(int estado);
void apagarLeds(int index);

#endif