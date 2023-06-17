#include "QMC5883.h"

DFRobot_QMC5883 compass;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  compass.Setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("now relative degree: ");
  Serial.println(compass.getRelativeDegrees());
  delay(500);
}
