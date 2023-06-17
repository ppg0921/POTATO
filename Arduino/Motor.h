#include <Servo.h>
//using servo of 360 degrees

Servo servo_l;
Servo servo_r;
const int k = 180;

void Motor_setup(int pin_l, int pin_r){
  servo_l.attach(pin_l);
  servo_r.attach(pin_r);
}

void Motor_f(){
  servo_l.write(90-k);
  servo_r.write(90+k);
}

void Motor_b(){
  servo_l.write(90+k);
  servo_r.write(90-k);
}

void Motor_l(){
  servo_l.write(90+k);
  servo_r.write(90+k);
  delay(1000);
}
void Motor_r(){
  servo_l.write(90-k);
  servo_r.write(90-k);
  delay(1000);
}

void Motor_u(){
  servo_l.write(90+k);
  servo_r.write(90+k);
  delay(1000);
}

void Motor_h(){
  servo_l.write(90);
  servo_r.write(90);
}

