#include "NewPing.h"
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 11 
#define MAX_DISTANCE 50 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

const int leds[] = {7, 6, 5, 4, 3};
#define NUM_LEDS 5

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  float mesafe = sonar.ping_cm();
  int delayTime = calculateDelay(mesafe);

  Serial.print("Mesafe: ");
  Serial.print(mesafe);
  Serial.println(" cm");

  controlLedsAndBuzzer(mesafe, delayTime);
}

int calculateDelay(float mesafe) {
  int delayTime = map(mesafe, 5, 100, 50, 1000);
  return constrain(delayTime, 50, 1000);
}

void controlLedsAndBuzzer(float mesafe, int delayTime) {
  turnOffAllLeds();

  if (mesafe <= 50 && mesafe > 40) {
    updateLeds(1);
  } else if (mesafe <= 40 && mesafe > 30) {
    updateLeds(2);
  } else if (mesafe <= 30 && mesafe > 20) {
    updateLeds(3);
  } else if (mesafe <= 20 && mesafe > 10) {
    updateLeds(4);
  } else if (mesafe <= 10 && mesafe > 2) {
    updateLeds(5);
  }
  if (mesafe > 2 && mesafe <= 50) {
    playBuzzer(delayTime);
  }
}

void updateLeds(int ledCount) {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(leds[i], HIGH);
  }
}

void turnOffAllLeds() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void playBuzzer(int delayTime) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(delayTime);
  digitalWrite(BUZZER_PIN, LOW);
  delay(delayTime);
}
