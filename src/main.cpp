#include <Arduino.h>
#include <SPI.h>

#define CS_LED_MATRIX 10
#define Potentiometer A0

void sendToMatrix(byte reg, byte data);
void clearDisplay();
void displayValue(int value);
void readValue();
void posi();

bool waitingForInput = true;

void setup() {
  pinMode(CS_LED_MATRIX, OUTPUT);
  digitalWrite(CS_LED_MATRIX, HIGH);

  Serial.begin(9600);
  SPI.begin();

  // MAX7219 Init
  sendToMatrix(0x0F, 0x00);
  sendToMatrix(0x0C, 0x01);
  sendToMatrix(0x0B, 0x07);
  sendToMatrix(0x09, 0x00);
  sendToMatrix(0x0A, 0x04);

  clearDisplay();
}

void loop() {
  // readValue();
  posi();   // KEIN clearDisplay() hier!
}


void displayValue(int value) {
  clearDisplay();

  int leds = (value / 255.0) * 64; // Skaliert auf 0-64 LEDs
  int fullRows = leds / 8; // Volle Reihen
  int restLEDs = leds % 8; // Modulo-LEDs

  for (int row = 1; row <= fullRows && row <= 8; row++) {
    sendToMatrix(row, 0xFF);
  }

  if (fullRows < 8 && restLEDs > 0) {
    byte mask = 0xFF << (8 - restLEDs);
    sendToMatrix(fullRows + 1, mask);
  }
}

void sendToMatrix(byte reg, byte data) {
  digitalWrite(CS_LED_MATRIX, LOW);
  SPI.transfer(reg);
  SPI.transfer(data);
  digitalWrite(CS_LED_MATRIX, HIGH);
}


void readValue() {

  if (waitingForInput) {
    Serial.println("Geben Sie eine Zahl von 0 bis 255 ein:");
    waitingForInput = false;
  }

  // Nur reagieren, wenn Daten da sind
  if (Serial.available() > 0) {
    int value = Serial.parseInt();

    // Buffer komplett leeren
    while (Serial.available() > 0) {
      Serial.read();
    }

    if (value < 0 || value > 255) {
      Serial.println("Ungültige Eingabe!");
      return;
    } 
    else {
      Serial.print("Angezeigt: ");
      Serial.println(value);
      displayValue(value);
    }

    waitingForInput = true;  // zurück in Wartezustand
  }
}

void posi() {
  int posi = analogRead(Potentiometer);
  int value = (posi / 4); // Skaliert auf 0-255
  Serial.print(value);
  displayValue(value);
}


void clearDisplay() {
  for (int i = 1; i <= 8; i++) {
    sendToMatrix(i, 0x00);
  }
}
