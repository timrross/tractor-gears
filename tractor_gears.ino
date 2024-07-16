
#include <CytronMotorDriver.h>

#define SHIFTER_REVERSE_PIN 14 // WHITE
#define SHIFTER_FORWARD_PIN 16 // GREEN
#define SHIFTER_FAST_PIN 18 // BLUE
#define ACCELERATOR_PIN 15

/**
 * Arduino D6  - Motor Driver PWM 1 Input
 * Arduino D7  - Motor Driver DIR 1 Input
 * Arduino D10  - Motor Driver PWM 2 Input
 * Arduino D11 - Motor Driver DIR 2 Input
 * Arduino GND - Motor Driver GND
 */

#define MOTOR1_PWM_PIN 6
#define MOTOR1_DIR_PIN 7 // PURPLE

#define MOTOR2_PWM_PIN 10 // YELLOW
#define MOTOR2_DIR_PIN 11 // PURPLE

#define DEBUG false

// Configure the motor driver.
CytronMD motor1(PWM_DIR, MOTOR1_PWM_PIN, MOTOR1_DIR_PIN); 
CytronMD motor2(PWM_DIR, MOTOR2_PWM_PIN, MOTOR2_DIR_PIN);


int currentPower = 0;
int targetPower = 0;

void stop() {
  if (DEBUG) {
    Serial.println("Stop");
  }
  targetPower = 0;
}

void reverse() {
  if (DEBUG) {
    Serial.println("Reverse");
  }
  targetPower = -95;
}

void forward() {
  if (DEBUG) {
    Serial.println("Forward");
  }
  targetPower = 127;
}

void fast() {
  if (DEBUG) {
    Serial.println("Fast");
  }
  targetPower = 255;
}

void setup() {
  if (DEBUG) {
    Serial.begin(9600);
  }
  // put your setup code here, to run once:
  pinMode(SHIFTER_REVERSE_PIN, INPUT_PULLUP);
  pinMode(SHIFTER_FORWARD_PIN, INPUT_PULLUP);
  pinMode(SHIFTER_FAST_PIN, INPUT_PULLUP);
  pinMode(ACCELERATOR_PIN, INPUT_PULLUP);

  pinMode(MOTOR1_PWM_PIN, OUTPUT);
  pinMode(MOTOR1_DIR_PIN, OUTPUT);

  pinMode(MOTOR2_PWM_PIN, OUTPUT);
  pinMode(MOTOR2_DIR_PIN, OUTPUT);

  stop();
}

void loop() {
  if (DEBUG) {
    char buffer[40];
    sprintf(buffer, "%d, %d, %d, %d", digitalRead(SHIFTER_REVERSE_PIN), digitalRead(SHIFTER_FORWARD_PIN), digitalRead(SHIFTER_FAST_PIN), digitalRead(ACCELERATOR_PIN));
    Serial.println(buffer);
  }


  // Read the pins and set the target power.
  if (digitalRead(SHIFTER_REVERSE_PIN) == LOW) {
    reverse();
  } else if (digitalRead(SHIFTER_FAST_PIN) == LOW && digitalRead(SHIFTER_FORWARD_PIN) == LOW) {
    fast();
  } else if (digitalRead(SHIFTER_FORWARD_PIN) == LOW) {
    forward();
  } else {
    stop();
  }

  // Now check the accelterator. If it's not pressed then stop. (pin is pulled high = off when pressed)
  if (digitalRead(ACCELERATOR_PIN) == HIGH) {
    stop();
  }
  if (DEBUG) {
    Serial.println(currentPower);
  }
  motor1.setSpeed(currentPower);
  motor2.setSpeed(currentPower);

  // Now increase the power incrementally til the target.
  if (currentPower < targetPower) {
    currentPower++;
    delay(10);
  }
  if (currentPower > targetPower) {
    currentPower--;
    delay(10);
  }
  if (DEBUG) {
    delay(500);
  }
}
