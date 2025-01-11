# Guardian Angel: Fall Detection System

## Overview
**Guardian Angel** is a real-time fall detection system aimed at improving personal safety for the elderly, solo travelers, and anyone at risk of falling without immediate assistance. Leveraging a combination of gyroscopic and accelerometric data, this system can detect falls accurately and initiate emergency responses if needed.

This prototype showcases a hardware implementation using an **MPU6050 sensor** and **ESP8266 microcontroller**, paving the way for future integration into smartphones, smartwatches, and other wearable devices.
<p align="center">
  <img src="https://github.com/user-attachments/assets/2a48f8b7-6e63-4496-a02e-8f08e155ddf1" alt="Fig 1. Flowchart of workflow" />
</p>

---

## Features
- **Real-Time Fall Detection**: Detects sudden falls using motion thresholds and acceleration analysis.
- **User Confirmation**: Sends an alert to verify if a fall occurred.
- **Automated Emergency Response**: Notifies emergency contacts and calls emergency services with location details if no user confirmation is received.
- **Adjustable Sensitivity**: Configurable thresholds to suit various scenarios and reduce false alarms.
- **Wearable Potential**: Can be integrated into smartwatches and other devices.

---

## Hardware Components
<p align="center">
  <img src="https://github.com/user-attachments/assets/0fbfd0ab-2065-4f45-91f0-fe1697bc022f" alt="Fig 2. Hardware connections" />
</p>

1. **MPU6050 Sensor**: Captures acceleration and angular velocity data.
2. **ESP8266 Microcontroller**: Processes sensor inputs and manages alerts.
    <p align="center">
      <img src="https://github.com/user-attachments/assets/43b4975c-53a3-4647-9de0-d2b1674cacfc" alt="Fig 3. Pin diagram of ESP8266" />
    </p>
4. **Buzzer & LED**: Indicate alerts and fall detection during testing.

---

## How It Works
1. The **MPU6050 sensor** monitors motion and orientation changes.
2. When a fall is detected (exceeding pre-set thresholds and nearing zero acceleration), an alert is sent to the user.
3. If no response is received within 10 seconds:
   - **Buzzer and LED** are activated as a local alert.
   - **Emergency contacts** are notified.
   - **Emergency services** are called with the user's location (to be implemented in future iterations).

---

## Getting Started

### Prerequisites
- An **ESP8266 microcontroller**.
- An **MPU6050 sensor module**.
- Arduino IDE with the following libraries installed:
  - [Adafruit MPU6050](https://github.com/adafruit/Adafruit_MPU6050)
  - [Adafruit Sensor](https://github.com/adafruit/Adafruit_Sensor)

### Installation
1. **Clone the repository**:
   ```bash
   git clone https://github.com/Herie-David/Guardian-Angel.git
   ```
2. **Hardware Setup**:
   - Connect the **MPU6050** and **ESP8266** according to the wiring diagram in the image.

     <p align="center">
      <img src="https://github.com/user-attachments/assets/f28f1f37-8d50-4ee5-80f2-b99b418cc557" alt="Fig 4. Simulation showing connections of ESP8266 with MPU6050" />
     </p>

3. **Upload the Code**:
   - Open the Arduino IDE and load the `guardian_angel.ino` file.
   - Set up the correct board and port for the ESP8266, then upload the sketch.
4. **Testing**:
   - Open the Serial Monitor to observe fall detection logs and emergency response triggers.

---

## Use Cases
- **Elderly Safety**: Provides peace of mind to families with elderly members living alone.
- **Solo Travelers**: Ensures help is dispatched in case of accidents in remote areas.
- **Wearable Integration**: Expands potential use cases for smartwatches and fitness trackers.

---

## Future Enhancements
- **Mobile App Integration**: Seamlessly connect with smartphones for alerts and location tracking.
- **Advanced Algorithms**: Utilize machine learning for more accurate fall detection and fewer false positives.
- **GPS Support**: Enhance emergency response by providing precise location data.
- **Low-Power Mode**: Optimize battery usage for wearable applications.

---

## Contributing
We welcome contributions to make **Guardian Angel** more robust and accessible. You can:
- Report issues.
- Suggest new features.
- Submit pull requests.

---
**Check out the repository for more details and code**: [Guardian Angel GitHub Repository](https://github.com/Herie-David/Guardian-Angel)
