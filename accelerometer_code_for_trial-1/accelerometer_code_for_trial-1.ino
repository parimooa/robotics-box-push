// These two includes are necessary to read
// the LSM6DS33 (accelerometer and gyro)
# include <Wire.h>
# include <LSM6.h>

// LSM6 is a class.  We create an instance
// of this class called "imu".  We will then
// use imu to access the device by method
// functions and variables inside the class.
LSM6 imu;

void setup() {

  // Start the wire library for i2c.
  // Note: do not add this command into
  // a class constructor. It must occur
  // (or be called) from setup().
  Wire.begin();

  // Serial for debug output
  Serial.begin(9600);
  Serial.println("***RESET***");
  delay(1000);

  // Check the IMU initialised ok.
  if (!imu.init() ) {  // no..? :(

    // Since we failed to communicate with the
    // IMU, we put the robot into an infinite
    // while loop and report the error.
    while (1) {
      Serial.println("Failed to detect and initialize IMU!");
      delay(1000);
    }
  }

  // IMU initialise ok!
  // Set the IMU with default settings.
  imu.enableDefault();

} // End of setup()



// Simple loop to report all the readings from
// the accelerometer and gyro
// imu.a = accelerometer
// imu.g = gyro
void loop() {

  // Make a read of the sensor.
  imu.read();

  // Report values
  Serial.print("A: ");
  Serial.print(imu.a.x);
  Serial.print(" ");
  Serial.print(imu.a.y);
  Serial.print(" ");
  Serial.println(imu.a.z);
  /*
  Serial.print("\t G:  ");
  Serial.print(imu.g.x);
  Serial.print(" ");
  Serial.print(imu.g.y);
  Serial.print(" ");
  Serial.println(imu.g.z);*/

  // Short delay to keep things
  // slow enough to observe.
  // There is a limit to how fast you
  // can make i2c readings.
  delay(100);


} // End of loop()
