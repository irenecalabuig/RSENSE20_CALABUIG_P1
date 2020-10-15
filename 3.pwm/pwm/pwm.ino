// the number of the LED pin
const int ledPin = 12;  // 12 corresponds to GPIO12 SACO LA SALIDA PWM
int y; //salida ajustada

// Características PWM
const int freq = 5000;// (5KHz)
const int pinPotenciometro = 2; //Pin del potenciómetro
const int resolution = 8; //(2^8)-1=255
 
void setup(){
  // configuracion PWM
  ledcSetup(pinPotenciometro, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, pinPotenciometro); //de donde obtener la señal, canal donde genero señal 
}
 
void loop(){
  int ValorPotenciometro = analogRead(pinPotenciometro); //Lee la entrada analógica del puerto 2
  y = map(ValorPotenciometro, 0, 4095 , 0, 255); //Reajusto los valores
  ledcWrite(pinPotenciometro,y);
  delay(20);
 
}   


  
  
