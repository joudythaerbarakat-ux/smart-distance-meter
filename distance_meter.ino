/*
  Smart Distance Meter
  Arduino Uno + HC-SR04 Ultrasonic Sensor + 16x2 I2C LCD

  Measures distance via ultrasonic time-of-flight, applies a moving-average
  filter to reduce sensor noise, and displays real-time readout on LCD + Serial.

  Author: Joudy Thaer Barakat
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---- Pin Configuration ----
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

// ---- LCD Configuration (I2C address 0x27, 16x2) ----
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---- Measurement Configuration ----
const int SAMPLES = 5;              // moving average window
const unsigned long PULSE_TIMEOUT = 30000UL; // microseconds (~5m max range safety)
const float SOUND_SPEED_CM_PER_US = 0.0343;  // speed of sound at ~20°C

float readings[SAMPLES];
int readIndex = 0;
float total = 0;
bool bufferFilled = false;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Distance");
  lcd.setCursor(0, 1);
  lcd.print("Meter - Ready");
  delay(1500);
  lcd.clear();

  for (int i = 0; i < SAMPLES; i++) readings[i] = 0;
}

float getRawDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, PULSE_TIMEOUT);

  if (duration == 0) {
    return -1; // out of range / no echo received
  }

  float distance = (duration * SOUND_SPEED_CM_PER_US) / 2.0;
  return distance;
}

float getFilteredDistanceCM() {
  float raw = getRawDistanceCM();
  if (raw < 0) return -1; // propagate out-of-range

  total -= readings[readIndex];
  readings[readIndex] = raw;
  total += raw;
  readIndex = (readIndex + 1) % SAMPLES;
  if (readIndex == 0) bufferFilled = true;

  int divisor = bufferFilled ? SAMPLES : (readIndex == 0 ? SAMPLES : readIndex);
  return total / divisor;
}

void loop() {
  float distance = getFilteredDistanceCM();

  lcd.setCursor(0, 0);
  lcd.print("Distance:       ");

  lcd.setCursor(0, 1);
  if (distance < 0) {
    lcd.print("Out of range    ");
    Serial.println("Out of range");
  } else {
    lcd.print(distance, 1);
    lcd.print(" cm         ");
    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.println(" cm");
  }

  delay(200); // ~5 Hz update rate
}
