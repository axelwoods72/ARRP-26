// ======================================================================
//  SESAME ROBOT — PWM & SERVO KINEMATICS
// ======================================================================
//  Goal: write the low-level servo layer that the full Sesame firmware
//  (sesame-firmware-main.ino + movement-sequences.h) is built on.
//
//  You will implement:
//    Part 1  Hardware timer allocation          (setupPWM)
//    Part 2  Degrees -> microseconds mapping    (angleToPulseUs)
//    Part 3  Attaching the 8 leg servos         (attachAllServos)
//    Part 4  Subtrim + staggered activation     (setServoAngle)
//    Part 5  Your first pose                    (runStandPose)
//
//  Search for "TODO" to find every place you need to write code.
//  Test with the Serial Monitor at 115200 baud (commands listed in setup()).
//
//  Library required: ESP32Servo  (Arduino Library Manager)
// ======================================================================

#include <Arduino.h>
#include <ESP32Servo.h>

// ----------------------------------------------------------------------
//  SERVO NAMES
//  These match movement-sequences.h. The number is the index into the
//  servos[] and servoPins[] arrays. Note the order is NOT simply L1..L4,
//  R1..R4 — it follows how the motors are wired to the board.
//    *1/*2 = hip joints, *3/*4 = foot/knee joints
// ----------------------------------------------------------------------
enum ServoName : uint8_t {
  R1 = 0,
  R2 = 1,
  L1 = 2,
  L2 = 3,
  R4 = 4,
  R3 = 5,
  L3 = 6,
  L4 = 7
};

const int NUM_SERVOS = 8;
Servo servos[NUM_SERVOS];

// ----------------------------------------------------------------------
//  PIN MAP — uncomment the line that matches YOUR board.
// ----------------------------------------------------------------------
// Sesame Distro Board V3:
// const int servoPins[NUM_SERVOS] = {4, 5, 6, 7, 10, 11, 12, 13};
// Sesame Distro Board V2 (legacy):
// const int servoPins[NUM_SERVOS] = {4, 5, 6, 7, 15, 16, 17, 18};
// Sesame Distro Board V1 (legacy):
// const int servoPins[NUM_SERVOS] = {15, 2, 23, 19, 4, 16, 17, 18};
// Lolin S2 Mini:
const int servoPins[NUM_SERVOS] = {1, 2, 4, 6, 8, 10, 13, 14};

// ----------------------------------------------------------------------
//  PWM CONSTANTS
// ----------------------------------------------------------------------
// TODO 0a: Hobby servos expect a new pulse every 20 ms. What frequency
//          (in Hz) is that? Set SERVO_FREQ_HZ accordingly.
const int SERVO_FREQ_HZ = 0;            // <-- fix me

// TODO 0b: Pulse widths (microseconds) for the ends of travel.
//          Standard 180° servos on Sesame:  0° -> 732 us, 180° -> 2929 us
//          270° servos (author's tested values): 833 us to 2167 us
//          Fill in the values for the servos YOU are using.
const int MIN_PULSE_US = 0;             // <-- fix me (pulse at 0°)
const int MAX_PULSE_US = 0;             // <-- fix me (pulse at 180°)

// ----------------------------------------------------------------------
//  CALIBRATION + POWER
// ----------------------------------------------------------------------
// Subtrim: a per-servo offset in degrees to correct for horns that are
// not mounted exactly at centre. Positive or negative, roughly -90..+90.
int8_t servoSubtrim[NUM_SERVOS] = {0, 0, 0, 0, 0, 0, 0, 0};

// Delay (ms) between consecutive servo commands. Moving 8 servos at the
// same instant can pull enough current to collapse the supply rail and
// brown out the ESP32. Default 20 ms; lower it if your supply is strong.
int motorCurrentDelay = 20;

// ======================================================================
//  PART 1 — HARDWARE TIMER ALLOCATION
// ======================================================================
//  The ESP32 generates PWM with a small number of hardware timers.
//  ESP32Servo shares them with every other PWM user (other servos, ESCs,
//  LED fades, tone(), etc.). Reserving timers 0–3 up front gives the
//  servos clean, high-resolution 50 Hz signals.
//
//  WARNING (from the project author): there are only 4 timers. Adding
//  extra PWM devices (e.g. two ESCs) can exhaust them and break other
//  features such as the Wi-Fi captive portal. If your custom firmware
//  shows network errors, check timer allocation first.
// ======================================================================
void setupPWM() {
  // TODO 1: Reserve hardware timers 0, 1, 2 and 3 for ESP32Servo.
  //         Hint: ESP32PWM::allocateTimer(n);

}

// ======================================================================
//  PART 2 — DEGREES -> MICROSECONDS (do the math yourself)
// ======================================================================
//  ESP32Servo's write(angle) does this conversion for you internally,
//  but you should understand it. This is a straight linear map:
//
//      pulse = MIN_PULSE + (angle / 180) * (MAX_PULSE - MIN_PULSE)
//
//  Questions to answer in your notebook:
//    a) What pulse width does 90° produce with 732–2929 us?
//    b) How many microseconds is ONE degree of rotation?
//    c) Why must angle be clamped before mapping?
// ======================================================================
int angleToPulseUs(int angleDeg) {
  // TODO 2a: Clamp angleDeg to 0..180.   Hint: constrain()

  // TODO 2b: Linearly map 0..180 to MIN_PULSE_US..MAX_PULSE_US and
  //          return the result.        Hint: Arduino's map()

  return 0;  // <-- replace
}

// ======================================================================
//  PART 3 — ATTACH THE SERVOS
// ======================================================================
//  For every servo:
//    1. Set its PWM period to SERVO_FREQ_HZ.
//    2. Attach it to its pin with your MIN/MAX pulse range, so that
//       write(0) and write(180) hit the true ends of travel.
// ======================================================================
void attachAllServos() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    // TODO 3a: servos[i].setPeriodHertz(...)

    // TODO 3b: servos[i].attach(pin, minPulse, maxPulse)

  }
  delay(10);
}

// ======================================================================
//  PART 4 — setServoAngle(): the ONE function every pose goes through
// ======================================================================
//  Every movement in movement-sequences.h calls this, so it must be safe:
//    1. Reject invalid channels (only 0..7 exist).
//    2. Add that servo's subtrim to the requested angle.
//    3. Clamp the result to 0..180 so we never command past the end stop.
//    4. Send the command to the servo.
//    5. Wait motorCurrentDelay ms (staggered activation) so servos start
//       one after another instead of all at once.
//
//  Note: the full firmware waits with delayWithFace() so the OLED face
//  and web server keep updating during the pause. We use plain delay()
//  here because this sketch has no display or Wi-Fi.
// ======================================================================
void setServoAngle(uint8_t channel, int angle) {
  // TODO 4a: Return immediately if channel is out of range.

  // TODO 4b: Compute adjustedAngle = angle + subtrim, clamped to 0..180.

  // TODO 4c: Command the servo. Choose ONE:
  //          servos[channel].write(adjustedAngle);
  //          servos[channel].writeMicroseconds(angleToPulseUs(adjustedAngle));
  //          (They should behave identically — try both and compare!)

  // TODO 4d: Staggered activation delay.

}

// ======================================================================
//  PART 5 — YOUR FIRST POSE
// ======================================================================
//  Use ONLY setServoAngle() and the ServoName labels (never raw numbers).
//  Target angles for the Sesame "stand" pose:
//      R1 135   R2  45   L1  45   L2 135
//      R4   0   R3 180   L3   0   L4 180
//  Notice the left and right sides mirror each other. Why? (Think about
//  how a servo on the left side is physically flipped vs. the right.)
// ======================================================================
void runStandPose() {
  Serial.println(F("STAND"));
  // TODO 5: Set all 8 servos to the stand pose.

}

// Challenge: write runRestPose() — what angles fold the legs flat?
// Compare your answer with movement-sequences.h when you're done.

// ======================================================================
//  SETUP / LOOP  (provided — no changes needed)
// ======================================================================
void handleSerial();

void setup() {
  Serial.begin(115200);
  delay(500);

  setupPWM();
  attachAllServos();

  Serial.println(F("--- Sesame Servo Lab ---"));
  Serial.println(F("  id,angle     e.g. 0,90    move one servo"));
  Serial.println(F("  all,angle    e.g. all,90  move every servo"));
  Serial.println(F("  stand                     run stand pose"));
  Serial.println(F("  trim,id,deg  e.g. trim,2,-5  set subtrim"));
  Serial.println(F("  delay,ms     e.g. delay,0    set motorCurrentDelay"));
  Serial.println(F("  pulse,angle  print angleToPulseUs(angle)"));
}

void loop() {
  handleSerial();
}

void handleSerial() {
  if (!Serial.available()) return;
  String in = Serial.readStringUntil('\n');
  in.trim();
  if (in.length() == 0) return;

  if (in.equalsIgnoreCase("stand")) { runStandPose(); return; }

  int c1 = in.indexOf(',');
  if (c1 < 0) { Serial.println(F("Bad command")); return; }
  String cmd = in.substring(0, c1);
  String rest = in.substring(c1 + 1);

  if (cmd.equalsIgnoreCase("all")) {
    int a = rest.toInt();
    for (int i = 0; i < NUM_SERVOS; i++) setServoAngle(i, a);
    Serial.printf("All -> %d deg\n", a);
  } else if (cmd.equalsIgnoreCase("trim")) {
    int c2 = rest.indexOf(',');
    int id = rest.substring(0, c2).toInt();
    int t  = rest.substring(c2 + 1).toInt();
    if (id >= 0 && id < NUM_SERVOS && t >= -90 && t <= 90) {
      servoSubtrim[id] = t;
      Serial.printf("Servo %d subtrim = %d\n", id, t);
    } else Serial.println(F("trim: id 0-7, deg -90..90"));
  } else if (cmd.equalsIgnoreCase("delay")) {
    motorCurrentDelay = max(0, (int)rest.toInt());
    Serial.printf("motorCurrentDelay = %d ms\n", motorCurrentDelay);
  } else if (cmd.equalsIgnoreCase("pulse")) {
    int a = rest.toInt();
    Serial.printf("%d deg -> %d us\n", a, angleToPulseUs(a));
  } else {
    int id = cmd.toInt();
    int a = rest.toInt();
    setServoAngle(id, a);
    Serial.printf("Servo %d -> %d deg\n", id, a);
  }
}
