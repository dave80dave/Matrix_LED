# 8×8 LED Matrix Controller (MAX7219)

This project demonstrates how to control an **8×8 LED Matrix Display (MAX7219)** using an **Arduino Uno R3**.  
The number of active LEDs can be adjusted either via **Serial Monitor input** or with a **Potentiometer**.

The project is designed to be **library-free**, using **direct SPI communication**, making it ideal for learning how SPI and the MAX7219 driver work internally.

---

## ✨ Features

- Control LED count from **0 to 255**
- Two input methods:
  - 📟 **Serial Monitor**
  - 🎛️ **Potentiometer**
- Direct **SPI communication** (no external MAX7219 library)
- Clean and modular code structure
- Perfect for learning **bitwise logic**, **SPI**, and **embedded basics**

---

## 🧰 Hardware Requirements

- Arduino Uno R3  
- 8×8 LED Matrix Display with **MAX7219**
- Potentiometer (e.g. 10kΩ)
- Jumper wires
- Breadboard (optional)

---

## 🔌 Wiring

### Arduino Uno R3 → Matrix Display (MAX7219)

| Arduino Uno | Matrix Display |
|------------|---------------|
| 5V         | VCC / ACC     |
| GND        | GND           |
| D11        | DIN           |
| D10        | CS / LOAD     |
| D13        | CLK           |


---

### Arduino Uno R3 → Potentiometer

| Arduino Uno | Potentiometer |
|------------|---------------|
| 5V         | Outer Pin     |
| GND        | Outer Pin     |
| A0         | Middle Pin    |

> The two outer pins can be swapped – it only changes the rotation direction.

---

## ⚙️ How It Works

### Potentiometer Mode
- `analogRead(A0)` reads a value from **0–1023**
- The value is scaled down to **0–255**
- The LED matrix displays the corresponding number of active LEDs

### Serial Input Mode
- A number between **0 and 255** is entered via the Serial Monitor
- The matrix updates immediately

### LED Mapping Logic
- The matrix is filled **row by row**
- Each row contains **8 LEDs**
- Full rows are set to `0xFF`
- Remaining LEDs are calculated using bit masks

---

## 🧠 Educational Focus

This project helps you understand:

- SPI communication (DIN, CLK, CS)
- MAX7219 internal registers
- Bitwise operations for LED control
- Analog-to-digital conversion (ADC)
- Clean embedded C++ structure

---

## 🚀 Possible Extensions

- Progress bar (left → right)
- Cascading multiple matrix modules
- Animation effects
- Input mode switching (Serial ↔ Potentiometer)
- Noise filtering / smoothing for the potentiometer

---

## 📜 License

This project is open-source and free to use for **learning and educational purposes**.

---

## 👨‍💻 Author

**David**  
HTL student & embedded systems enthusiast  
