#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include "ap-portal-frontend.h"
#include "face-bitmaps.h"
#include "servo-sequences.h"

// ----------------------------------------------------------------------
//  AP CREDENTIALS
// ----------------------------------------------------------------------
const char *ap_ssid = "ARRP-26";
const char *ap_pass = "arrp2026";

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
// ----------------------------------------------------------------------
const int SERVO_FREQ_HZ = 50;
const int MIN_PULSE_US  = 732;
const int MAX_PULSE_US  = 2929;

// ----------------------------------------------------------------------
//  CALIBRATION
// ----------------------------------------------------------------------
int8_t servoSubtrim[NUM_SERVOS] = {0, 0, 0, 0, 0, 0, 0, 0};
int motorCurrentDelay = 20; // ms between servo commands

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
	if (channel >= NUM_SERVOS) return;
	int adjusted = constrain(angle + servoSubtrim[channel], 0, 180);
	servos[channel].write(adjusted);
	delay(motorCurrentDelay);
}

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
		display.display();
		Serial.println("OLED ready");
	}

	// AP
	WiFi.softAP(ap_ssid, ap_pass);
	Serial.print("AP IP: ");
	Serial.println(WiFi.softAPIP()); // 192.168.4.1

	// Routes
	server.on("/", []() {
		server.send(200, "text/html", index_html);
	});

	server.on("/cmd", []() {
		String pose    = server.arg("pose");
		String face    = server.arg("face");
		String student = server.arg("student");

		// --- Pose ---
		if (pose != "") {
			if      (pose == "stand")    poseStand();
			else if (pose == "lay_down") poseLayDown();
			else if (pose == "wave")     poseWave();
		}

		// --- Face ---
		if (face != "") {
			Serial.println("Face: " + face);
			display.clearDisplay();
			if      (face == "happy")  display.drawBitmap(0, 0, face_happy,  128, 64, WHITE);
			else if (face == "sad")    display.drawBitmap(0, 0, face_sad,    128, 64, WHITE);
			else if (face == "sleepy") display.drawBitmap(0, 0, face_sleepy, 128, 64, WHITE);
			else if (face == "cute")   display.drawBitmap(0, 0, face_cute,   128, 64, WHITE);
			display.display();
		}

		// --- Student demos ---
		if (student != "") {
			Serial.println("Student: " + student);
			display.clearDisplay();

			if (student == "brielle") {
				poseBrielle();
				display.drawBitmap(0, 0, face_brielle, 128, 64, WHITE);
			} else if (student == "kosta") {
				poseKosta();
				display.drawBitmap(0, 0, face_happy, 128, 64, WHITE);
			} else if (student == "stephan") {
				poseStephan();
				display.drawBitmap(0, 0, face_cute, 128, 64, WHITE);
			} else if (student == "tanish") {
				poseTanish();
				display.drawBitmap(0, 0, face_tanish, 128, 64, WHITE);
			}

			display.display();
		}

		server.send(200, "text/plain", "ok");
	});

	server.begin();
	Serial.println("Server started — connect to " + String(ap_ssid));
}

void loop() {
	server.handleClient();
}
