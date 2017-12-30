/*
  Awesome Messages.c
*/

#include "simpletools.h"                      // Include simple tools
#include "autonomous.h"
#include "Action.h"

int main()                                    // main function
{
  print("Nick");                              // Print a name
  awesome();                                  // Append with "is awesome!\n"

  print("Jessica");                           // Print another name
  epic();                                     // Append with "is epic!\n"
  helloworld();
  
  printPinInfo();
  hb25InitAll();
  
  rampUp();
  rampDown();
}