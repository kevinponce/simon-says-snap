#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Debounce.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 125
#define SERVOMAX 575

uint8_t servo1 = 0;
Debounce debounce1 = Debounce(2, 50);
boolean trapSet = true;
int number = 0;
boolean gameOver = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  debounce1.attach();

  randomSeed(analogRead(0));

  number = random(0, 4);

  pwm.begin();

  pwm.setPWMFreq(60);

  yield();
}

void release (int slot) {
  pwm.setPWM(slot, 0, SERVOMIN);
}

void reset(int slot) {
  pwm.setPWM(slot, 0, SERVOMAX);
}


void gameOverAction() {
  if (debounce1.pressed()) {
    trapSet = !trapSet;

    if (trapSet) {
      release(0); 
    } else {
      reset(0);
    }
  }
}

void action() {
  boolean correct = false;

  if (debounce1.pressed()) {
    int number_check =  random(0, 4);
    Serial.print(number);
    Serial.print(" == ");
    Serial.println(number_check);
    if (number == number_check) {
      gameOver = true;
      release(0);
    } else {
      number = random(0, 4);
    }
  }
}

void loop() {
  if (gameOver) {
    gameOverAction();
  } else {
    action();
  }
}
