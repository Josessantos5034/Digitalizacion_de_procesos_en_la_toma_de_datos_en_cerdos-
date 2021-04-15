#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#else
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#endif

#include <MQTT.h>

const char ssid[] = "RED-111";
const char pass[] = "74241767ab";
const char ssid2[] = "";
const char pass2[] = "";
WiFiClient net;
MQTTClient client;
int led = 2;
int foco = 33;
unsigned long lastMillis = 0;
void connect() {
  Serial.print("Conectando con wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    digitalWrite(led, 0);
    delay(100);
    digitalWrite(led, 1);
    delay(100);
    Serial.print("*");
  }

  Serial.print("\nConectando con MQTT...");
  //LA DISTRIBUCION DE DATOS ES DE REPOSITORIO,INSTANCES Y CODIGO DEL TOKEN //
  while (!client.connect("Proyectos_IOT", "josesantos5034", "0OQ0zjmiW7oAs3gq")) {
    digitalWrite(led, 0);
    delay(1000);
    digitalWrite(led, 1);
    delay(1000);
    Serial.print("*");
  }

  Serial.println("\nConectado MQTT!");

  client.subscribe("/Proyecto/data");
}

void MensajeRecibido (String &topic, String &payload) {
  Serial.println("Mensaje: " + topic + " - " + payload);
  if (payload == "1") {
    digitalWrite(foco, 1);
    Serial.println("Navidad Activada");
  }
  else {
    digitalWrite(foco, 0);
    Serial.println("Navidad Desactivada");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(foco, OUTPUT);
  digitalWrite(led, 0);
  digitalWrite(foco, 0);

 Serial.println("Iniciando Wifi");
WiFi.mode(WIFI_STA);
  delay(100);
  wifiMulti.addAP("RED-111", "74241767ab");
  wifiMulti.addAP(ssid2, pass2);

  client.begin("josesantos5034.cloud.shiftr.io", net);
  client.onMessage(MensajeRecibido);

  connect();
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    connect();
  }
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
  }
}
