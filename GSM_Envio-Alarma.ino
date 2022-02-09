
const char * result = "";
float resistance = 2.55;

char charFloat [5];

char GSM_data[100];
char GSM_data2[100];
int j=0;
char Data = 0, Data2 = 0;

// se declaran pines de entrada y salida para interactuar con el modulo celular
int pwr = 2;                    // pin para power                
int eoff = 3;                   // pin para emergency off
int stat = 4;                   // pin para status
int led = 13;                   // pin para encender LED
int cont = 0;

/*
const float ADC_mV = 0.805;       // convesion multiplier from Arduino ADC value to voltage in mV
const float SensorOffset = 1;     // in mV 
const float sensitivity = 9.8;      // in mV/mmH2O 
const float mmh2O_cmH2O = 10;         // divide by this figure to convert mmH2O to cmH2O

float promedio=0;
float promedio2=0;
float sensorValue2 = 0;
float flujo=0;
*/

void Emergencia();

void setup() {
 
  
  // inicializar serial.-
  Serial.begin(9600);
 
  pinMode(pwr, OUTPUT);         // pwr como salida
  pinMode(eoff, OUTPUT);        // eoff como salida 
  pinMode(led, OUTPUT);         // led como salida
  pinMode(stat, INPUT);         // stat como entrada  
  
  /* Se enciende el modulo celular */
  while(digitalRead(stat)!=LOW){
    digitalWrite(pwr, HIGH);
    delay(1000);
    digitalWrite(pwr, LOW);
  } 
  delay(3000);  

  
  // se inicializa el modulo
    Serial.println("AT");
    delay(2000);
  
  // se activan todas las funciones del modulo celular    
    Serial.println("AT+CFUN=1");
    delay(2000);

  
  // se configura el formato de MSM en ASCII
    delay(2000);
    Serial.println("AT+CMGF=1");

  
  // se configura para ver mensajes recibidos
    delay(2000);
    Serial.println("AT+CNMI=2,2,0,0");

   // se evalua la señal de la que dispone el dispositivo
    delay(2000);
    Serial.println("AT+CSQ");
 
}


      

void loop() {

  int alto = 0;
  int bajo= 0;
  /*promedio=0;
   
  // Se Realiza el muestreo y calculo para flujo
  for (int i=0;i<=19;i++){
  sensorValue2 = (analogRead(15) * ADC_mV - SensorOffset) / sensitivity / mmh2O_cmH2O;
  promedio=promedio+sensorValue2;
  promedio2=promedio2+1;
  delay(100);
  }

  promedio=promedio /20;
  //resistance = flujo;
  char result[8]; // Buffer big enough for 7-character float
  dtostrf(resistance, 6, 2, result); // Leave room for too large numbers!
  flujo=5;
  
  if (flujo < 0.1){
    bajo = 1; // secuencia para activar alamra
    goto Emergencia;
  }*/

 Emergencia :
 if (bajo == 1){
    Serial.write("AT+CMGS=");
    Serial.write(0x22);
    Serial.write("3015970822");    // aqui se debe colocar el numero de celular
    Serial.write(0x22);
    Serial.write(0x0D);
    Serial.write(0x0A);
    Serial.write("!El flujo es muy bajo, menor a 0.1! \n El flujo actual esta en: ");  // este es el mensaje que se desea enviar
    Serial.write(result);
    Serial.write(0x1A);
    Serial.println("");
    delay (8000);
 }



    
  // se envia un mensaje de texto al numero asignado
 
    Serial.write("AT+CMGS=");
    Serial.write(0x22);
    Serial.write("3015970822");    // aqui se debe colocar el numero de celular
    Serial.write(0x22);
    Serial.write(0x0D);
    Serial.write(0x0A);
    Serial.write("El flujo es:");  // este es el mensaje que se desea enviar
    Serial.write(result);
    Serial.write(0x1A);
    Serial.println("");
    delay (10000);
      
    
}
