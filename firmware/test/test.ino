// ======================================================================
//  ARRP-26 TEST FIRMWARE
//  All 8 servos + SSD1306 OLED + AP web server on Lolin S2 Mini
//
//  Libraries required (install via Arduino Library Manager):
//    - ESP32Servo
//    - Adafruit SSD1306
//    - Adafruit GFX Library
// ======================================================================

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

// ----------------------------------------------------------------------
//  AP CREDENTIALS
// ----------------------------------------------------------------------
const char *AP_SSID = "ARRP-26";
const char *AP_PASS = "arrp2026";

// ----------------------------------------------------------------------
//  I2C PINS (S2 Mini)
// ----------------------------------------------------------------------
#define I2C_SDA 33
#define I2C_SCL 35

// ----------------------------------------------------------------------
//  SERVO PINS (S2 Mini)
// ----------------------------------------------------------------------
#define NUM_SERVOS 8

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

const int servoPins[NUM_SERVOS] = {1, 2, 4, 6, 8, 10, 13, 14};

// ----------------------------------------------------------------------
//  PWM CONSTANTS
//  Standard 180° servo: 732–2929 us
//  If your servos are 270°, use: 833–2167 us
// ----------------------------------------------------------------------
const int SERVO_FREQ_HZ = 50;
const int MIN_PULSE_US = 732;
const int MAX_PULSE_US = 2929;

// ----------------------------------------------------------------------
//  CALIBRATION
// ----------------------------------------------------------------------
int8_t servoSubtrim[NUM_SERVOS] = {0, 0, 0, 0, 0, 0, 0, 0};
int motorCurrentDelay = 20; // ms between each servo command

// ----------------------------------------------------------------------
//  OBJECTS
// ----------------------------------------------------------------------
Servo servos[NUM_SERVOS];
Adafruit_SSD1306 display(128, 64, &Wire, -1);
WebServer server(80);

// ======================================================================
//  SERVO LAYER
// ======================================================================

void setupPWM() {
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
}

void attachAllServos() {
	for (int i = 0; i < NUM_SERVOS; i++) {
		servos[i].setPeriodHertz(SERVO_FREQ_HZ);
		servos[i].attach(servoPins[i], MIN_PULSE_US, MAX_PULSE_US);
	}
	delay(10);
}

void setServoAngle(uint8_t channel, int angle) {
	if (channel >= NUM_SERVOS)
		return;
	int adjusted = constrain(angle + servoSubtrim[channel], 0, 180);
	servos[channel].write(adjusted);
	delay(motorCurrentDelay);
}

// ======================================================================
//  POSES
// ======================================================================

void poseStand() {
	Serial.println("Pose: stand");
	setServoAngle(R1, 135);
	setServoAngle(R2, 45);
	setServoAngle(L1, 45);
	setServoAngle(L2, 135);
	setServoAngle(R4, 0);
	setServoAngle(R3, 180);
	setServoAngle(L3, 0);
	setServoAngle(L4, 180);
}

void poseLayDown() {
	Serial.println("Pose: lay down");
	// TODO: tune these angles once robot is assembled
	for (int i = 0; i < NUM_SERVOS; i++)
		setServoAngle(i, 90);
}

void poseWave() {
	Serial.println("Pose: wave");
	// TODO: define wave sequence
	poseStand();
	setServoAngle(R1, 90);
	delay(500);
	setServoAngle(R1, 135);
}

// ======================================================================
//  TEST
// ======================================================================

void poseTest() {
	Serial.println("Pose: test");

	// ---- PASTE YOUR SERVO SEQUENCE HERE ----

	// ----------------------------------------
}

const unsigned char face_test[] PROGMEM = {
    // ---- PASTE YOUR BITMAP HERE ----

    // --------------------------------
};

// ======================================================================
//  WEB FRONTEND (inline HTML)
// ======================================================================

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ARRP-26 Test</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: sans-serif;
      background: #111;
      color: #fff;
      text-align: center;
      padding: 40px 20px;
    }
    h1 { margin-bottom: 8px; }
    p.sub { color: #888; font-size: 13px; margin-bottom: 40px; }
    h2 {
      font-size: 12px;
      text-transform: uppercase;
      letter-spacing: 2px;
      color: #666;
      margin: 30px 0 12px 0;
    }
    .group {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 10px;
      max-width: 300px;
      margin: 0 auto;
    }
    button {
      padding: 16px;
      font-size: 15px;
      border: none;
      border-radius: 10px;
      color: #fff;
      cursor: pointer;
      transition: opacity 0.1s;
    }
    button:active { opacity: 0.7; }
    .btn-servo { background: #ff8c42; }
    .btn-face  { background: #5b8dd9; }
    .btn-test  { background: #3dba6f; }
    #status {
      margin-top: 24px;
      font-size: 12px;
      color: #555;
    }
  </style>
</head>
<body>
  <h1>ARRP-26</h1>
  <p class="sub">Test Interface</p>

  <h2>Servo Commands</h2>
  <div class="group">
    <button class="btn-servo" onclick="cmd('pose','stand')">Stand</button>
    <button class="btn-servo" onclick="cmd('pose','lay_down')">Lay Down</button>
    <button class="btn-servo" onclick="cmd('pose','wave')">Wave</button>
  </div>

  <h2>OLED Face</h2>
  <div class="group">
    <button class="btn-face" onclick="cmd('face','happy')">Happy</button>
    <button class="btn-face" onclick="cmd('face','sad')">Sad</button>
    <button class="btn-face" onclick="cmd('face','sleepy')">Sleepy</button>
    <button class="btn-face" onclick="cmd('face','cute')">Cute</button>
  </div>

  <h2>Your Tests</h2>
  <div class="group">
    <button class="btn-test" onclick="cmd('pose','test')">Test Pose</button>
    <button class="btn-test" onclick="cmd('face','test')">Test Face</button>
  </div>

  <p id="status">ready</p>

  <script>
    function cmd(type, value) {
      document.getElementById('status').textContent = type + ': ' + value + '...';
      fetch('/cmd?' + type + '=' + value)
        .then(() => { document.getElementById('status').textContent = 'ok'; })
        .catch(() => { document.getElementById('status').textContent = 'error'; });
    }
  </script>
</body>
</html>
)rawliteral";

// ======================================================================
//  SETUP / LOOP
// ======================================================================

void setup() {
	Serial.begin(115200);

	// Servos
	setupPWM();
	attachAllServos();
	Serial.println("Servos ready");

	// OLED
	Wire.begin(I2C_SDA, I2C_SCL);
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		Serial.println("OLED not found — check wiring");
	} else {
		display.clearDisplay();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(30, 28);
		display.println("ARRP-26 ready");
		display.display();
		Serial.println("OLED ready");
	}

	// AP
	WiFi.softAP(AP_SSID, AP_PASS);
	Serial.print("AP IP: ");
	Serial.println(WiFi.softAPIP());

	// Routes
	server.on("/", []() {
		server.send(200, "text/html", index_html);
	});

	server.on("/cmd", []() {
		String pose = server.arg("pose");
		String face = server.arg("face");

		if (pose != "") {
			if (pose == "stand")
				poseStand();
			else if (pose == "lay_down")
				poseLayDown();
			else if (pose == "wave")
				poseWave();
			else if (pose == "test")
				poseTest();
		}

		if (face != "") {
			Serial.println("Face: " + face);
			display.clearDisplay();
			if (face == "test") {
				// Draw the student's test bitmap
				display.drawBitmap(0, 0, face_test, 128, 64, WHITE);
			} else {
				// For built-in faces: print name as text until bitmaps are added
				display.setTextSize(2);
				display.setTextColor(WHITE);
				display.setCursor(20, 24);
				display.println(face);
			}
			display.display();
		}

		server.send(200, "text/plain", "ok");
	});

	server.begin();
	Serial.println("Server started — connect to " + String(AP_SSID));
}

void loop() {
	server.handleClient();
}
