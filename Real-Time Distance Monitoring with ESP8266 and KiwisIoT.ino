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