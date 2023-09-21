#include <BluetoothSerial.h>
#include <Preferences.h>
#include <WiFi.h>
#include "models/WifiData.h"

Preferences prefs;
BluetoothSerial SerialBT;

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println(F("Intelligreen iniciando..."));
  prefs.begin("intelligreen", false);
  prefs.clear();
  inicializarBT();
}

void loop() {
  obtenerInternet();
  // put your main code here, to run repeatedly:
}

// INICIO WIFI

void conectarInternet(WifiData wifiData) {
  delay(10);

  Serial.println("Conectando  a " + wifiData.ssid);

  WiFi.begin(wifiData.ssid, wifiData.password);
}

// FIN WIFI

// INICIO BLUETOOTH
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
// FIN BLUETOOTH

