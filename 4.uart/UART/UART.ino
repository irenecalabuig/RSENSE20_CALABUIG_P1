//---------------------------------------- PRÁCTICA 1 ----------------------------------------//
// Ejercicio 4: Comandar por la UART los periféricos de tal forma que si mandas:
// - ADC: envíe la lectura actual del ADC
// - ADC(x): envíe la lectura del ADC cada x seg
// - PWM(x): comanda el duty cycle del PWM con números del 0 al 9

String option; // variable que escribes por pantalla para elegir que es lo que deseas mostrar

// Características Potenciómetro
int y; //variable que contiene la salida reajustada del potenciómetro
int seg; //variable para que envíe lectura cada x segundos
const int pinPotenciometro = 2; //Pin del potenciómetro
int ValorPotenciometro; //Variable que almacena el valor del potenciómetro


// Características PWM
const int freq = 5000;// (5KHz)
const int ledChannel = 0; // Elijo un canal
const int resolution = 8; //(2^8)-1=255
const int ledPin = 12;  // 12 corresponds to GPIO12 SACO LA SALIDA PWM
int duty; //variable de selección de 0 a 9
int dutyPWM; //valor del PWM escalado en función de la variable 'duty'

void setup() {
  Serial.begin(115200);
  // configuracion PWM
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
  }
  


void loop() {
    
  if(Serial.available()>0){ //(Si el puerto serie está libre->ENTRO)
    seg=0;
    option = Serial.readStringUntil('\n'); //(Lo que escribo por el puerto serie)
    
    //------------------- 3 CASOS -------------------//
    if (option == "ADC"){
      Serial.println(option);
      ValorPotenciometro = analogRead(pinPotenciometro); //Leo entrada analógica del potenciómetro
      y = map(ValorPotenciometro, 0, 4095 , 0, 3300); //Reajusto los valores
      Serial.println(y); //Imprime los datos en el Monitor      
    }
    
    else if (option.startsWith("ADC(")){
      Serial.println(option);
      option.remove(-1); //borro la última posición del String [equivale a borrar ')' ]
      option.remove(0, 4); //borro las 4 primeras posiciones del String [equivale a borrar 'ADC(' ]
      seg=option.toInt();
      Serial.println("ADC(x), repetir cada "+String(seg)+" segundos");      
    }
    
    else if (option.startsWith("PWM(")){
      Serial.println(option);
      option.remove(-1); // borro la última posición del String [equivale a borrar ')' ]
      option.remove(0, 4); // borro las 4 primeras posiciones del String [equivale a borrar 'PWM(' ]
      duty=option.toInt(); // paso a int el número escrito por pantalla [es un número del 0 al 9]
      dutyPWM=(255*duty)/9; // ajusto el valor de salida del PWM [0 valor mínimo y 9 valor máximo]
      Serial.println(dutyPWM);
    }
    
    else if (option == 0){
      //DEJO DE MANDAR DATOS
    }

  }
      
  //Para el caso del ADC(x)
  if(seg>0){        
    ValorPotenciometro = analogRead(pinPotenciometro); //Leo entrada analógica del potenciómetro
    y = map(ValorPotenciometro, 0, 4095 , 0, 3300); //Reajusto los valores
    Serial.println(y); //Imprime los datos en el Monitor Serie
    delay(seg*1000);//paso a ms              
  }
      

  //Para el caso del PWM(x)      
  if (dutyPWM>0){
    ledcWrite(ledChannel,dutyPWM);    
    delay(1000); //tiempo entre lecturas de 1000 ms (1s)
  }
  
}
