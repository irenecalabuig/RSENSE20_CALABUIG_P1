//---------------------------------------- PRÁCTICA 1 ----------------------------------------//
// Ejercicio 1: Leer el valor del ADC

const int pinPotenciometro = 2; //Pin del potenciómetro
int y; //variable de salida re-asignada
int ValorPotenciometro;

void setup() {
  Serial.begin(115200); //Función que inicia la comunicación serie a 115200 bits por segundo
}

void loop() {
  //Conecto potenciometro al puerto 2 
  //(Se podrían haber usados los puertos: 36, 39, 34, 32, 33, 25, 27, 27,8, 12)
  ValorPotenciometro = analogRead(pinPotenciometro); ////Leo entrada analógica del potenciómetro
  // La función map(): Re-asigna un número de una gama a otra
  y = map(ValorPotenciometro, 0, 4095 , 0, 3300); //map(value, fromLow, fromHigh, toLow, toHigh)
  // He ajustado el valor de salida de 0 a 3300mV.
  Serial.println(y); //Imprime los datos en el Monitor Serie
  delay(1000); //tiempo entre lecturas de 1000 ms (1s)

}
