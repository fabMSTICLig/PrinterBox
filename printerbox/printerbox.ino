/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.

  You may need to edit the PRINTER_FIRMWARE value in Adafruit_Thermal.h
  to match your printer (hold feed button on powerup for test page).
  ------------------------------------------------------------------------*/

#include "Adafruit_Thermal.h"
#include "masticlogo.h"
#include "rfflogo.h"
#include <string.h>

//Tableau de chaine à imprimer.
#define MAX_STRING_SIZE 40
#define NUMBERGT 26

char arr2[][MAX_STRING_SIZE] =
{ 
  "Convergence 26",
  "La ecan a jule",
  "le carefour numérique",
  "Chaux de fonds",
  "Chantier Libre",
  "Platforme C",
  "Fab-o-Lab",
  "MASTIC",
  "La Palanquée",
  "Technisub",
  "Les Carmes",
  "Incroyable possible",
  "La Fabrique Caylus",
  "le LOL",
  "Le petit lien",
  "RoseLab",
  "Autonabee",
  "EcoCentre",
  "LuzIn",
  "Serendip Numerique",
  "H-Fablab",
  "Cybergrange",
  "Mobilab66",
  "Imerir",
  "BlueLab",
  "RedLab",
  "ImagiVienne",
  "Bocal",
  "La quincaillerie"
};

char arr[][MAX_STRING_SIZE] =
{ "GT Ecologie",
  "GT Mobilite",
  "GT Accessibilite",
  "GT International",
  "GT Education",
  "GT Arts et culture",
  "GT Outils",
  "GT Gouvernance",
  "GT Metiers de Labs",
  "GT MakeHerSpace",
  "GT Open Bages",
  "GT Comm",
  "GT Ressources Documentaire"
};
// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

//#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

//SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&Serial2,D4);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

//Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------

void setup() {

  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  //pinMode(7, OUTPUT); digitalWrite(7, LOW);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  //mySerial.begin(9600);  // Initialize SoftwareSerial
  Serial2.begin(9600); // Use this instead if using hardware serial
  printer.begin(80);        // Init printer (same regardless of serial type)
  //D3 pi du bouton pour l'impression
  pinMode(D3,INPUT_PULLUP);

}

int indexT = 0;

void loop() {
  if(digitalRead(D3)==LOW) // Apuis sur le bouton
  {
    delay(1000);//Attente 1 seconde
    int test=digitalRead(D3);
    printer.feed(2);
    if(!test){ //Si toujours imprimer on imprime la carte de visite
    printer.printBitmap(masticlogo_width, masticlogo_height, masticlogo_data);
    printer.println(F("Germain Lemasson"));
    printer.println(F("fablab-mastic"));
    printer.println(F("@univ-grenoble-alpes.fr"));
    printer.println(F("site : fabmastic.imag.fr"));
    }
    else //Sinon on imprime une chaine de caractères.
    {
      printer.printBitmap(rfflogo_width, rfflogo_height, rfflogo_data);
      printer.println(arr2[indexT]);
      indexT++;
      indexT=indexT%NUMBERGT;
    }
    printer.feed(3);
  }
  delay(100);
}
