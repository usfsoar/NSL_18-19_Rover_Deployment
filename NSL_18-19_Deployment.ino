/**
 * @file NSL_18-19_Deployment.ino
 * @brief Main arduino file for the deployment system used for the NSL_18-19 competition
 */
#include <Arduino.h>
#include "xbee.h"
#include "motor_driver.h"

/**
 * @brief SOL_1 controls solenoids, MOTOR_1 controls deployment motor
 */
const byte SOL_1 = 8;
const byte MOTOR_1 = 10;

motor_driver motor;
xbee xb;
/**
 * @brief Automatically runs when Arduino initializes.
 */
void setup() {
  Serial.begin(9600);
  Serial.println("NSL 18-19 Deployment Test\n");

  pinMode(SOL_1, OUTPUT);
  pinMode(MOTOR_1, OUTPUT);
}


/**
 * @brief Menu for motor deployment on proper signal and an emergency stop.
 *
 * @param c Character corresponding to input key.
 */
void menu(char c) {
  switch (c) {
    case '7':
      Serial.print("SOL ON LOW\n");
      digitalWrite(SOL_1, LOW);
      break;
    case '8':
      Serial.print("SOL ON HIGH\n");
      digitalWrite(SOL_1, HIGH);
      break;
    case '9':
      delay(500);
      Serial.print("MOTOR FORWARD\n");
      motor.setSpeedPercent(100,100);
      break;
    case '0':
      Serial.print("MOTOR REVERSE\n ");
      motor.setSpeedPercent(-100,-100);
      break;
    case ' ':
      Serial.print("STOP");
      motor.setSpeedPercent(0,0);
      break;
  }
}

/**
 * @brief Automatically loops while Arduino is running.
 *
 */
void loop() {
  menu(xb.readInput());
  delay(10);
}
