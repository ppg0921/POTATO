/*-------------------------Malissa-------------------------*/
// start at 2023-05-15
// 
// 
/*--------------------End of imformation--------------------*/

#include "bluetooth.h"
#include "Motor.h"
#include "RFID.h"
#include "Ultrasonic.h"


//Wiring

// BlueTooth
// BT connect to Serial1 (Hardware Serial)
// Mega               HC05
// Pin  (Function)    Pin
// 18    TX       ->  RX
// 19    RX       <-  TX

#define PIN_motor_l 9
#define PIN_motor_r 10
const int PIN_ulso_trig[4] = {22, 24, 26, 28};
const int PIN_ulso_echo[4] = {23, 25, 27, 29};

Ultrasonic ulso[4]={Ultrasonic(22, 23), Ultrasonic(24, 25), Ultrasonic(26, 27), Ultrasonic(28, 29)};
char cmdline[1000];

ulso[2].getdist

enum State{
  STATE_READMAP, STATE_LOCATE, STATE_GO, STATE_TEST
};

State state = STATE_TEST;
void state_test();

void setup() {
  Motor_setup(PIN_motor_l, PIN_motor_r);
  Serial1.begin(9600);
  Serial.begin(9600);

}



void loop() {
  switch (state){
  case STATE_READMAP:
    if(BT_receive(cmdline))state = STATE_LOCATE;
    break;

    case STATE_LOCATE:
    case STATE_TEST: state_test(); break;
  }


}

void state_test(){
  Motor_f(); delay(5000);
  Motor_h(); delay(5000);
}

int conv_x 


