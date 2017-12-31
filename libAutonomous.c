/*
  Awesome Messages.c
*/

#include "simpletools.h"                      // Include simple tools
#include "autonomous.h"
#include "Action.h"

void testServo(int pin){

   //print("testing servo on pin %d\n", pin);
  servo_angle(pin, 400);                         // P16 servo to 0 degrees
  pause(1000);                                // ...for 3 seconds
//  servo_angle(pin, 900);
  servo_angle(pin, 1800);                       // P16 servo to 90 degrees
  pause(1000);                                // ...for 3 seconds
  //servo_angle(pin, 400);                      // P16 servo to 180 degrees
  //pause(1000);                                // ...for 3 seconds
  servo_stop();

}

void testDrive(){
  hb25InitAll();
    driveForward();    
    pause(500);
    stop();
    pause(500);
    driveReverse();
    pause(500);
    stop();
}

void testPinger(int pin){
  int cmDist = ping_cm(pin);                 // Get cm distance from Ping)))
    print("cmDist = %d\n", cmDist);           // Display distance
    pause(200);      
}

void testVPant(){
   for(int i = 0; i < 4; i++){
  testServo(V_PANT_PIN);
  }      
}

void testHPant(){ 
  for(int i = 0; i < 4; i++){
  testServo(H_PANT_PIN);
  }
}

setupSDCard(){
  int DO = 22, CLK = 23, DI = 24, CS = 25;    // SD I/O pins
  sd_mount(DO, CLK, DI, CS);                  // Mount SD card
}

int main()                                    // main function
{
  int userInput;
  setupSDCard();

  while(1){
    print("What would you like to do?");
    scan("%d/n", &userInput);
    
    if(userInput == 1){
      leftWheelsForward();
      //rightWheelsForward();
    }else if(userInput == 2){
      stop();
    }else if (userInput == 3){
      print("Playing sound\n");
     playSound("techloop.wav");
    }else if (userInput == 4){
      wav_stop();
    }else if (userInput == 5){
      //hb25Init(RIGHT_SERVO_PIN);
      hb25InitAll();
    }else if (userInput ==6){
      leftWheelsReverse();
      //rightWheelsReverse();
    }else if (userInput == 7){
      pwm_stop();
      return 0;
    }else if (userInput == 8){
      playSound("regper.wav");
    }else if (userInput == 9){
      rampUp();
      rampDown();
    }else if (userInput == 10){
      rightWheelsForward();
    }else if (userInput == 11){
      rightWheelsReverse();
    }else if (userInput == 12){
      driveForward();
    }else if (userInput == 13){
      driveReverse();
    }else if (userInput == 14){
      spinRight();
    }else if (userInput == 15){
      testServo(HEAD_SERVO_PIN);
    }else if(userInput == 16){
      testPinger(PINGER_PIN);
    }else if(userInput == 17){
        cog_run(testVPant, 128);
        cog_run(testHPant, 128);
    }
      //print("Playing sound\n");
      //playSound("techloop.wav");
      //playSound("regper.wav");
  }
}