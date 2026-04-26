# Solar-Hybrid Dewatering System for Mining Operations 🌊☀️

This project implements an autonomous power-management and water-level monitoring system designed for industrial mining environments.

## 🚀 Live Simulation
**[Click here to run the project in Wokwi](https://wokwi.com/projects/460034481195040769)**

---

## 🛠️ System Logic & Features
* **Solar-Priority Switching:** Automatically prioritizes solar energy to reduce diesel consumption and carbon footprint.
* **Autonomous Dewatering:** Uses ultrasonic sensors to monitor water levels and trigger pumps before flooding occurs.
* **IoT Integration:** Real-time telemetry via **Blynk IoT** for remote monitoring of system health and water levels.
* **Fail-safe Mechanisms:** Includes logic for emergency alerts and buzzer notifications for critical levels.

## 🔌 Hardware & Protocols
* **Microcontroller:** ESP32
* **Sensors:** Ultrasonic (HC-SR04), IR Sensors
* **Actuators:** Relay Module (Pump Control), LED/Buzzer (Alerts)
* **Communication:** UART (Serial Debugging)

## 📁 Repository Contents
* `Solar_Hybrid_Dewatering.ino`: The main system logic and IoT integration code.
* `diagram.json`: The circuit configuration for the Wokwi simulation.
