#pragma once

// ======================================================================
//  BUILT-IN POSES
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
	Serial.println("Pose: lay_down");
	// TODO: tune these angles once robot is assembled
	for (int i = 0; i < NUM_SERVOS; i++)
		setServoAngle(i, 90);
}

void poseWave() {
	Serial.println("Pose: wave");
	poseStand();
	setServoAngle(R1, 90);
	delay(500);
	setServoAngle(R1, 135);
}

// ======================================================================
//  STUDENT POSES
// ======================================================================

void poseBrielle() {
	Serial.println("Pose: Brielle");
	int time = 100;
	poseStand();
	for (int i = 0; i < 4; i++) {
		setServoAngle(L3, 135);
		setServoAngle(R4, 135);
		delay(time);
		setServoAngle(L1, 20);
		setServoAngle(R2, 20);
		delay(time);
		setServoAngle(L3, 0);
		setServoAngle(R4, 0);
		delay(time);
		setServoAngle(R3, 45);
		setServoAngle(L4, 45);
		delay(time);
		setServoAngle(L2, 160);
		setServoAngle(R1, 160);
		setServoAngle(L1, 45);
		setServoAngle(R2, 45);
		delay(time);
		setServoAngle(R3, 180);
		setServoAngle(L4, 180);
		delay(time);
	}
}

void poseKosta() {
	Serial.println("Pose: Kosta");
	for (int j = 0; j < 10; j++) { // fixed: was int j (uninitialised)
		setServoAngle(R1, 135);
		for (int i = 1; i < 3; i++) {
			setServoAngle(R3, 160);
			delay(1000 * i);
			setServoAngle(R3, 60);
			delay(1000 * i);
		}
		setServoAngle(R3, 0);
		delay(1000);
		setServoAngle(L2, 135);
		for (int i = 1; i < 3; i++) {
			setServoAngle(L4, 160);
			delay(1000 * i);
			setServoAngle(L4, 60);
			delay(1000 * i);
		}
		setServoAngle(L4, 0);
		delay(1000);
		setServoAngle(L1, 135);
		for (int i = 1; i < 3; i++) {
			setServoAngle(L3, 160);
			delay(1000 * i);
			setServoAngle(L3, 60);
			delay(1000 * i);
		}
		setServoAngle(L3, 0);
		delay(1000);
		setServoAngle(R2, 135);
		for (int i = 1; i < 3; i++) {
			setServoAngle(R4, 160);
			delay(1000 * i);
			setServoAngle(R4, 60);
			delay(1000 * i);
		}
		setServoAngle(R4, 0);
	}
}

void poseStephan() {
	Serial.println("Pose: Stephan");
	setServoAngle(R1, 135);
	delay(500);
	setServoAngle(R1, 135);
}

void poseTanish() {
	Serial.println("Pose: Tanish");
	int a = 180;
	int b = 0;
	for (int i = 0; i < 135; i++) {
		setServoAngle(R1, 180);
		setServoAngle(R2, 0);
		setServoAngle(L1, 0);
		setServoAngle(L2, 180);
		setServoAngle(R4, 0);
		setServoAngle(R3, a);
		setServoAngle(L3, b);
		setServoAngle(L4, 180);
		delay(10);
		a--;
		b++;
	}
}
