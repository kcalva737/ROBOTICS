/*This program has been written with the purpose to implement Serial.read and Xbee.read.
 * 
 * This code will be used by low level language and has the extent to be used with higher level languages such as python. The serial communicatoin renders the Arduino to be a slave.
 * The Arduino will be able to execute any code given to it through serial communication.
 * 
 * 
 */
#include "arduino.h"
#include "arduinoPin.h"
#include "stepper.h"
#include "servo.h"

char channel = 'B';

myServo myservo;
SerialString myString;
Stepp myStepper(0,52,50,23,25,27,29,31,35);

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  xbee.begin(9600);
  myStepper.step_start();
  //myString.intro();
}
void loop() {
  myStepper.step_loop();
  myStepper.step_move();
  //myStepper.step_print();
  
  if(myString.input_string() || myString.input_xbee() ){
    //Serial.print("main input_string()");
      if(myString.pin_assign() ){
        myString.print_input();
        
        switch(myString.command() ){ //swtich statetment

        case 'w':      // If received 'w'
        case 'W':      // or 'W'
          writeAPin(myString.pin(),myString.val() ); // Write analog pin
          break;
        case 'd':      // If received 'd'
        case 'D':      // or 'D'
          writeDPin(myString.pin(),myString.val() ); // Write digital pin
          break;
        case 'r':      // If received 'r'
        case 'R':      // or 'R'
          readDPin(myString.pin() );  // Read digital pin
          break;
        case 'a':      // If received 'a'
        case 'A':      // or 'A'
          readAPin(myString.pin() );  // Read analog pin
          break;
        case 'S':
        case 's':
          myservo.servoMove(myString.pin(), myString.val() );
          break;
        case 'T':
          for(int i=0;i<myString.val();i++){
            myStepper.controlStepper(700,0,1);
          }
          break;
        case 't':
          for(int i=0;i<myString.val();i++){
            myStepper.controlStepper(700,1,0);
          }
          break;
        }
      }
  }
  
}
