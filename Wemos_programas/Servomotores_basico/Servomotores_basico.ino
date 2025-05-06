#include <Servo.h>
Servo servo_izquierdo;
Servo servo_derecho;

void setup() {
  servo_izquierdo.attach(D8, 500, 2500);  // GPIO5, ajuste de pulsos
  servo_derecho.attach(D2, 500, 2500);    // GPIO4, ajuste de pulsos
  delay(1000);  // Tiempo para que los servos se inicialicen
}

void loop() {
  servo_izquierdo.write(0);    // Gira a 0°
  servo_derecho.write(180);   // Gira a 90°
  delay(1000);
  servo_izquierdo.write(90);   // Gira a 90°
  servo_derecho.write(90);   // Gira a 90°
  delay(1000);
  servo_izquierdo.write(180);   // Gira a 90°
  servo_derecho.write(0);   // Gira a 90°
  delay(1000);
  servo_izquierdo.write(90);   // Gira a 90°
  servo_derecho.write(90);   // Gira a 90°
  delay(1000);
}