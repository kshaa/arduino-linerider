#include <Servo.h>
// LEDs (which will provide light for light sensors to detect the line on table)
// aren't even in code, because they should always be on - just plug straight into power

const int drivePin1 = 10; // Left, when facing forwards
const int drivePin2 = 11; // Right, when facing forwards

const int visionPin1 = A0;
const int visionPin2 = A1;
const int visionPin3 = A2;
const int visionPin4 = A3;
const int visionPin5 = A4;
const int lineTreshold = 300;

const bool debugMode = true;

void setup() {
  // Logging
  Serial.begin(9600);

  // Drive motors
  pinMode(drivePin1, OUTPUT);
  pinMode(drivePin2, OUTPUT);

  // Photoresistors
  pinMode(visionPin1, INPUT);
  pinMode(visionPin2, INPUT);
  pinMode(visionPin3, INPUT);
  pinMode(visionPin4, INPUT);
  pinMode(visionPin5, INPUT);
}

void loop() {
  // Get "vision" data!
  // What do the light sensors say?
  // Is a line being seen in some visionPin?
  bool seeLine1 = analogRead(visionPin1) < lineTreshold;
  bool seeLine2 = analogRead(visionPin2) < lineTreshold;
  bool seeLine3 = analogRead(visionPin3) < lineTreshold;
  bool seeLine4 = analogRead(visionPin4) < lineTreshold;
  bool seeLine5 = analogRead(visionPin5) < lineTreshold;

  // log line seeing info
  if (debugMode) {
    Serial.print(seeLine1);
    Serial.print(seeLine2);
    Serial.print(seeLine3);
    Serial.print(seeLine4);
    Serial.print(seeLine5);
    Serial.println();
  }

  // Act based on vision
  if (seeLine3) {
    // Middle vision sees line - keep going forward!
    analogWrite(drivePin1, 255);
    analogWrite(drivePin2, 255);
  } else {
    // If some other visions see line - slow down & try to steer so we're back on line
    if (seeLine1) {
      analogWrite(drivePin1, 230);
      analogWrite(drivePin2, 255);  
    }
    if (seeLine2) {
      analogWrite(drivePin1, 240);
      analogWrite(drivePin2, 255);
    }
    if (seeLine4) {
      analogWrite(drivePin1, 255);
      analogWrite(drivePin2, 240);
    }
    if (seeLine5) {
      analogWrite(drivePin1, 255);
      analogWrite(drivePin2, 230);
    }
  }
}