//---------------------------------------- PRÁCTICA 1 ----------------------------------------//
// Ejercicio 3: Generar una salida PWM a 5KHz proporcional a la lectura del ADC

const int SalidaPWM = 12;  // 12 corresponds to GPIO12 SACO LA SALIDA PWM
const int pinPotenciometro = 2; //Pin del potenciómetro

int y; //salida ajustada
int ValorPotenciometro; //Variable que almacena el valor del potenciómetro

// Características PWM
const int freq = 5000;// (5KHz)
const int resolution = 8; //(2^8)-1=255
 
void setup(){
  // configuracion PWM
  ledcSetup(pinPotenciometro, freq, resolution); 
  //vinculo el canal de la GPIO ("SalidaPWM") para ser controlado por el potenciómetro
  ledcAttachPin(SalidaPWM, pinPotenciometro); //(Donde obtengo la salida, de donde modulo el PWM)
}
 
void loop(){
  ValorPotenciometro = analogRead(pinPotenciometro); //Leo entrada analógica del potenciómetro
  y = map(ValorPotenciometro, 0, 4095 , 0, 255); //map(value, fromLow, fromHigh, toLow, toHigh)
  // He ajustado el valor de salida de 0 a 255 (resolución máxima)
  ledcWrite(pinPotenciometro,y); //(canal, dutty)
  delay(20);
 
}   



  
  
