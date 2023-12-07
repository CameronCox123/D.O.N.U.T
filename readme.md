# Open Melt 2

Open Melt is an open-source translational drift (aka "melty brain") robot controller project.  

A translational drift robot spins its entire body using its drive wheel(s), but is still capable of directional control by modulating motor power at certain points each rotation.  To achieve this - the rate of rotation must be tracked.

<div align="center">
<table class="center"><tr><td align="center">
<a href="./antweight_reference_platform/"><img src="./images/plastic_ant.jpg" alt="drawing" width="230"/><br>Antweight Reference Platform</a</td>
<td valign="center"><img src="./images/rcf_equation.png" alt="drawing" width="250"/></td>
<td align="center"><img src="./images/melt_demo.gif" alt="drawing" width="320"/><br>~2300rpm</td>
</td></tr></table></div>

Open Melt uses an accelerometer to calculate the rate of rotation based on G-forces around a given radius (centrifugal force).  For example - an accelerometer mounted 4cm from the center of rotation experiencing 145g can be [calculated](https://druckerdiagnostics.com/g-force-calculator/) to indicate 1800rpm rotation.

An LED is turned on once per rotation - giving the appearance of the "front" of the robot.  This allows the driver to see the expected direction of translation.  The user can adjust the heading beacon by moving the remote control left or right.  This also allows for steering and correction of minor tracking errors.

This system can work with robots using either one or two drive motors.

#### For a complete parts list, 3d print files and build notes see the ["antweight reference platform"](./antweight_reference_platform/).


## General Hardware Requirements

- Arduino Micro (or other Atmega32u4 5v 16MHz Arduino / compatible)
- [H3LIS331](https://www.st.com/resource/en/datasheet/h3lis331dl.pdf) 400g accelerometer (recommended: [Adafruit H3LIS331 breakout](https://www.adafruit.com/product/4627))
- RC Transmitter / Receiver 
- Heading LED
- Motor Driver(s)
- Motor(s)

The HSLI311 is a 3v part - but the Adafruit breakout includes a 3v<->5v level converter to make interfacing with the Arduino easy.  Alternatively, [Sparkfun's H3LIS331DL Breakout](https://www.sparkfun.com/products/14480) has been verified to work when used in conjunction with the [SparkFun 3v<->5v Logic Level Converter](https://www.sparkfun.com/products/12009).

Use of an **Atmega328-based Arduino is not supported** due to lack of adequate interrupt pins.
  

## 1 vs. 2 Wheels
Open Melt generates signals for 2 motors independent of how many are connected.  There are no configuration changes needed. Motor 2 is powered for the same portion of each rotation as motor 1 (trailing 180 degrees out of phase).

<div align="center">
<table class="center"><tr><td>
<img src="./images/1wheel.gif" alt="drawing" width="230"/></td>
<td><img src="./images/bounce.gif" alt="drawing" width="230"/></td>

<td><img src="./images/mbfinal.jpg" alt="drawing" width="230"/></td>
</td></tr></table></div>

In a 1 wheel robot - the unsupported end scrapes the ground during spin-up - but then levitates when it reaches speed.  

In some 1 wheel robots - oscillation / bouncing has been observed at higher speeds - which can reduce translational control.  This phenomena is not fully understood - but may be caused by too-soft wheels deforming / shifting off the center of the hub.  Conversely - harder wheels may cause this problem when they bounce off imperfections in the floor.  

Robots with lower ground clearance seem to experience this problem less.  The reference platform is fairly stable up to about 2800rpm.

2 wheel designs seem less prone to these issues (but are not as cool looking).

## Accelerometer Placement
The accelerometer must be positioned so that it experiences no more than 400g at the robot's anticipated max rotation speed. A [centrifuge calculator](https://druckerdiagnostics.com/g-force-calculator/) may be used to determine this.

Open Melt provides an interactive setup routine that makes precise placement or orientation of the accelerometer unnecessary.

Alignment of the accelerometer off-axis will result in a linear error - which has the same effect as reducing the radius of rotation.  The software also corrects for installing the accelerometer 180 degrees rotated.

## Motor Driver(s) / Throttle Control

Open Melt can generate either a simple on / off motor signal - or provide a 0-100% 490Hz PWM signal.

Either kind of signal may be fed directly to a MOSFET or motor controller that accepts 5v logic-level input.

The reference platform uses a RFP30N06LE N-Channel MOSFET.

Brushless RC motor controllers that support high-speed 490Hz PWM may work with Open Melt.  A "Hobbypower 30a" brushless controller running the [SimonK firmware](https://github.com/sim-/tgy) has been tested and found to work.  Other controllers running SimonK firmware may also work.

Open Melt supports a few different configurations to control throttle / rotation speed.  See melty_config.h for configuration options.

## Heading LED

The heading LED should installed at a location along the perimeter of the robot where it can be viewed at any angle while driving.  Open Melt's interactive configuration can adjust for any placement.

The [Arduino Micro is capable of 20ma per I/O pin](https://store.arduino.cc/products/arduino-micro#:~:text=Each%20pin%20can%20provide%20or,permanent%20damage%20to%20the%20microcontroller) - so a resistor must be used to limit LED current.  The 100ohm resistor in the schematic is a good value for blue LEDs.  Values for other color LEDs may be determined using an [LED Series Resistor Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-led-series-resistor).

Selecting an LED with a wide viewing angle will help maximize visibility.

20ma is surprisingly bright - but if you need better visibility - a larger LED may be driven using a MOSFET.

## Schematic / Supporting Components

A 10:1 voltage divider is implemented using 2 resistors for measuring battery voltage.

The 4700uF capacitor is required across the 5v power bus to assure motor noise does not cause power fluctuations (and unwanted reboots).

If using a MOSFET - an appropriately sized Schottky diode *must* be installed across the motor leads. 

The receiver and accelerometer are powered via the Arduino's 5v regulator (rated 7-12v input).  Practically - this seems to work well enough with either a 7.4 or 11.1v LiPo battery.  For higher voltages - a dedicated voltage regulator should be used.

<img src="./openmelt_schematic/schematic.jpg" alt="drawing" width="600"/>


<img src="./images/internals_labelled.jpg" alt="drawing" width="600"/>

## Remote Control
Open Melt is controlled using a standard hobby RC control system.  3-channels are required (throttle, forward-back and left-right).

Be sure to choose a receiver that supports fail-safe and is configured to set the throttle to 0% (or no signal) in event of radio loss. **Verify it works correctly**. 

The [FlySky i6 transmitter ](https://www.flysky-cn.com/i6-gaishu) and [FlySky iA6 receiver](https://www.flysky-cn.com/ia6-canshu) are inexpensive options that work well (and support fail-safe).

## Safety / Disclaimer

**Building and operating a robot of this type, even in smaller versions, is inherently dangerous. By choosing to use the provided code and plans, you acknowledge the risks involved.  The creator of these plans cannot be held responsible for any injuries, damages, or losses that may result from the use of this project.**

A few mechanisms are implemented with the intent of improving safety.

If no RC updates are received for ~1 second - the robot should spin down.

A [watchdog timer](https://github.com/adafruit/Adafruit_SleepyDog) is used - so if the code unexpectedly becomes trapped - the Arduino should reboot (and the robot should enter an unpowered state).

At boot-up - it is verified that the RC signal is both good - and that the throttle is at 0% for ~1 second.  This means that if the robot reboots unexpectedly - it can not be spun up again until the driver lowers the throttle for ~1 second.  This behavior may be disabled (see melty_config.h).

It should be noted that MOSFET drivers can fail in a "closed" state.  This means that they will drive the motor until the battery runs out.


## Users Guide
 - Work in progress...
