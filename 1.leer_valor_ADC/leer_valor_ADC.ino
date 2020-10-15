//------------------ PRÁCTICA 1 ------------------//
// Ejercicio 1: Leer el valor del ADC

void setup() {
  Serial.begin(115200); //Función que inicia la comunicación serie a 115200 bits por segundo
}

void loop() {
  //Conecto potenciometro al puerto 2 
  //(Se podrían haber usados los puertos: 36, 39, 34, 32, 33, 25, 27, 27,8, 12)
  int ValorPotenciometro = analogRead(2); //Lee la entrada analógica del puerto 2
  Serial.println(analogRead(2)); //Imprime los datos en el Monitor Serie
  delay(1000); //tiempo entre lecturas de 1000 ms (1s)

}
