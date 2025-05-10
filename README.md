# StepMate - Smart Walking Stick for the Visually Impaired

StepMate is an assistive device designed to help visually impaired individuals navigate their surroundings safely. It uses an ESP32 microcontroller paired with an HC-SR04 ultrasonic sensor to detect obstacles and provides real-time haptic feedback via a mini coreless vibration motor. Power is managed through a LM2596 buck converter and the onboard AMS1117 regulator, ensuring stable operation.

---

## 🚀 Features

* Obstacle detection using HC-SR04 ultrasonic sensor
* Real-time haptic feedback with varying vibration intensities based on distance
* ESP32-based microcontroller system
* Efficient power management using LM2596 and AMS1117
* Compact, portable, and reliable

---

## 🔧 Hardware Components

* ESP32 Dev Board (NodeMCU-style)
* HC-SR04 Ultrasonic Sensor
* Mini Coreless Vibration Motor (6mm x 12mm)
* BC547 NPN Transistor
* LM2596 Buck Converter Module
* AMS1117 Voltage Regulator (3.3V)
* 1kΩ Resistors (x4)
* 1N4007 Diodes (x2)
* Breadboard and jumper wires
* On/Off Switch
* 9V Li-ion Battery

---

## 🧠 Software Requirements

* Arduino IDE or VS Code with PlatformIO
* ESP32 Board Package installed
* Serial Monitor for debugging

---

## 🔌 Circuit Overview

* ESP32 GPIO 2 → HC-SR04 Trig
* ESP32 GPIO 4 → HC-SR04 Echo (via resistor + diode voltage divider)
* ESP32 GPIO 13 → Base of BC547 (via 1kΩ resistor)
* Collector → Vibration Motor + Diode across motor
* Emitter → GND
* Power via 9V Battery → LM2596 (5V) → AMS1117 (3.3V) → ESP32

---

## 📄 Code Summary

The ESP32 sends a trigger signal to the ultrasonic sensor and measures the echo time to determine the distance to obstacles. Based on this distance, it activates the vibration motor:

* **< 40 cm** → Continuous vibration (high intensity)
* **< 80 cm** → Pulsing vibration (medium intensity)
* **> 80 cm** → No vibration

---

## 📥 Upload Instructions

1. Open `stepmate.ino` in Arduino IDE or VS Code.
2. Connect your ESP32 to your system.
3. Select the correct board and port.
4. Upload the code and monitor the output via Serial Monitor.

---

## 📈 Future Improvements

* Add buzzer/audio feedback
* Use low-power mode to optimize battery life
* Expand obstacle detection angle with multiple sensors

---

## 🙏 Credits

Created by CJ and team as a mini project. Special thanks to everyone who contributed to testing and feedback!

---

Feel free to fork, modify, and contribute. Together, let's build more inclusive tech! 💡
