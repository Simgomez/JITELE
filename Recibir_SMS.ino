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



void setup() {
 
  
  // inicializar serial.-
  Serial.begin(9600);
 
  pinMode(pwr, OUTPUT);         // pwr como salida
  pinMode(eoff, OUTPUT);        // eoff como salida 
  pinMode(led, OUTPUT);         // led como salida
  pinMode(stat, INPUT);         // stat como entrada  
  
  /* Se enciende el modulo celular */
      while (digitalRead(stat) != LOW) {
        digitalWrite(pwr, HIGH);
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

    // se configura para recibir mensajes
    Serial.println("AT+CMGR=?");
      delay(500);
  // se configura para ver mensajes recibidos
    delay(2000);
    Serial.println("AT+CNMI=2,2,0,0");

   // se evalua la señal de la que dispone el dispositivo
    delay(2000);
    Serial.println("AT+CSQ");


 
}


      

void loop() {

  
   int mensaje=0;
  
    if (Serial.available() > 0 && mensaje == 0) {        //Pregunta si hay un dato en el serial
        Data = Serial.read();                         // Se lee el dato
        if (Data == '@') {                                 // Si reconoce la caracteristica del dato comienza a almacenarlo
          while (true) {
            if (Serial.available() > 0 && mensaje == 0) {                  // Vuelve a preguntar los datos pero apartir del @xxxx
              Data2 = Serial.read();                  // Se lee los datos del serial
              GSM_data[j] = Data2;                         // Se guarda en la cadena
              j++;
              if (Data2 == '\n') {                         //Fin de mensaje
                Serial.println("Lectura:");                 
                Serial.print(GSM_data);                    // Imprime los caracteres almacenados
                mensaje=1;
              }
            }
          }
        }
    }
}
