#include "bluetooth_funciones.h"

BluetoothSerial SerialBT;

void inicializarBT() {
  SerialBT.begin("IntGreen0");
}

void obtenerInternet() {
  WifiData wifiData;

  if (SerialBT.available()) {
    String datos = SerialBT.readString();

    int indexDelimitador = datos.indexOf('|');

    if (indexDelimitador > 0) {
      String ssid = datos.substring(0, datos.indexOf('|'));
      String password = datos.substring(datos.indexOf('|') + 1, datos.length());

      wifiData.ssid = ssid;
      wifiData.password = password;

      conectarInternet(wifiData);
    } else {
      Serial.println(F("Datos de internet ínvalidos"));
    }
  }
}