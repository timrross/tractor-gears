#define SHIFTER_REVERSE_PIN 14 // WHITE
#define SHIFTER_FORWARD_PIN 16 // GREEN
#define SHIFTER_FAST_PIN 18 // BLUE
#define ACCELERATOR_PIN 15

#define MOTOR1_RPWM_PIN 5 // GREEN
#define MOTOR1_LPWM_PIN 6 // YELLOW
#define MOTOR1_R_EN_PIN 7 // PURPLE
#define MOTOR1_L_EN_PIN 8 // BLUE

#define MOTOR2_RPWM_PIN 9 // GREEN
#define MOTOR2_LPWM_PIN 10 // YELLOW
#define MOTOR2_R_EN_PIN 11 // PURPLE
#define MOTOR2_L_EN_PIN 12 // BLUE

int currentPower = 0;
int targetPower = 0;

void stop() {
  digitalWrite(MOTOR1_R_EN_PIN, LOW);
  digitalWrite(MOTOR1_L_EN_PIN, LOW);
  digitalWrite(MOTOR2_R_EN_PIN, LOW);
  digitalWrite(MOTOR2_L_EN_PIN, LOW);

  digitalWrite(MOTOR1_RPWM_PIN, LOW);
  digitalWrite(MOTOR1_LPWM_PIN, LOW);
  digitalWrite(MOTOR2_RPWM_PIN, LOW);
  digitalWrite(MOTOR2_LPWM_PIN, LOW);
}

void start() {
  //Serial.println("Start");
  digitalWrite(MOTOR1_L_EN_PIN, HIGH);
  digitalWrite(MOTOR1_R_EN_PIN, HIGH);
  digitalWrite(MOTOR2_L_EN_PIN, HIGH);
  digitalWrite(MOTOR2_R_EN_PIN, HIGH);
}

void reverse() {
  //Serial.println("Reverse");
  targetPower = 95;
  analogWrite(MOTOR1_RPWM_PIN, 0);
  analogWrite(MOTOR1_LPWM_PIN, currentPower);
  analogWrite(MOTOR2_RPWM_PIN, 0);
  analogWrite(MOTOR2_LPWM_PIN, currentPower);
}

void forward() {
  //Serial.println("Forward");
  targetPower = 127;
  //Serial.println(currentPower);
  analogWrite(MOTOR1_RPWM_PIN, currentPower);
  analogWrite(MOTOR1_LPWM_PIN, 0);
  analogWrite(MOTOR2_RPWM_PIN, currentPower);
  analogWrite(MOTOR2_LPWM_PIN, 0);
}

void fast() {
  //Serial.println("Fast");
  targetPower = 255;
  analogWrite(MOTOR1_RPWM_PIN, currentPower);
  analogWrite(MOTOR1_LPWM_PIN, 0);
  analogWrite(MOTOR2_RPWM_PIN, currentPower);
  analogWrite(MOTOR2_LPWM_PIN, 0);
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(SHIFTER_REVERSE_PIN, INPUT_PULLUP);
  pinMode(SHIFTER_FORWARD_PIN, INPUT_PULLUP);
  pinMode(SHIFTER_FAST_PIN, INPUT_PULLUP);
  pinMode(ACCELERATOR_PIN, INPUT_PULLUP);

  pinMode(MOTOR1_RPWM_PIN, OUTPUT);
  pinMode(MOTOR1_LPWM_PIN, OUTPUT);
  pinMode(MOTOR1_R_EN_PIN, OUTPUT);
  pinMode(MOTOR1_L_EN_PIN, OUTPUT);

  pinMode(MOTOR2_RPWM_PIN, OUTPUT);
  pinMode(MOTOR2_LPWM_PIN, OUTPUT);
  pinMode(MOTOR2_R_EN_PIN, OUTPUT);
  pinMode(MOTOR2_L_EN_PIN, OUTPUT);
  stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  // char buffer[40];
  // sprintf(buffer, "%d, %d, %d, %d", digitalRead(SHIFTER_REVERSE_PIN), digitalRead(SHIFTER_FORWARD_PIN), digitalRead(SHIFTER_FAST_PIN), digitalRead(ACCELERATOR_PIN));
  // Serial.println(buffer);
  //stop();

  // Read the pins and set the target power.
  if (digitalRead(SHIFTER_REVERSE_PIN) == LOW) {
    reverse();
  } else if (digitalRead(SHIFTER_FAST_PIN) == LOW && digitalRead(SHIFTER_FORWARD_PIN) == LOW) {
    fast();
  } else if (digitalRead(SHIFTER_FORWARD_PIN) == LOW) {
    forward();
  }

  // Now check the accelterator. If it's not pressed then override the target power with 0
  if (digitalRead(ACCELERATOR_PIN) == LOW) {
    start();
  } else if (digitalRead(ACCELERATOR_PIN) == HIGH) {
    targetPower = 0;
    if (currentPower == 0) {
      stop();
    }
  }

  // Now increase the power incrementally til the target.
  if (currentPower < targetPower) {
    currentPower++;
    delay(15);
  }
  if (currentPower > targetPower) {
    currentPower--;
    delay(2);
  }

  // delay(50);
  // Serial.println(currentPower);
}
