
//---------------------------------------- PRÁCTICA 1 ----------------------------------------//
// Ejercicio 2: Generar una interrupción cada 10s que lea el ADC

const int pinPotenciometro = 2; //Pin del potenciómetro
int y; //variable de salida re-asignada
int ValorPotenciometro;

volatile int interruptCounter; //variable que se comparte entre el bucle principal y el ISR 
int totalInterruptCounter; //variable que cuenta el número total de interrupciones
 
hw_timer_t * timer = NULL; //Puntero para configurar el temporizador

//para cuidarla sincronizacion entre bucle princial y la rutina de servicio de interrupción
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; 

//FUNCIÓN ISR
void IRAM_ATTR onTimer() {
  //Le dice al buble principal que ha habido una interrupción
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++; //incremento el contador de interrupciones
  portEXIT_CRITICAL_ISR(&timerMux);
  //Incrementa el contador de interrupciones para indicar al bucle principal que ocurrió la interrupcion
 
}
 
void setup() {
   Serial.begin(115200);//Función que inicia la comunicación serie a 115200 bits por segundo
  
  //----------- CONFIGURACIÓN ----------- //
  // (nºde temporizador a usar (0-3, hay 4), valor preescalador, true: cuenta hacia arriba)
  timer = timerBegin(0, 800, true);
  //Manejo de la interrupcion y un flag que indica si la interrupcion a generar es flanco (True) o nivel (falso)
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true); //Decimos que queremos la interrupcion a los 10s
  timerAlarmEnable(timer); //Habilitamos el temporizador
 
}
 
void loop() {
  
  if (interruptCounter > 0) {
  
    portENTER_CRITICAL(&timerMux);
    interruptCounter--; // se ha detectado interrupcion-> DECREMENTO
    portEXIT_CRITICAL(&timerMux);
 
    totalInterruptCounter++;
 
    Serial.print("INTERRUPCIÓN Nº: ");
    Serial.println(totalInterruptCounter);
    ValorPotenciometro = analogRead(pinPotenciometro); ////Leo entrada analógica del potenciómetro
    // La función map(): Re-asigna un número de una gama a otra
    y = map(ValorPotenciometro, 0, 4095 , 0, 3300); //map(value, fromLow, fromHigh, toLow, toHigh)
    // He ajustado el valor de salida de 0 a 3300mV.
    Serial.println(y); //Imprime los datos en el Monitor Serie
 
  }
}
