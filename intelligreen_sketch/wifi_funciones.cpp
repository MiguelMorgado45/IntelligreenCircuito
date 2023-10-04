#include "WiFiType.h"
#include "wifi_funciones.h"

#define NUM_LEDS 8
#define DATA_PIN 23

const char* mqtt_server = "192.168.1.12";


WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
CRGB leds[NUM_LEDS]; 
long lastMsg = 0;
bool conectado = false;

void conectarInternet() {
  WifiData wifiData;
  wifiData.ssid = "IZZI-D66E";
  wifiData.password = "etpRGh6G";
  conectarInternet(wifiData);
}

void conectarInternet(WifiData wifiData) {
  delay(10);

  int contador = 0;

  Serial.println("Conectando  a " + wifiData.ssid);

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
    conectarMQTT();
  } else {
    conectado = false;
    encenderLeds(3);
    delay(10000);
    conectarInternet(wifiData);
  }
}

void conectarMQTT() {
  mqttClient.setServer(mqtt_server, 1883);
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
  
}

void reconectarMQTT() {
  while(!mqttClient.connected()) {
    encenderLeds(4);
    Serial.println("Intentando conexión con MQTT");
    if (mqttClient.connect("ClienteIntelligreen")) {
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
    
    mqttClient.publish("esp32/pruebas", msg);
  } 
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.println("Llego un mensaje");
}

void configurarLeds() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
}

void encenderLeds(int estado) {
  int index;
  if (estado <= 3) {
    index = 0;
  } else if (estado <= 6) {
    index = 1;
  }

  apagarLeds(index);
  // 1 a 3 - Internet
  if (estado == 1) {
    for (int i = 0; i < 8; i++) {
      leds[i] = CRGB::Green;
      FastLED.show();
      delay(100);
    }
  }
  if (estado == 2) {
    leds[0] = CRGB::BlueViolet;
    FastLED.show();
  }
  if (estado == 3) {
    leds[0] = CRGB::Red;
    FastLED.show();
  }

  // 4 a 6 - MQTT
  if (estado == 4) {
    for (int i = 1; i < 8; i++) {
      leds[i] = CRGB::Green;
      FastLED.show();
      delay(100);
    }
  }
  if (estado == 5) {
    leds[1] = CRGB::BlueViolet;
    FastLED.show();
  }
  if (estado == 6) {
    leds[1] = CRGB::Red;
    FastLED.show();
  }
}

void apagarLeds(int index) {
  for(int i = index; i < 8; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}