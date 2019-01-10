/*This program has been written with the purpose to implement Serial.read and Xbee.read.
 * 
 * This code will be used by low level language and has the extent to be used with higher level languages such as python. The serial communicatoin renders the Arduino to be a slave.
 * The Arduino will be able to execute any code given to it through serial communication.
 * 
 * 
 */
#include "arduino.h"
#include "arduinoPin.h"
#include "servo.h"

char channel = 'B';

myServo myServo;
SerialString myString;

void setup(){
  Serial.begin(9600);
  xbee.begin(9600);
  //myString.intro();
}
void loop() {
  if(myString.input_string() ){
    //Serial.print("main input_string()");
      if(myString.pin_assign() ){
        myString.print_input();
        
        switch(myString.command() ){ //swtich statetment

        case 'w':      // If received 'w'
          writeAPin(myString.pin(),myString.val() ); // Write analog pin
          break;
        case 'd':      // If received 'd'
          writeDPin(myString.pin(),myString.val() ); // Write digital pin
          break;
        case 'r':      // If received 'r'
          readDPin(myString.pin() );  // Read digital pin
          break;
        case 'a':      // If received 'a'
          readAPin(/*myString.channel(),*/myString.pin() );  // Read analog pin
          break;
        case 'm':
          myServo.servoMove(myString.pin(),myString.val() );
          break;
        }
      }
  }
  
}
