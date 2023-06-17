#include "QMC5883.h"
#include "Ultrasonic.h"

// DFRobot_QMC5883 compass;
Ultrasonic Sonic(28, 29);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // compass.Setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("now distance: ");
  Serial.println(Sonic.getdist());
  delay(500);
}
