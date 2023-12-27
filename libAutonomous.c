/*
  Awesome Messages.c
  WX ModuleIP Address in AP+STA mode:
  - http://192.168.4.1/index.html
  - http://esp8266.nonet/wifi/wifi.html
    IP with Joined Network:
     - 192.168.4.163
*/                    
// Include simple tools
//#include "Autonomous.h"
#include "Action.h"
#include "fdserial.h"
#include "PingerController.h"
#include "ServoController.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 6

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


//Hashmap TODO: factor out
struct node {
    int key;
    char* value;
    struct node* next;
};

struct node* hash_table[TABLE_SIZE];

int hash_function(int key) {
    return key % TABLE_SIZE;
}

void insert(int key, char* value) {
    int index = hash_function(key);
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->key = key;
    new_node->value = (char*) malloc(strlen(value) + 1);
    strcpy(new_node->value, value);
    new_node->next = NULL;

    if (hash_table[index] == NULL) {
        hash_table[index] = new_node;
    } else {
        struct node* current_node = hash_table[index];
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }
}

char* search(int key) {
    int index = hash_function(key);
    struct node* current_node = hash_table[index];
    while (current_node != NULL) {
        if (current_node->key == key) {
            return current_node->value;
        }
        current_node = current_node->next;
    }
    return NULL; // Key not found
} 
/////////////////////////////

char* getCmdPromptMsg(){
  insert(0, "Stop Driving.");
  insert(1, "Drive forward.");
  insert(2, "Test Servo");
  insert(3, "Test Pinger");
  insert(4, "Drive Autonomously");
  insert(5, "Initialize");
  insert(6, "Exit");
  
  char *intro = "Type a command from one of the following options:\n";
  char fullMsg[500] = "";
  strcat(fullMsg, intro);

  for(int i = 0; i <= TABLE_SIZE; i++){
    char str[100];
    sprintf(str, "%d: %s\n", i, search(i));
    strcat(fullMsg, str);
  }
  return fullMsg;
}  

bool initialize(){
    //Setup fdserial
  print("hb-25 initialization starting...\n");
  hb25InitAll();
  print("hb-25 initialization completed.\n");
  return true;
}
  
int main(){
  bool initialized = false;

  int frontDistance = 0;
  int userInput;

  while(1){
    userInput = -1;
    print(getCmdPromptMsg());
    scan("%d\n", &userInput); // Get input from terminal
    if(userInput == 6){
      print("Exiting program!\n");
      break;   
    }else{
      
        if(userInput == 0){
          print("You entered: 0: Stop Driving...\n");
          stop();
        }else if(userInput == 1){
          print("You entered: 1: Driving forward...\n");
          driveForward();
        }else if(userInput == 2){
          print("You entered: 2: Testing servo...\n");
          testServo(17);
        }else if(userInput == 3){
          print("You entered: 3: Testing Ping...\n");
          testPing(12);
        }else if(userInput == 4){
          print("You entered: 4: Driving Autonomously...\n");
          driveAutonomously();
        }else if(userInput == 5){         
          print("You entered: 5: Initialize...\n");
          initialized = initialize();
        }          
    }      
  }
}  