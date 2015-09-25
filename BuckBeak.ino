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
ROPWM spike(0);
RODigitalIO pressureSwitch(0, INPUT);
ROSolenoid shooter(0);

void setup()
{
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
}

/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
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
    frontLeft = (frontLeft / maximum) * 127;
    frontRight = (frontRight / maximum) * 127;
    backLeft = (backLeft / maximum) * 127;
    backRight = (backRight / maximum) * 127;
  }

  if (pressureSwitch.read()) {
    spike.write(127);
  } else {
    spike.write(255);
  }

  // turn on spinner to shoot the frisbee
  if (usb.btnLShoulder()) {
    spinner.write(255);

    // shoot frisbee if motor is spinning
    if (usb.rTrigger()) {
      shooter.on();
    } else {
      shooter.off();
    }
  } else {
    spinner.write(127);
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
}

// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}
