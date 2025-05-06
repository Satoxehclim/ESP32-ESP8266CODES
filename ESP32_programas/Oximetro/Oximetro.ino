#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define TIEMPO_ENTRE_REPORTE 1000

PulseOximeter pox;
uint32_t ultimo_reporte = 0;
void enPulsoDetectado() {
    Serial.println("Latido detectado!");
}

void setup() {
  Serial.begin(115200);
  delay(2000);
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
    pox.update();
    if (millis() - ultimo_reporte > TIEMPO_ENTRE_REPORTE) {
        Serial.print("Frecuencia Cardiaca:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");
        ultimo_reporte = millis();
    }
}