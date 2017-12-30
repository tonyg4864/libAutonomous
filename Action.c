#include "Action.h"

int LEFT_SERVO_PIN = 3;
int RIGHT_SERVO_PIN = 4;
int HEAD_SERVO_PIN = 19;
int PINGER_PIN = 18;
int V_PANT_PIN = 14;
int H_PANT_PIN = 15;

//PWM Freq in KHz
int HB25_FREQ = 9200;

int HB25_FULL_FORWARD_MS = 2200;
int HB25_NEUTRAL_MS = 1500;
int HB25_FULL_REVERSE_MS = 1000;

void printPinInfo(int pin){
  /*The pin's state. If the pin is an output, 1 = 3.3 V
  and 0 = 0 V. If the pin is an input, 1 means V > 1.65 V, 0 means it's less.*/
  int pinState = get_state(pin);

  //I/O pin direction as seen by the cog that runs the function.
  int pinDirection = get_direction(pin);

  //In a register bit for I/O pin, either 1 or 0.
  int pinOutput = get_output(pin);

  print("pin %d state: %d\n", pin, pinState);
  print("pin %d direction: %d\n", pin, pinDirection);
  print("pin %d output: %d\n", pin, pinOutput);

}

void sendLowSignal(int pin){
   set_direction(pin, 1);
  low(pin);
}

void hb25Init(int pin){
  print("hb-25 init started on pin: %d\n", pin);
  sendLowSignal(pin);

  pause(5000);
  print("getting input from mc\n");
  set_direction(pin, 0);
  
  while( get_state(pin) == 0){
    //print("Wating for hb-25 to start...\n");
  } 

  sendLowSignal(pin);

  printPinInfo(pin);
  pause(20);
  printPinInfo(pin);
  
}

void hb25InitAll(){
  pwm_start(HB25_FREQ);
  hb25Init(LEFT_SERVO_PIN);
  hb25Init(RIGHT_SERVO_PIN);
}

void playSound(const char soundFileName[]){
  //const char techloop[] = {"techloop.wav"};   // Set up levels string
  wav_play(soundFileName);                         // Pass to wav player
  wav_volume(10);                              // Adjust volume
  pause(165900);                               
  //pause(1500000);
}

void leftWheelsForward(){
  pwm_set(LEFT_SERVO_PIN,0,HB25_FULL_FORWARD_MS);
  pause(20);

}

void stopLeftWheels(){
  pwm_set(LEFT_SERVO_PIN,0,HB25_NEUTRAL_MS);
  pause(20);
}

void leftWheelsReverse(){

  pwm_set(LEFT_SERVO_PIN,0,HB25_FULL_REVERSE_MS);
  pause(20);
}

void rightWheelsForward(){
   pwm_set(RIGHT_SERVO_PIN,1,HB25_FULL_FORWARD_MS);
   pause(20);
}

void rightWheelsReverse(){
  pwm_set(RIGHT_SERVO_PIN,1,HB25_FULL_REVERSE_MS);
  pause(20);
}

void stopRightWheels(){
   pwm_set(RIGHT_SERVO_PIN,1,HB25_NEUTRAL_MS);
   pause(20);
}

void driveForward(){
  print("driving forward\n");
  leftWheelsForward();
  rightWheelsForward();
  pause(20);
}

void driveReverse(){

  print("driving reverse\n");
  leftWheelsReverse();
  rightWheelsReverse();
  pause(20);
}

void stop(){
  print("stopping...\n");
  stopLeftWheels();
  stopRightWheels();
}
void rampUp(){
  //pwm_set(RIGHT_SERVO_PIN,0,HB25_FULL_REVERSE_MS);
  
  print("ramping up...");  
  for(int i = HB25_NEUTRAL_MS; i <= HB25_FULL_FORWARD_MS; i++){
    pwm_set(RIGHT_SERVO_PIN, 0, i);
    pwm_set(LEFT_SERVO_PIN, 0, i);
    pause(150);
    print("%d\n", i);
  }
}

void rampUpReverse(){
  print("ramping up reverse...");
  
  for(int i = 1070; i >= HB25_FULL_REVERSE_MS; i--){
    pwm_set(RIGHT_SERVO_PIN, 0, i);
    pause(150);
      print("%d\n", i);
  }
}

void rampDown(){
  print("ramping down...");
  
  for(int i = HB25_FULL_FORWARD_MS; i >= HB25_NEUTRAL_MS; i--){
    pwm_set(RIGHT_SERVO_PIN, 0, i);
    pwm_set(LEFT_SERVO_PIN, 0, i);
    pause(150);
    print("%d\n", i);
  }

  stop();
}

void spinRight(){
  rightWheelsForward();
  leftWheelsReverse();
}
void helloworld(void)                            // awesome function
{
  print("helloworld!\n");
}
