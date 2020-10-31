//---------------------------------------- PRÁCTICA 1 ----------------------------------------//
// Ejercicio 5: 
// - Conecta un sensor inercial por I2C (o SPI)
// - Muestrea la aceleración cada 100 ms 
// - Manda los datos cada segundo vía UART (cada vez que envíes activa un LED durante 200ms) 

#include <Wire.h> //librería para conectar por I2C
 
//Direccion I2C de la IMU
#define MPU 0x68
 
//Ratios de conversion
#define A_R ((32768.0/2.0)/9.8) // (32768/2)/9.8
 
 
//MPU-6050 da los valores en enteros de 16 bits
//Valores RAW
int16_t AcX, AcY, AcZ;

const int pinSDA = 17; // Pin de conexión SDA (MPU6050) y pin 17 ESP32
const int pinSCL = 5;  // Pin de conexión SCL (MPU6050) y pin 5 ESP32
const int pinLED = 12; // Pin de conexión LED

int cont; //variable contador

void setup(){
  // CONFIGURACIÓN I2C
  Wire.begin(pinSDA, pinSCL);  // pin 17(GPI17) = SDA , pin 5(GPIO5) = SCL
  Wire.beginTransmission(MPU); //Iniciar una transmisión al dispositivo esclavo I2C con la dirección dada.
  Wire.write(0x6B);            //Iniciar MPU
  Wire.endTransmission(true);
  
  // COMUNICACIÓN SERIE
  Serial.begin(115200); //Función que inicia la comunicación serie a 115200 bits por segundo
  
  // CONFIGURACIÓN LED
  pinMode(pinLED, OUTPUT); //Establecer el pin al que conecto el LED
  }

void loop(){
  // Muestreo cada 100 ms
  for( cont = 0; cont < 10; cont ++){
    Wire.beginTransmission(MPU);
    Wire.write(0x3B); //Pedir el registro 0x3B - corresponde al AcX -> DATASHEET
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,6,true);
       
    AcX = Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 reg -> Unimos valor alto con bajo (OBTENEMOS 16bits)
    AcY = Wire.read()<<8|Wire.read();
    AcZ = Wire.read()<<8|Wire.read();  
         
    delay(100);
  }

  // Mando valor vía UART cada segundo 
  if( cont == 10){
    Serial.println(String(AcX/A_R) + "," + String(AcY/A_R)+ "," + String(AcZ/A_R)); // Muestro por pantalla los valores de la aceleración
     
    digitalWrite(pinLED, HIGH); // Enciende el LED.
    delay(200);                 // Espero 200 ms
    digitalWrite(pinLED, LOW);  // Apaga el LED.
    
    cont = 0; // reseteo el contador
  }
}
