#include <Preferences.h>
#include "bluetooth_funciones.h"
#include "wifi_funciones.h"

Preferences prefs;

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void setup() {
  Serial.begin(115200);

  Serial.println(F("Intelligreen iniciando..."));
  prefs.begin("intelligreen", false);
  prefs.clear();

  configurarLeds();
  iniciarDHT();
  conectarInternet();
}

void loop() {
  configurarMQTT();
}

