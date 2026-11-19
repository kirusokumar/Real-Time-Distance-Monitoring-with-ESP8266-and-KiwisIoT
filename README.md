# Real-Time Distance Monitoring with ESP8266 and KiwisIoT

An IoT-based distance monitoring project using an HC-SR04 ultrasonic sensor and NodeMCU ESP8266 to measure object distance and display live readings on the KiwisIoT cloud dashboard.

## Project Overview

In this project, I built a real-time distance monitoring system using an HC-SR04 ultrasonic sensor and NodeMCU ESP8266.

The ultrasonic sensor measures the distance to an object by transmitting sound waves and detecting their returning echo. The ESP8266 calculates the distance in centimeters and sends the readings to the KiwisIoT dashboard through Wi-Fi.

This allows users to monitor distance measurements remotely.

**System Architecture:**

HC-SR04 → NodeMCU ESP8266 → Wi-Fi → KiwisIoT Dashboard

## Features

- Real-time distance measurement
- Ultrasonic object detection
- Distance calculation in centimeters
- Wireless data transmission using ESP8266
- Cloud-based monitoring through KiwisIoT
- Live dashboard visualization
- Serial Monitor output for testing

## Hardware Components

| Component | Quantity |
|---|---:|
| NodeMCU ESP8266 | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| USB-A to Mini-USB Cable | 1 |
| Jumper Wires | As required |

## Software Requirements

- Arduino IDE
- ESP8266 Board Package
- KiwisIoT Arduino Library
- KiwisIoT Account
- Wi-Fi Connection

## Circuit Connections

### HC-SR04 Ultrasonic Sensor to NodeMCU ESP8266

| HC-SR04 Pin | NodeMCU Pin |
|---|---|
| VCC | VIN / suitable 5V supply |
| GND | GND |
| TRIG | D5 (GPIO14) |
| ECHO | D7 (GPIO13), through a voltage divider |

**Important:** The HC-SR04 ECHO pin can output 5V, while ESP8266 GPIO pins use 3.3V logic. Use a suitable voltage divider or logic-level shifter before connecting ECHO to D7. Never connect a 5V signal directly to an ESP8266 GPIO pin.

## KiwisIoT Dashboard Configuration

Create a dashboard named **Distance Monitoring** and add a gauge or numeric value widget.

| Channel | Parameter | Unit |
|---|---|---|
| Channel 1 | Object Distance | cm |

Configure the widget to receive data from Channel 1 and display the measurement in centimeters.

## Arduino Programming

The program uses the `pulseIn()` function to measure the duration of the ultrasonic echo pulse and calculates the distance using the speed of sound.

### Distance Calculation

\[
Distance = \frac{Duration \times 0.0343}{2}
\]

The result is calculated in centimeters.

### Arduino Code

```cpp
#include <KiwisIoT.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";
const char* topic = "YOUR_TOPIC_ID";

KiwisIoT kiwisiot(ssid, pass, topic);

#define TRIG_PIN D5
#define ECHO_PIN D7

unsigned long duration;
float distance;

void setup()
{
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);
  kiwisiot.begin();

  Serial.println("Distance Monitoring Started");
}

void loop()
{
  kiwisiot.run();

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (duration > 0)
  {
    distance = duration * 0.0343f / 2.0f;

    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.println(" cm");

    kiwisiot.send("1", distance);
  }
  else
  {
    Serial.println("No echo received");
  }

  delay(1000);
}
```

Replace the Wi-Fi credentials and KiwisIoT Topic ID with your own values before uploading the program.

## How It Works

1. The HC-SR04 sends an ultrasonic pulse when triggered.
2. The pulse travels through the air and reflects from an object.
3. The sensor receives the returning echo.
4. The NodeMCU ESP8266 measures the echo duration.
5. The ESP8266 calculates the distance in centimeters.
6. The KiwisIoT library sends the distance value through Channel 1.
7. The dashboard displays the updated distance measurement.

## Installation and Setup

1. Install the Arduino IDE.
2. Install the ESP8266 board package.
3. Select NodeMCU ESP8266 in the Arduino IDE.
4. Install the KiwisIoT Arduino library.
5. Connect the HC-SR04 sensor according to the circuit connections.
6. Create a KiwisIoT dashboard named Distance Monitoring.
7. Add a gauge or numeric widget configured for Channel 1.
8. Copy your KiwisIoT Topic ID.
9. Enter your Wi-Fi credentials and Topic ID in the Arduino sketch.
10. Select the correct COM port.
11. Upload the program.
12. Open the Serial Monitor at 115200 baud.
13. Place an object in front of the sensor and observe the readings.

## Testing the Project

- Place an object in front of the HC-SR04 sensor.
- Move the object closer to the sensor.
- Observe the distance values in the Serial Monitor.
- Move the object farther away.
- Verify that the KiwisIoT dashboard updates through Channel 1.

Actual readings depend on the target surface, sensor alignment, and measurement conditions.

## Applications

- Parking assistance systems
- Obstacle detection
- Robotics and automation
- Proximity monitoring
- Smart object detection
- Experimental water-tank level measurement
- IoT-based distance monitoring

## Troubleshooting

**The Sensor Shows No Echo**
- Check the VCC and GND connections.
- Make sure TRIG is connected to D5 and ECHO to D7.
- Confirm that the target is within the sensor's usable range.
- Check the ECHO voltage divider connection.

**Distance Readings Are Incorrect**
- Point the sensor directly toward the object.
- Avoid soft, angled, or irregular surfaces.
- Check the wiring and sensor alignment.
- Compare the reading with a known distance.

**NodeMCU Does Not Upload the Code**
- Select the correct ESP8266 board.
- Check the COM port.
- Use a USB cable that supports data transfer.
- Confirm that the ESP8266 board package is installed.

**KiwisIoT Dashboard Does Not Update**
- Check your Wi-Fi name and password.
- Verify the dashboard Topic ID.
- Make sure the widget is configured for Channel 1.
- Confirm that `kiwisiot.begin()`, `kiwisiot.run()`, and `kiwisiot.send("1", distance)` are included.
- Check the Serial Monitor for valid distance readings.

## Safety Notes

- Never connect the HC-SR04 ECHO pin directly to an ESP8266 GPIO because it can output 5V.
- Use a suitable voltage divider or level shifter.
- Ensure stable power and common ground connections.

## Recommended Platform: KiwisIoT

KiwisIoT helps connect hardware projects to an online dashboard and visualize sensor readings remotely.

Explore more projects:

https://github.com/Kiwistron/KiwisIoT-Projects/tree/main

## Libraries and Resources

- **KiwisIoT Website:** https://www.kiwisiot.in/
- **KiwisIoT Arduino Library:** https://github.com/Kiwistron/KiwisIoT
- **KiwisIoT Example Projects:** https://github.com/Kiwistron/KiwisIoT-Projects/tree/main

## Project Tutorial

Read the complete project tutorial on Hackster.io:

[Real-Time Distance Monitoring with ESP8266 and KiwisIoT](https://www.hackster.io/kirusokumar/real-time-distance-monitoring-with-esp8266-and-kiwisiot-9793e6)

## Author

**Kirusokumar**

## License

This project is licensed under the Apache License 2.0. You may use, modify, and distribute it according to the license terms.