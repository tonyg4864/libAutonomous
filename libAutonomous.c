/*
  Awesome Messages.c
*/                    // Include simple tools
//#include "Autonomous.h"
#include "Action.h"
#include "fdserial.h"
#include "PingerController.h"
#include "ServoController.h"
#include <stdbool.h>

fdserial *xbee;
int FORWARD_DISTANCE_THRESHOLD = 100;
int DIRECTION_CHANGE_DURATION_MS = 1000;
//8.28 volts draw
//.11 amps at idle draw and 5.79 amps with all 6 wheels running and 1.54 one side running .74 volts on the signal cable

//Find the new direction to move to
//return l for left r for right b for reverse
char findNewDirection(){
  rotateCenter(HEAD_SERVO_PIN);
  int centerDistance = getPingCMDistance(PINGER_PIN);
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
  
void driveAutonomously(){
    //reset
    stop();
    rotateCenter(HEAD_SERVO_PIN);
    while(1){
        int forwardDistance = getPingCMDistance(PINGER_PIN);
        while(forwardDistance < FORWARD_DISTANCE_THRESHOLD){
            stop();
            driveReverse();
            pause(DIRECTION_CHANGE_DURATION_MS);
            stop();
            char newDirection = findNewDirection();
            if(newDirection == 'l'){
                spinLeft();
                pause(DIRECTION_CHANGE_DURATION_MS);
                stop();
            }else if(newDirection == 'r'){
                spinRight();
                pause(DIRECTION_CHANGE_DURATION_MS);
                stop();
            }
            forwardDistance = getPingCMDistance(PINGER_PIN);
        }
        driveForward();
    }
}

char* getCmdPromptMsg(){
  return "Enter command to run:";
}  

int main(){
  //Setup fdserial
  hb25InitAll();
  //xbee = fdserial_open(9, 8, 0, 9600);
  //writeChar(xbee, CLS);
  //dprint(xbee, "Click this terminal, \n");
  //dprint(xbee, "and type on keybaord...\n\n");

  int frontDistance = 0;
  int userInput;

  while(1){
    userInput = -1;
    //userInput = fdserial_rxChar(xbee);
    print(getCmdPromptMsg());
    scan("%d\n", &userInput); // Get input from terminal
    if(userInput != -1){
        //dprint(xbee, "You typed: %c\n", userInput);
        if(userInput == 1){
          print('Driving forward');
          driveForward();
        }else if(userInput == '2'){
          testServo(17);
        }else if(userInput == '3'){
          testPing(12);
        }else if(userInput == 4){
          driveAutonomously();
        }else if(userInput == 9){
          //Stop Driving
          stop();
        }          
     }
  }
}  