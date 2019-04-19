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
//const byte MOTOR_1 = 10;

motor_driver motor;
xbee xb;
/**
 * @brief Automatically runs when Arduino initializes.
 */
void setup() {
  Serial.begin(9600);
//  Serial.println("NSL 18-19 Deployment Test\n");

  pinMode(SOL_1, OUTPUT);
  //pinMode(MOTOR_1, OUTPUT);
  digitalWrite(SOL_1, HIGH);
}


/**
 * @brief Menu for motor deployment on proper signal and an emergency stop.
 *
 * @param c Character corresponding to input key.
 */
void menu(char c) {
  switch (c) {
    case '+':
      Serial.print("1");
      digitalWrite(SOL_1, LOW);
      delay(1000*10);
      motor.setSpeedPercent(100,100);
      Serial.print("2");
      delay(3*1000);
      digitalWrite(SOL_1, HIGH);
      delay(1000*22); //25 sec
      motor.setSpeedPercent(0,0);
      Serial.print("3");
      delay(1000*15); // 15 sec
      Serial.print("4");
      Serial.print("+");
      break;
    case '-':
      //Serial.print("STOP");
      digitalWrite(SOL_1, HIGH);
      motor.setSpeedPercent(0,0);
      break;
    case 'a':
      //Serial.print("STOP");
      digitalWrite(SOL_1, LOW);
      break;
    case 's':
      motor.setSpeedPercent(0,0);
     // Serial.print(" ");
      break;
    case ',':
      motor.setSpeedPercent(-100, -100);
      break;
    case '.':
      motor.setSpeedPercent(100, 100);
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
