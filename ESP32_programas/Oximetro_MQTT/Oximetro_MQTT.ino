#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <WiFi.h>
#include <PubSubClient.h>

#define TIEMPO_ENTRE_REPORTE 1000

const char* ssid = "Megacable-72B0"; //cambiar a la red que se usara
const char* password = "VmN7qgZS5N"; //cambiar a la red que se usara
const char* mqttServer = "192.168.1.74"; //cambiar a la ip del mqtt
const int mqttPort = 1883; //puerto que esta configurado desde el broker mqtt
const char* mqttUser = "sato"; //usuario dado de alta en el broker mqtt
const char* mqttPassword = "2301"; // password del broker mqtt
uint32_t ultimo_reporte = 0;

WiFiClient espClient;
PubSubClient client(espClient);
PulseOximeter pox;

void enPulsoDetectado() {
    Serial.println("Latido detectado!");
}

void reconectarMQTT() {
  if (!client.connected()) {
    while (!client.connected()) {
    Serial.println("Intentando reconectar a MQTT...");
      if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
        Serial.println("Reconectado!");
      } else {
        Serial.print("Falló la reconexión. Estado: ");
        Serial.println(client.state());
        delay(2000);
      }
    }
  }
}
void reconectarWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado, intentando reconectar...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Reconectado a WiFi!");
  }
}

void publicarDatosOximetro() {
  if (millis() - ultimo_reporte > TIEMPO_ENTRE_REPORTE) {
    //Serial.print("Frecuencia Cardiaca:");
    //Serial.print(pox.getHeartRate());
    //Serial.print("bpm / SpO2:");
    //Serial.print(pox.getSpO2());
    //Serial.println("%");
    char mensaje[64];
    snprintf(mensaje, sizeof(mensaje), "Frecuencia Cardiaca:%d bpm / SpO2:%d%%", (int)pox.getHeartRate(), (int)pox.getSpO2());
    if (client.publish("oximetro/datos", mensaje)) {
      Serial.println("Mensaje MQTT enviado con éxito");
    } else {
      Serial.println("Error al enviar mensaje MQTT");
    }
    ultimo_reporte = millis();
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  WiFi.begin(ssid, password);
  Serial.println("...................................");
  Serial.print("Conectando a red WiFi.");
  while (WiFi.status() != WL_CONNECTED)
       {  delay(500);
          Serial.print(".") ;
       }
  Serial.println("se ha conectado a la red WiFi!");
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()){ 
    Serial.println("Conectando a MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword ))
      Serial.println("Conectado!");
    else{   
      Serial.print("fallo la conexion y el estado es: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  Serial.print("Inicializando oximetro..");
  if (!pox.begin()) {
      Serial.println("Error!");
  } else {
      Serial.println("INICIALIZADO!");
  } 
  pox.setIRLedCurrent(MAX30100_LED_CURR_46_8MA);
  pox.setOnBeatDetectedCallback(enPulsoDetectado);
  Serial.println("Cuenta regresiva: ");
  for(int i = 0; i<3;i++){
    String aux = +"... ";
    Serial.print(aux);
    delay(1000);
  }
  Serial.println("Comenzando!");
}

void loop() {
  reconectarWiFi();
  reconectarMQTT();
  client.loop();
  pox.update();
  publicarDatosOximetro();
}