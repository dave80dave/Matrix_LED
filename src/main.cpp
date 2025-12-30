#include <Arduino.h>
#include <SPI.h>

#define CS_LED_MATRIX 10
#define Potentiometer A0

void sendToMatrix(byte reg, byte data);
void clearDisplay();
void displayValue(int value);
void readValue();
void Posi();

void setup() {
  pinMode(CS_LED_MATRIX, OUTPUT);
  digitalWrite(CS_LED_MATRIX, HIGH);

  Serial.begin(9600);
  SPI.begin();

  Serial.print("Bitte Zahl von 0 bis 255 eingeben:");

  // --- MAX7219 Initialisierung ---
  sendToMatrix(0x0F, 0x00); // Display-Test AUS
  sendToMatrix(0x0C, 0x01); // Shutdown AUS (Display EIN)
  sendToMatrix(0x0B, 0x07); // 8 Zeilen aktiv
  sendToMatrix(0x09, 0x00); // Decode-Mode AUS (Matrix!)
  sendToMatrix(0x0A, 0x04); // Helligkeit (sichtbar)

  clearDisplay();
}

void loop() {
  //if (Serial.available() > 0) {
  //  readValue();
  //}

  Posi();
}

void displayValue(int value) {
  clearDisplay();

  int fullRows = value / 8;   // volle Reihen
  int restLEDs = value % 8;   // Modulo-LEDs

  // Volle Reihen
  for (int row = 1; row <= fullRows && row <= 8; row++) {
    sendToMatrix(row, 0xFF);
  }

  // Modulo-LEDs
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
  float value = Serial.parseFloat() / 3.984375;
  Serial.println(value);

  if (value > 0 && value <= 255) {
    displayValue(value);
    Serial.print("Angezeigt: ");
    Serial.println(value);
  }
  else{
    Serial.println("Ihre Zahl ist zu groß oder zu klein.");
    Serial.print("Bitte Zahl von 0 bis 255 eingeben:");
  }
}

void Posi() {
  int posi = analogRead(Potentiometer);
  int value = ((posi/4)/4);
  Serial.println(value);

  if (value > 0 && value <= 255) {
    displayValue(value);
    Serial.print("Angezeigt: ");
    Serial.println(value);
  }
}

void clearDisplay() {
  for (int i = 1; i <= 8; i++) {
    sendToMatrix(i, 0x00);
  }
}
