// the number of the LED pin
const int ledPin = 12;  // 12 corresponds to GPIO12 SACO LA SALIDA PWM

// setting PWM properties
const int freq = 5000;// (5KHz)
const int ledChannel = 2; //(POTENCIOMETRO)
const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel); //de donde obtener la señal, canal donde genero señal 
}
 
void loop(){
  // increase the LED brightness
  ledcWrite(ledChannel,analogRead(2));
  delay(20);
 
}   


  
  
