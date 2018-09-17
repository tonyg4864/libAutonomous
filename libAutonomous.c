/*
  Awesome Messages.c
*/

#include "simpletools.h"                      // Include simple tools
#include "autonomous.h"
#include "Action.h"
#include "fdserial.h"

fdserial *xbee;
//8.28 volts draw
//.11 amps at idle draw and 5.79 amps with all 6 wheels running and 1.54 one side running .74 volts on the signal cable
void testServo(int pin){

  print("testing servo on pin %d\n", pin);
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
  //My setup
  //int userInput;
  setupSDCard();
  
  //Setup fdserial
  hb25InitAll();
  xbee = fdserial_open(9, 8, 0, 9600);
  writeChar(xbee, CLS);
  dprint(xbee, "Click this terminal, \n");
  dprint(xbee, "and type on keybaord...\n\n");

  char userInput;
  while(1){
    userInput = fdserial_rxChar(xbee);
    if(userInput != -1)
    {
        dprint(xbee, "You typed: %c\n", userInput);
        if(userInput == '8'){
          leftWheelsForward();
          //rightWheelsForward();
        }else if(userInput == '2'){
          stop();
        }else if (userInput == '13'){
          print("Playing sound\n");
         playSound("techloop.wav");
        }else if (userInput == '14'){
          wav_stop();
        }else if (userInput == '5'){
          //hb25Init(RIGHT_SERVO_PIN);
          hb25InitAll();
        }else if (userInput == '16'){
          leftWheelsReverse();
          //rightWheelsReverse();
        }else if (userInput == '7'){
          pwm_stop();
          return 0;
        }else if (userInput == '11'){
          playSound("regper.wav");
        }else if (userInput == '9'){
          rampUp();
          rampDown();
        }else if (userInput == '10'){
          rightWheelsForward();
        }else if (userInput == '11'){
          rightWheelsReverse();
        }else if (userInput == '1'){
          driveForward();
        }else if (userInput == '3'){
          driveReverse();
        }else if (userInput == '4'){
          spinRight();
        }else if (userInput =='6'){
          spinLeft();
        }else if (userInput == '15'){
          testServo(HEAD_SERVO_PIN);
        }else if(userInput == '16'){
          testPinger(PINGER_PIN);
        }else if(userInput == '17'){
            cog_run(testVPant, 128);
            cog_run(testHPant, 128);
        }
    }
    //print("What would you like to do?");
    //scan("%d/n", &userInput);
    
    /*if(userInput == 1){
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
    }*/
      //print("Playing sound\n");
      //playSound("techloop.wav");
      //playSound("regper.wav");
  }
}