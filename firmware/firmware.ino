#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ap-portal-frontend.h"
#include "face-bitmaps.h"

const char *ap_ssid = "ARRP-26";
const char *ap_pass = "arrp2026";

#define I2C_SDA 33
#define I2C_SCL 35

WebServer server(80);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
	Serial.begin(115200);

	/* OLED init */
	Wire.begin(I2C_SDA, I2C_SCL);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
	display.display();

	WiFi.softAP(ap_ssid, ap_pass);
	Serial.print("AP IP: ");
	Serial.println(WiFi.softAPIP()); // 192.168.4.1

	/* serve html */
	server.on("/", []() {
		server.send(200, "text/html", index_html);
	});

	/* handle commands from web server */
	server.on("/cmd", []() {
		String pose = server.arg("pose");
		String face = server.arg("face");

		if (pose != "") {
			Serial.println("Pose: " + pose);
			if (pose == "lay_down") {
				// TODO: lay down servo sequence
			} else if (pose == "stand_up") {
				// TODO: stand up servo sequence
			} else if (pose == "wave") {
				// TODO: wave servo sequence
			}
		}

		if (face != "") {
			Serial.println("Face: " + face);
			display.clearDisplay();
			if (face == "happy") {
				display.drawBitmap(0, 0, face_happy, 128, 64, WHITE);
			} else if (face == "sad") {
				display.drawBitmap(0, 0, face_sad, 128, 64, WHITE);
			} else if (face == "sleepy") {
				display.drawBitmap(0, 0, face_sleepy, 128, 64, WHITE);
			} else if (face == "cute") {
				display.drawBitmap(0, 0, face_cute, 128, 64, WHITE);
			}
			display.display();
		}

		server.send(200, "text/plain", "ok");
	});

	server.begin();
	Serial.println("Server started");
}

void loop() {
	server.handleClient();
}
