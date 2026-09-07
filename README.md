# 🔥 Interfacing Flame Sensor Module with Arduino

![Interfacing Flame Sensor Module with Arduino](https://playwithcircuit.com/wp-content/uploads/2025/05/Interfacing-Flame-Sensor-Module-with-Arduino.webp)

Flame sensors can detect fire earlier than systems that depend only on a significant increase in temperature. The commonly available flame sensor module uses a photodiode to detect infrared radiation from a flame.

In this project, an **Arduino UNO** is used to read the sensor. Two approaches are demonstrated:

* **Analog output (AO):** Reads the relative intensity of detected IR radiation.
* **Digital output (DO):** Provides a HIGH/LOW signal based on the threshold adjusted using the onboard potentiometer.

A buzzer is used as an audible alarm when a flame is detected.

## 🧰 Hardware Required

| Component           |    Quantity |
| ------------------- | ----------- |
| Arduino UNO         |           1 |
| Flame Sensor Module |           1 |
| I2C LCD             |           1 |
| Buzzer              |           1 |
| Breadboard          |           1 |
| Jumper Wires        | As required |
| Small flame source  |           1 |

## How the Flame Sensor Works

The flame sensor detects **infrared light** emitted by hot objects and flames. Its photodiode converts the detected IR radiation into an electrical signal.

The onboard **LM393 comparator** compares this signal against a threshold set by the potentiometer. When the detected IR level crosses the threshold, the digital output changes state.

The **AO pin** provides an analog signal that can be read by an Arduino analog input, while the **DO pin** can be used for simple flame/no-flame detection.

The module also includes power and signal LEDs for visual indication.

## ⚙️ Module Specifications

| Parameter         | Typical Value |
| ----------------- | ------------- |
| Operating voltage | 3.3V–5V       |
| Detection angle   | ~60°          |
| Detection range   | ~1–2 m        |
| Sensitivity       | Adjustable    |
| Sensor type       | IR photodiode |
| Comparator        | LM393         |

Actual detection range and sensitivity can vary depending on the module, flame size, and surrounding light conditions.

## Flame Sensor Pinout
![Flame Sensor Module Pinout](https://playwithcircuit.com/wp-content/uploads/2025/05/Flame-Sensor-Module-Pinout.webp)
| Pin     | Function                       |
| ------- | ------------------------------ |
| **VCC** | Power supply                   |
| **GND** | Ground                         |
| **DO**  | Digital flame detection output |
| **AO**  | Analog IR intensity output     |

## Wiring
![Flame Sensor Calibration](https://playwithcircuit.com/wp-content/uploads/2025/05/wiring-flame-sensor-with-Arduino-UNO-for-calibration.webp)
### Calibration / Analog + Digital Testing

For calibration, connect both sensor outputs so that the analog reading and digital state can be observed simultaneously.

| Flame Sensor | Arduino UNO |
| ------------ | ----------- |
| VCC          | VCC         |
| GND          | GND         |
| AO           | A0          |
| DO           | D10         |

For the I2C LCD:

| I2C LCD | Arduino UNO |
| ------- | ----------- |
| VCC     | VCC         |
| GND     | GND         |
| SDA     | A4          |
| SCL     | A5          |

The I2C LCD uses the Arduino UNO's **A4 (SDA)** and **A5 (SCL)** pins, so these pins should not be used for other analog-input functions while the LCD is connected.

For the LCD configuration used in this project, the I2C address is **0x27**. Keep the **A0, A1, and A2 address jumpers open** to use this address. If all three jumpers are shorted, the address becomes **0x20**.

## 🎛️ Calibrating the Flame Sensor

Before using the digital output, adjust the onboard potentiometer so the sensor reliably changes its digital state when a flame is introduced into its detection area.

During calibration, the I2C LCD can display:

* Analog sensor counts from **A0**
* Digital output state from **D10**

The analog mode does not require a specific potentiometer setting because the Arduino reads the sensor's analog value directly.

## 🔔 Analog Output Configuration

For analog operation, use the same wiring as the calibration setup but leave the **DO pin unused**.
![Flame Sensor Module Pinout](https://playwithcircuit.com/wp-content/uploads/2025/05/wiring-flame-sensor-with-Arduino-UNO-using-analog-output.webp)

Add the buzzer:

| Buzzer    | Arduino UNO |
| --------- | ----------- |
| Red (+)   | D11         |
| Black (-) | GND         |

The Arduino can then monitor the analog value from **A0** and activate the buzzer when the detected IR level reaches the desired threshold.

## 🚨 Digital Output Configuration

For digital operation, use the sensor's **DO pin** and leave the analog output disconnected.
![Flame Sensor Module Pinout](https://playwithcircuit.com/wp-content/uploads/2025/05/wiring-flame-sensor-with-Arduino-UNO-using-digital-output.webp)

| Connection       | Arduino UNO |
| ---------------- | ----------- |
| Flame Sensor VCC | VCC         |
| Flame Sensor GND | GND         |
| Flame Sensor DO  | D10         |
| Buzzer (+)       | D11         |
| Buzzer (-)       | GND         |

The potentiometer on the module determines the threshold at which the digital output changes state.

## 🧪 Testing

After completing the wiring:

1. Power the Arduino and flame sensor.
2. Keep the flame away from the sensor initially.
3. For digital mode, adjust the potentiometer until the output changes reliably when a flame is detected.
4. For analog mode, observe the values reported by the Arduino.
5. Place a flame within the sensor's detection area and verify the buzzer response.
6. Test under the actual lighting conditions in which the project will be used.

## 📚 Reference

For the complete explanation, wiring diagrams, calibration procedure, LCD setup, and detailed Arduino implementation, see the original tutorial:

**[Play With Circuit – Interfacing Flame Sensor Module with Arduino](https://playwithcircuit.com/flame-sensor-module-arduino-tutorial/)**

The project can be extended with an LCD, IoT connectivity, relay control, or additional sensors to create a more advanced fire-monitoring system.
