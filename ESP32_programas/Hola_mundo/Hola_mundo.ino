//HOLA MUNDO

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.print("Esto es el setup. ");
  Serial.println("Linea nueva despues...");
}

void loop() {
  Serial.println("Esto es el loop");
  delay(2000);
}
