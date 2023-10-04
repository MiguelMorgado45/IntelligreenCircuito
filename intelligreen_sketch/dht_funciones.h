#ifndef DHT
#define DHT
#include <Arduino.h>
#include <DHTesp.h>
#include "DatosDht.h"

void iniciarDHT();
TempAndHumidity obtenerDatosDHT();

#endif