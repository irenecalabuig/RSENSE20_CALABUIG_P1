
String option;
String segundos;
int y;
int seg; //
int duty;
int dutyPWM;
const int pinPotenciometro = 2; //Pin del potenciómetro
const int ledPin = 12;  // 12 corresponds to GPIO12 SACO LA SALIDA PWM
// Características PWM
const int freq = 5000;// (5KHz)
const int ledChannel = 0; // Elijo un canal
const int resolution = 8; //(2^8)-1=255

void setup() {
  Serial.begin(115200);
  // configuracion PWMv
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
      Serial.println(analogRead(pinPotenciometro)); //Imprime los datos en el Monitor Serie
         }
    else if (option.startsWith("ADC(")){
      Serial.println(option);
      option.remove(-1);
      option.remove(0, 4);
      seg=option.toInt();
      Serial.println("ADC(x), repetir cada "+String(seg)+" segundos");
      
    }
    else if (option.startsWith("PWM(")){
      Serial.println(option);
      option.remove(-1);
      option.remove(0, 4);
      duty=option.toInt();
      dutyPWM=(255*duty)/9;
      Serial.println(dutyPWM);

      
    }
        
  }
  //Para el caso del ADC(x)
      if (seg>0){        
        int ValorPotenciometro = analogRead(pinPotenciometro);
        y = map(ValorPotenciometro, 0, 4095 , 0, 3300); //Reajusto los valores
        Serial.println(y); //Imprime los datos en el Monitor Serie
        delay(seg*1000);//paso a ms
      }

  //Para el caso del PWM(x)      
      if (dutyPWM>0){
        ledcWrite(ledChannel,dutyPWM);    
        delay(100); //tiempo entre lecturas de 1000 ms (1s)
      }
      
}
