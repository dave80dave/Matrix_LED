Here is the Code to control the Matrix Display with Serial Input or Potentiometer.

Hardware:
  Arduino Uno R3,
  Matrix Display,
  Potentiometer

Connect:
  Arduino Uno R3 with Matrix Display:
    | Arduino |  | Martrix |
        5V          ACC
        GND         GND
        DIN         D11
        CS          D10
        CLK         D13

  Arduino Uno R3 with Potentiometer
    | Arduino |  | Potentiometer | 
        5V          ACC // left or right
        GND         GND // left or right
        A0 - A5     Middle
