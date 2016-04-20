#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <RobotOpenSH.h>

/* I/O Setup */
ROJoystick usb(1);         // Joystick #1
ROPWM frontLeftMotor(0);
ROPWM frontRightMotor(1);
ROPWM backLeftMotor(2);
ROPWM backRightMotor(3);
ROPWM spinner(4);
RODigitalIO pressureSwitch(0, INPUT);
RODigitalIO spike(1, OUTPUT);
ROSolenoid shooter_back(0);
ROSolenoid shooter_front(1);
ROTimer shotTimer;

void setup()
{
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
  shotTimer.queue(0);
}

/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  
  if (pressureSwitch.read()) {
    spike.off();
  } else {
    spike.on();
  }

  // turn on spinner to shoot the frisbee
  if (usb.btnLShoulder()) {
    spinner.write(255);

    // shoot frisbee if motor is spinning  
    if (usb.rTrigger()) {
      shooter_back.off();
      shooter_front.on();
      shotTimer.queue(250);
    } else {
      shooter_back.on();
      shooter_front.off();
    }
  } else {
    spinner.write(127);
  }

  if (shotTimer.ready()) {
      shooter_back.on();
      shooter_front.off(); 
  }

	// I totally just copied all of the mecanum drive code from Robot Open
  // get desired translation and rotation, scaled to [-127..128] (0 neutral)
  int x = usb.leftX() - 127;
  int y = (255 - usb.leftY()) - 127;
  int rotate = usb.rightX() - 127;

  // calculate wheel throttles (Robot Open)
  int frontLeft = x + y + rotate;
  int frontRight = x - y + rotate;
  int backLeft = -x + y + rotate;
  int backRight = -x - y + rotate;

  // normalize wheel throttles (Robot Open)
  int maximum = max(max(abs(frontLeft), abs(frontRight)), max(abs(backLeft), abs(backRight)));
  if (maximum > 127) {
    frontLeft = frontLeft * 127 / maximum;
    frontRight = frontRight * 127 / maximum;
    backLeft = backLeft * 127 / maximum;
    backRight = backRight * 127 / maximum;
  }

  // Set PWMs, shifted back to [0..255] (Robot Open)
  frontLeftMotor.write(frontLeft + 127);
  frontRightMotor.write(frontRight + 127);
  backLeftMotor.write(backLeft + 127);
  backRightMotor.write(backRight + 127);
}

/* This is called while the robot is disabled
 * PWMs and Solenoids are automatically disabled
 */
void disabled() {
  // safety code
}

/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 */
void timedtasks() {
  RODashboard.publish("Uptime Seconds", ROStatus.uptimeSeconds());

  if (pressureSwitch.read()) {
    spike.off();
  } else {
    spike.on();
  }
}

// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}
