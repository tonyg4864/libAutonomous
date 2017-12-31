#include "simpletools.h"
#include "wavplayer.h"
#include "servo.h" 
#include "ping.h" 

extern int LEFT_SERVO_PIN;
extern int RIGHT_SERVO_PIN;
extern int HEAD_SERVO_PIN;
extern int PINGER_PIN;
extern int V_PANT_PIN;
extern int H_PANT_PIN;

//PWM Freq in KHz
extern int HB25_FREQ;

extern int HB25_FULL_FORWARD_MS;
extern int HB25_NEUTRAL_MS;
extern int HB25_FULL_REVERSE_MS;

void printPinInfo();
void hb25Init(int pin);
void hb25InitAll();
void playSound(const char soundFileName[]);
void leftWheelsForward();
void stopLeftWheels();
void leftWheelsReverse();
void rightWheelsForward();
void rightWheelsReverse();
void stopRightWheels();
void driveForward();
void driveReverse();
void stop();
void rampUp();
void rampUpReverse();
void rampDown();
void spinRight();