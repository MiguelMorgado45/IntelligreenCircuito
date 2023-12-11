#include "WiFiType.h"
#include "wifi_funciones.h"

const char* mqtt_server = "x2824759.ala.us-east-1.emqxsl.com";

const char *ca_cert =
  "-----BEGIN CERTIFICATE-----\n"
  "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n"
  "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
  "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
  "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n"
  "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
  "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n"
  "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n"
  "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n"
  "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n"
  "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n"
  "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n"
  "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n"
  "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n"
  "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n"
  "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n"
  "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n"
  "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n"
  "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n"
  "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n"
  "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n"
  "-----END CERTIFICATE-----";

WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);
long lastMsg = 0;
bool conectado = false;

/*
void conectarInternet() {
  WifiData wifiData;
  wifiData.ssid = "IZZI-D66E";
  wifiData.password = "etpRGh6G";
  conectarInternet(wifiData);
}*/

void conectarInternet(WifiData wifiData) {
  delay(10);

  int contador = 0;

  Serial.println("Conectando  a " + wifiData.ssid);

  WiFi.disconnect();
  WiFi.begin(wifiData.ssid, wifiData.password);

  while (WiFi.status()  != WL_CONNECTED) {
    contador++;
    if (contador == 10) {
      break;
    }
    encenderLeds(1);
  }
  Serial.println(WiFi.status());
  if (WiFi.status() == WL_CONNECTED) {
    encenderLeds(2);
    wifiClient.setCACert(ca_cert);
    conectarMQTT();
  } else {
    conectado = false;
    encenderLeds(3);
  }
}

void conectarMQTT() {
  mqttClient.setServer(mqtt_server, 8883);
  mqttClient.setCallback(callback);
  conectado = true;
}

void configurarMQTT() {
  if (conectado) {
    if (!mqttClient.connected()) {
      reconectarMQTT();
    }
    mqttClient.loop();

    dataLoop();
  } else {
    Serial.println("No estas conectado");
  }
  delay(5000);
}

void reconectarMQTT() {
  while(!mqttClient.connected()) {
    encenderLeds(4);
    Serial.println("Intentando conexión con MQTT");
    if (mqttClient.connect("ClienteIntelligreen","user","user")) {
      encenderLeds(5);
      mqttClient.subscribe("intelligreen/salida");
    } else {
      encenderLeds(6);
      Serial.println("Estado MQTT=");
      Serial.println(mqttClient.state());
      delay(10000);
    }
  }
}

void dataLoop() {
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    char msg[1024];
    DynamicJsonDocument doc(1024);

    TempAndHumidity dhtData = obtenerDatosDHT();
    
    doc["humedad"] = dhtData.humidity;
    doc["temperatura"] = dhtData.temperature;
    doc["humedadTierra"] =  obtenerHumedadTierra();

    serializeJson(doc, msg);
    
    mqttClient.publish("esp32/7e61df91-f29d-4aa6-ba34-620917b212bf", msg);
  } 
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.println("Llego un mensaje");
}