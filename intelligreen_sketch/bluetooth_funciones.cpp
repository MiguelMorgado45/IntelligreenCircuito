#include "bluetooth_funciones.h"

BluetoothSerial SerialBT;

void inicializarBT() {
  encenderLeds(7);
  SerialBT.begin("IntGreen10");

  encenderLeds(8);
}

void obtenerInternet() {
  WifiData wifiData;

  if (SerialBT.available()) {
    String datos = SerialBT.readString();
    Serial.println(datos);

    int indexDelimitador = datos.indexOf('|');

    if (indexDelimitador > 0) {
      String ssid = datos.substring(0, datos.indexOf('|'));
      String password = datos.substring(datos.indexOf('|') + 1, datos.length());

      ssid.trim();
      password.trim();

      wifiData.ssid = ssid;
      wifiData.password = password;
      
      Serial.print("SSID: ");
      Serial.println(wifiData.ssid);
      Serial.print("Pass: ");
      Serial.println(wifiData.password);

      conectarInternet(wifiData);
    } else {
      Serial.println(F("Datos de internet ínvalidos"));
    }
  }
}

void pingId() {
  String id = "7e61df91-f29d-4aa6-ba34-620917b212bf";
    uint8_t buf[id.length()];
    memcpy(buf, id.c_str(), id.length());
    SerialBT.write(buf, id.length());
    Serial.println(id);
}