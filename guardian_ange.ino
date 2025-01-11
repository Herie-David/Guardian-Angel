#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Initialize I2C and MPU6050
Adafruit_MPU6050 mpu;

// Set up GPIO for LED and buzzer
const int ledPin = D8;  // LED connected to D8
const int buzzerPin = D7;  // Buzzer connected to D7

// Fall detection constants
const float ACCELERATION_ZERO_THRESHOLD = 0.2;  // Threshold near zero acceleration
const float BASELINE_THRESHOLD = 0.5;  // Threshold to detect significant drop
float baselineAcceleration = 0.0;  // To store baseline acceleration

// Time duration for LED and buzzer
const int ALERT_DURATION = 5000;  // 5 seconds

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("Starting setup...");

  // Initialize I2C
  Wire.begin();

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip. Check wiring.");
    while (1) {
      delay(10);  // Infinite loop if initialization fails
    }
  }

  // Set up GPIO for LED and buzzer
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Baseline calibration
  Serial.println("Calibrating baseline acceleration...");
  baselineAcceleration = calculateBaseline();
  Serial.print("Baseline acceleration: ");
  Serial.println(baselineAcceleration);
}

void loop() {
  // Read sensor data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Get the total acceleration
  float currentAcceleration = sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2));
  Serial.print("Current Acceleration: ");
  Serial.println(currentAcceleration);

  // Check for a fall
  if (detectFall(currentAcceleration)) {
    Serial.println("Potential fall detected!");

    // Ask the user if the fall is real
    Serial.println("Was the fall real? (Enter 'N' if no fall occurred): ");
    unsigned long startTime = millis();
    bool userResponded = false;

    while (millis() - startTime < 10000) {  // 10 seconds to respond
      if (Serial.available() > 0) {
        char userResponse = Serial.read();
        if (userResponse == 'N' || userResponse == 'n') {
          Serial.println("No fall confirmed by user.");
          userResponded = true;
          break;
        }
      }
    }

    // If no response, activate alert
    if (!userResponded) {
      activateAlert();
      Serial.println("Calling emergency services...");
    } else {
      Serial.println("User confirmed no fall.");
    }
  }
  delay(500);  // Small delay for readability in the Serial Monitor
}

float calculateBaseline() {
  float sum = 0.0;
  int sampleCount = 50;  // Number of samples to average over 5 seconds

  for (int i = 0; i < sampleCount; i++) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Get the total acceleration
    float acceleration = sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2));
    sum += acceleration;

    delay(100);  // Sample every 100ms for 5 seconds
  }

  return sum / sampleCount;
}

bool detectFall(float currentAcceleration) {
  // Check if the current acceleration is significantly below baseline and close to zero
  return (baselineAcceleration - currentAcceleration) > BASELINE_THRESHOLD && currentAcceleration < ACCELERATION_ZERO_THRESHOLD;
}

void activateAlert() {
  digitalWrite(ledPin, HIGH);  // Turn on LED
  digitalWrite(buzzerPin, HIGH);  // Activate buzzer
  delay(ALERT_DURATION);  // Keep alert active for 5 seconds
  digitalWrite(ledPin, LOW);  // Turn off LED
  digitalWrite(buzzerPin, LOW);  // Turn off buzzer
}