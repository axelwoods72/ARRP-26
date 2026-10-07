#include <WiFi.h>
#include <WebServer.h>
#include "ap-portal-frontend.h"
#include "face-bitmaps.h"

const char *ap_ssid = "ARRP-26";
const char *ap_pass = "arrp2026";

WebServer server(80);

void setup() {
	Serial.begin(115200);

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
		Serial.println("Command: " + pose);

		if (pose == "lay_down") {
			// TODO: lay down servo sequence
		} else if (pose == "stand_up") {
			// TODO: stand up servo sequence
		} else if (pose == "wave") {
			// TODO: wave servo sequence
		}

		server.send(200, "text/plain", "ok");
	});

	server.begin();
	Serial.println("Server started");
}

void loop() {
	server.handleClient();
}
