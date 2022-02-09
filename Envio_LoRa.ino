//Libreria LoRa
#include <SPI.h>
#include <LoRa.h>

//Librerias para OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Define los pines usado por LoRa
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//433E6 for Asia
//866E6 for Europe
#define BAND 915E6 
//#define BAND 866E6

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


int counter = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void setup() {

  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //inicia OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,5);
  display.print("LORA ENVIO");
  display.display();
  
  //initialize Serial Monitor
  Serial.begin(115200);
  
  Serial.println("Prueba Envio LoRa:");

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(250000);
  LoRa.setCodingRate4(5);
  LoRa.setSyncWord(0x34);
  
  Serial.println("LoRa Initializing OK!");
  display.setCursor(0,20);
  display.print("LoRa Initializing OK!");
  display.display();
  delay(2000);
}

void loop() {

  Serial.print("Enviando Paquete: ");
  Serial.println(counter);

  //Envia Paquete LoRa al receptor
  LoRa.beginPacket();
  //LoRa.print("<0001>");
  //LoRa.print("count=");
  LoRa.print("Paquete Numero: ");
  LoRa.print(counter);
  LoRa.endPacket();


  digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)// Led TTGO T BEAM
  delay(1000);                       // wait for a second
  digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
  
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("LORA SENDER");
  display.setCursor(0,20);
  display.setTextSize(1);
  display.print("Paquete LoRa Enviado.");
  display.setCursor(0,30);
  display.print("Contador:");
  display.setCursor(50,30);
  display.print(counter);      
  display.display();

  counter++;
  
  delay(10000);
}
