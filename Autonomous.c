#include "autonomous.h"

void awesome(void)                            // awesome function
{
  print(" is awesome!\n");
}

void epic(void)                               // epic function
{
  print(" is epic!\n");
}

char leftOrRight(int leftD, int rightD){
  if(leftD > rightD){
    return 'l';
  }else{
    return 'r';
  }
}