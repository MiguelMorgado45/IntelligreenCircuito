#include "dht_funciones.h"

DHTesp dht;

const int dhtPin = 13;

void iniciarDHT() {
  dht.setup(dhtPin, DHTesp::DHT11);
}

TempAndHumidity obtenerDatosDHT() {
  return dht.getTempAndHumidity();;
}