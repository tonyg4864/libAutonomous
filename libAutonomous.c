/*
  Awesome Messages.c
*/                    // Include simple tools
//#include "Autonomous.h"
#include "Action.h"
#include "fdserial.h"
#include "PingerController.h"
#include "ServoController.h"

fdserial *xbee;
//8.28 volts draw
//.11 amps at idle draw and 5.79 amps with all 6 wheels running and 1.54 one side running .74 volts on the signal cable

char findNewDirection(){
  rotateLeft(HEAD_SERVO_PIN);
  int leftDistance = getPingCMDistance(PINGER_PIN);
  rotateRight(HEAD_SERVO_PIN);
  int rightDistance = getPingCMDistance(PINGER_PIN);
  rotateCenter(HEAD_SERVO_PIN);
  if(leftDistance > rightDistance){
    return 'l';
  }else{
    return 'r';
  }    
}
  
int main(){
  //Setup fdserial
  hb25InitAll();
  xbee = fdserial_open(9, 8, 0, 9600);
  writeChar(xbee, CLS);
  dprint(xbee, "Click this terminal, \n");
  dprint(xbee, "and type on keybaord...\n\n");

  int frontDistance = 0;

  char userInput;
  while(1){
    userInput = -1;
    userInput = fdserial_rxChar(xbee);
    if(userInput != -1){
        dprint(xbee, "You typed: %c\n", userInput);
        if(userInput == '1'){
          driveForward();
        }else if(userInput == '2'){
          testServo(17);
        }else if(userInput == '3'){
          testPing(12);
        }
     }
     int forwardDistance = getPingCMDistance(PINGER_PIN);
     while(forwardDistance < 50){
        stop();
        char newDirection = findNewDirection();
        if(newDirection == 'l'){
            spinLeft();
            pause(3000);
            stop();
        }else{
            spinRight();
            pause(3000);
            stop();
        }
        forwardDistance = getPingCMDistance(PINGER_PIN);
     }
     driveForward();
  }
}  