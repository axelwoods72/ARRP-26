#include <WiFi.h>
#include <WebServer.h>
#include "ap-portal-frontend.h"

const char *ap_ssid = "ARRP-26";
const char *ap_pass = "arrp2026";

WebServer server(80);

void setup() {
	Serial.begin(115200);

	WiFi.softAP(ap_ssid, ap_pass);
	Serial.print("AP IP: ");
	Serial.println(WiFi.softAPIP()); // 192.168.4.1

	server.on("/", []() {
		server.send(200, "text/html", index_html);
	});

	server.on("/cmd", []() {
		String pose = server.arg("pose");
		Serial.println("Command: " + pose);
		// TODO: handle pose commands here
		server.send(200, "text/plain", "ok");
	});

	server.begin();
	Serial.println("Server started");
}

void loop() {
	server.handleClient();
}
