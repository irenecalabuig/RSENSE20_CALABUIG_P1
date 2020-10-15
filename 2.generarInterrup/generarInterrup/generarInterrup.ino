//MIRAR AQUI https://techtutorialsx.com/2017/10/07/esp32-arduino-timer-interrupts/
volatile int interruptCounter;
int totalInterruptCounter;
 
hw_timer_t * timer = NULL; //Puntero para configurar el temporizador
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; //para cuidad la sincronizacion entre
// bucle princial y la rutina de servicio de interrupción
 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
  //Incrementa el contador de interrupciones para indicar al bucle principal que ocurrió la interrupcion
 
}
 
void setup() {
 
  Serial.begin(115200);
 
  timer = timerBegin(0, 800, true);// (nºde temporizador a usar (0-3, hay 4), valor preescalador, true: cuenta hacia arriba)
  timerAttachInterrupt(timer, &onTimer, true);//Manejo de la interrupcion y un flag que indica si la 
  //interrupcion a generar es flanco (True) o nivel (falso)
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
    Serial.println(analogRead(2));
 
  }
}
