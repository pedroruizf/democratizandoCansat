/*
  SD card read/write
 
 This example shows how to read and write data to and from an SD card file 	
 The circuit:
  created   Nov 2010  by David A. Mellis
 modified 9 Apr 2012  by Tom Igoe
  This example code is in the public domain.
Adaptado por Pedro Ruiz para placa TTGO LoRa32 V2.1_1.6, con chip esp32 pico d-4
El programa abre el archivo y escribe del 0 al 9 en el y posteriormente lee el contenido del archivo
 */

#include <SPI.h>
#include <mySD.h>

ext::File myFile;
int contador = 0;  // inicializamos contador

// change this to match your SD shield or module;
// para TTGO LoRa32 V2.1_1.6 CS=13
const int chipSelect = 13;

void setup() {
  //Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.print("Initializing SD card...");

  pinMode(SS, OUTPUT);

  if (!SD.begin(13, 15, 2, 14)) {  //definición de pines CS,MOSI,MISO,SCK
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  for (contador = 0; contador < 10; contador++) {

    myFile = SD.open("prueba.csv", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) {
      Serial.print("Writing to prueba.csv...");
      myFile.println(contador);
      // close the file:
      myFile.close();
      Serial.print("done.");
      Serial.println(contador);
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening prueba.csv");
    }
    delay(1000);
  }

  //open the file for reading:
  myFile = SD.open("prueba.csv");
  if (myFile) {
    Serial.println("prueba.csv:");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening prueba.csv");
  }
}

void loop() {
}
