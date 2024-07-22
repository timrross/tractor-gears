
#include <CytronMotorDriver.h>

#define SHIFTER_REVERSE_PIN 17 // WHITE
#define SHIFTER_FORWARD_PIN 19 // GREEN
#define SHIFTER_FAST_PIN 21 // BLUE
#define ACCELERATOR_PIN 14

/**
 * Arduino D5  - Motor Driver PWM 1 Input
 * Arduino D4  - Motor Driver DIR 1 Input
 * Arduino D3  - Motor Driver PWM 2 Input
 * Arduino D2 - Motor Driver DIR 2 Input
 * Arduino GND - Motor Driver GND
 */

#define MOTOR1_PWM_PIN 5
#define MOTOR1_DIR_PIN 4 // PURPLE

#define MOTOR2_PWM_PIN 3 // YELLOW
#define MOTOR2_DIR_PIN 2 // PURPLE

#define DEBUG false

// Configure the motor driver.
CytronMD motor1(PWM_DIR, MOTOR1_PWM_PIN, MOTOR1_DIR_PIN); 
CytronMD motor2(PWM_DIR, MOTOR2_PWM_PIN, MOTOR2_DIR_PIN);


int currentPower = 0;
int targetPower = 0;
int acceleration = 10; // This is the ms delay between incrementing the power. 

void stop() {
  if (DEBUG) {
    Serial.println("Stop");
  }
  acceleration = 10; // Reset
  targetPower = 0;
}

void reverse() {
  if (DEBUG) {
    Serial.println("Reverse");
  }
  if (currentPower > 0) {
    acceleration = 3; 
  } else {
    acceleration = 15; 
  }
  targetPower = -95;
}

void forward() {
  if (DEBUG) {
    Serial.println("Forward");
  }
  acceleration = 10;
  targetPower = 127;
}

void fast() {
  if (DEBUG) {
    Serial.println("Fast");
  }
  acceleration = 3; // Reset
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
    delay(acceleration);
  }
  if (currentPower > targetPower) {
    currentPower--;
    delay(acceleration);
  }
  if (DEBUG) {
    delay(500);
  }
}
