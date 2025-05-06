/*
  LEDs
*/

#define led_rojo 18
#define led_verde 21
#define led_rgb 22

void setup() {
  pinMode(led_rojo,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_rgb,OUTPUT);
}

void loop() {
  digitalWrite(led_rojo,HIGH);
  delay(2000);
  digitalWrite(led_verde,HIGH);
  delay(2000);
  digitalWrite(led_rgb,HIGH);
  delay(2000);

  digitalWrite(led_rojo,LOW);
  delay(2000);
  digitalWrite(led_verde,LOW);
  delay(2000);
  digitalWrite(led_rgb,LOW);
  delay(2000);
}
