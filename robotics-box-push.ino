#define EMIT_PIN 11
#define BR 5
#define BL 4

#include "motors.h"
#include "bump_sensor.h"


RoboMotors motor;
BumpSensor sensor;

void setup() {
  sensor.initialise();
  //  // put your setup code here, to run once:
  //  pinMode(BL, INPUT);
  //
  //  //emitter pin for bump sensor
  //  pinMode(EMIT_PIN, OUTPUT);
  //  digitalWrite(BL, LOW);
  Serial.begin(9600);
  delay(1000);
  Serial.println("****RESET****");
 moveMotorForward();

}

void loop() {
  moveMotorForward();
  delay(2000);
  sensor.readBumpSensor();
  float rbs = sensor.bump_sensor_reading[0];
  float lbs = sensor.bump_sensor_reading[1];

  for (int i = 0; i < 2; i++) {
    Serial.print(sensor.bump_sensor_reading[i]);
    Serial.print(",");

  }
  Serial.println("");
  sensor.weighted_measure();
  if (sensor.bump_sensor_reading[0] > 720 && sensor.bump_sensor_reading[1] < 840) {
    //    Serial.println("RB: Activated, LB:Not Activated");
    Serial.println("Object is in Right of Robot");
    
    moveMotorRight();
  } else if (sensor.bump_sensor_reading[0] < 720 && sensor.bump_sensor_reading[1] > 840) {
    //    Serial.println("RB:Not Activated, LB:Activated");
    Serial.println("Object is in left of Robot");
    moveMotorLeft();

  } else if (sensor.bump_sensor_reading[0] >= 720 && sensor.bump_sensor_reading[1] >= 840) {
    //    Serial.println("RB:Activated, LB:Activated");
    Serial.println("Object is in centre");
    moveMotorForward();
  } else {
    Serial.println("Object not detected");
    stopMotor();
    delay(1000);
    
    
    
  }

  delay(100);



}
void stopMotor() {
  motor.setMotorPower(0, 0);
}
void moveMotorForward() {
  float turn = sensor.weighted_measure();
  float left_wheel_speed = forwardBias - turn;
  float right_wheel_speed = forwardBias + turn;
  motor.setMotorPower(left_wheel_speed, right_wheel_speed);
}
void moveMotorLeft() {
  float turn = sensor.weighted_measure();
  float left_wheel_speed = forwardBias - turn;
  float right_wheel_speed = forwardBias + turn;
  motor.setMotorPower(-left_wheel_speed, right_wheel_speed);
}

void moveMotorRight() {
  float turn = sensor.weighted_measure();
  float left_wheel_speed = forwardBias - turn;
  float right_wheel_speed = forwardBias + turn;
  motor.setMotorPower(left_wheel_speed, -right_wheel_speed);

}
