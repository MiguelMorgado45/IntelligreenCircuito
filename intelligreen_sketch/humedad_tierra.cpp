#include "humedad_tierra.h"

const int tierraPin = 34;
const int seco = 3368;
const int humedo = 1487;

float obtenerHumedadTierra() {
  int humedad = map(analogRead(tierraPin), humedo, seco, 100, 0);
  
  if (humedad < 0) {
    humedad = 0;
  } else if (humedad > 100) {
    humedad = 100;
  }

  return humedad;
}