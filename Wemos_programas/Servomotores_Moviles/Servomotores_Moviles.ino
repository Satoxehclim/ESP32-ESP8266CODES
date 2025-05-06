#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>

// Configuración de servos
Servo servo_izquierdo;
Servo servo_derecho;
const int pin_servo_izq = D8;  // GPIO15
const int pin_servo_der = D2;  // GPIO4

// Configuración WiFi AP
const char* ssid_ap = "Robot_Servos";
const char* password_ap = "12345678";

// Configuración UDP
WiFiUDP Udp;
unsigned int localUdpPort = 8888;  // Puerto de escucha
char packetBuffer[50];             // Buffer para paquetes entrantes

void setup() {
  Serial.begin(115200);
  
  // Inicializa servos
  servo_izquierdo.attach(pin_servo_izq, 500, 2500);
  servo_derecho.attach(pin_servo_der, 500, 2500);
  servo_izquierdo.write(90);  // Posición inicial
  servo_derecho.write(90);

  // Configura WiFi en modo AP
  WiFi.softAP(ssid_ap, password_ap);
  Serial.print("AP creado. IP: ");
  Serial.println(WiFi.softAPIP());

  // Inicia UDP
  Udp.begin(localUdpPort);
  Serial.print("Servidor UDP iniciado. Puerto: " + String(localUdpPort));
}

void loop() {
  // Procesa paquetes UDP entrantes
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(packetBuffer, sizeof(packetBuffer) - 1);
    if (len > 0) {
      packetBuffer[len] = '\0';  // Null-terminate
      String data = packetBuffer;
      
      // Formato esperado: "SERVO,ANGULO" (ej: "1,90" o "2,180")
      int servo = data.substring(0, data.indexOf(',')).toInt();
      int angle = data.substring(data.indexOf(',') + 1).toInt();

      // Mueve el servo correspondiente
      if (servo == 1) {
        servo_izquierdo.write(angle);
      } else if (servo == 2) {
        servo_derecho.write(angle);
      }
    }
  }
}