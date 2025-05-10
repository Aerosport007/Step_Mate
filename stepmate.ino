// Haptic Walking Stick Project for Visually Impaired
// Uses ultrasonic sensor to detect obstacles and provides haptic feedback with distinct intensity levels

// Pin definitions
const int trigPin = 5;    // Trigger pin of HC-SR04
const int echoPin = 18;   // Echo pin of HC-SR04
const int motorPin = 23;  // Pin connected to transistor base for vibration motor

// Constants
const float speedOfSound = 0.034; // Speed of sound in cm/microsecond
const int maxDistance = 150;      // Maximum distance we want to measure (in cm) - turn off beyond this
const int minDistance = 10;       // Minimum distance for strongest vibration (in cm)

// Distance ranges and corresponding intensities (using full range)
const int NUM_RANGES = 4;
const int distanceRanges[NUM_RANGES] = {30, 70, 110, 150};  // Upper bound of each range in cm
const int intensityLevels[NUM_RANGES] = {255, 190, 125, 60}; // PWM values for each range - full spectrum

// Variables
long duration;
float distance;
bool motorActive = false;

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);
  
  // Configure pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin, OUTPUT);
  
  // Ensure motor is off initially - force it low
  digitalWrite(motorPin, LOW);
  
  Serial.println("Haptic Walking Stick initialized!");
  Serial.println("Motor will turn off beyond 150cm");
}

void loop() {
  // Measure distance
  distance = measureDistance();
  
  // Print distance to Serial monitor (for debugging)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Provide haptic feedback based on distance
  if (distance <= maxDistance) {
    // Get vibration intensity for the measured distance
    int vibrationIntensity = getVibrationIntensity(distance);
    
    // Print intensity value for debugging
    Serial.print("Vibration intensity: ");
    Serial.println(vibrationIntensity);
    
    // Apply vibration feedback
    applyVibration(vibrationIntensity);
    motorActive = true;
  } else {
    // Turn off vibration if object is beyond maximum distance
    if (motorActive) {
      Serial.println("No object within range - FORCING motor OFF");
      digitalWrite(motorPin, LOW);
      analogWrite(motorPin, 0);  // Force PWM to 0 too
      delay(10); // Small delay to ensure signal is sent
      digitalWrite(motorPin, LOW); // Double-ensure it's off
      motorActive = false;
    } else {
      Serial.println("No object within range - motor remains OFF");
    }
  }
  
  // Short delay before next measurement
  delay(100);
}

// Function to measure distance using ultrasonic sensor
float measureDistance() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigger pin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo pin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  float calculatedDistance = duration * speedOfSound / 2;
  
  // Return raw distance, even if beyond maxDistance (we'll handle that in the loop)
  if (calculatedDistance <= 0) {
    return maxDistance + 50; // Return something clearly beyond max if reading is invalid
  }
  
  return calculatedDistance;
}

// Get vibration intensity based on distance using distinct ranges
int getVibrationIntensity(float distance) {
  // If extremely close, use maximum intensity
  if (distance <= minDistance) {
    return 255; // Maximum PWM value
  }
  
  // Find the appropriate intensity level based on distance range
  for (int i = 0; i < NUM_RANGES; i++) {
    if (distance <= distanceRanges[i]) {
      return intensityLevels[i];
    }
  }
  
  // Beyond maximum range, no vibration
  return 0;
}

// Apply vibration with specific intensity
void applyVibration(int intensity) {
  if (intensity > 0) {
    // Use PWM to control vibration intensity
    analogWrite(motorPin, intensity);
  } else {
    // Turn off vibration
    digitalWrite(motorPin, LOW);
  }
}