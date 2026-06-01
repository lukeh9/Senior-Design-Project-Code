#include <Adafruit_MotorShield.h>
#include <Servo.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *actuator1 = AFMS.getMotor(1);
Adafruit_DCMotor *actuator2 = AFMS.getMotor(2);

Servo servo1;
Servo servo2;

const int buttonPin = 7;
bool lastButtonState = LOW;

int start = 90;

void setup() {
  AFMS.begin();
  pinMode(buttonPin, INPUT);
  
  servo1.attach(8);
  servo2.attach(9);
  
  servo1.write(start);
  servo2.write(start);
  
  actuator1->run(RELEASE);
  actuator2->run(RELEASE);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);
  
  // Detect button press
  if (lastButtonState == LOW && currentButtonState == HIGH) {
    runSequence();
  }
  
  lastButtonState = currentButtonState;
}

void runSequence() {
  // --- STEP 1: Servo sequence ---
  Serial.print("servo1 is running");
  servo1.write(start);
  delay(500);
  Serial.print("servo2 is running");
  servo2.write(start);
  delay(500);

  servo1.write(start+45);
  delay(1000);
  servo2.write(start+45);
  delay(1000);

  servo1.write(start-45);
  delay(1000);
  servo2.write(start-45);
  delay(1000);

  servo1.write(start);
  delay(500);
  servo2.write(start);
  delay(500);

  // --- STEP 2: Actuator extends ---
  actuator1->setSpeed(255);
  actuator2->setSpeed(255);
  actuator1->run(FORWARD);
  delay(5000);
  actuator2->run(FORWARD);
  delay(5000);          // Tune to your actuator stroke length
  actuator1->run(RELEASE);
  actuator2->run(RELEASE);
  delay(500);

  // --- STEP 3: Actuator retracts ---
  actuator1->setSpeed(255);
  actuator2->setSpeed(255);
  actuator1->run(BACKWARD);
  actuator2->run(BACKWARD);
  delay(5000);          // Same duration as extend
  actuator1->run(RELEASE);
  actuator2->run(RELEASE);
}