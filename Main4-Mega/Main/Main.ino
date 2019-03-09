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
#include "relayControl.h"
char channel = 'B';

myServo myServo;
SerialString myString;
relayControl Arm0(22,23);
relayControl Arm1(24,25);
relayControl Arm2(26,27);

Servo axis1;
Servo axis2;

Servo myServo0;
Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  //xbee.begin(9600);
  //myString.intro();
  axis1.attach(12);
  axis2.attach(11);
  
  myServo0.attach(9);
  myServo1.attach(8);
  myServo2.attach(7);
  myServo3.attach(6);
  myServo4.attach(5);
}
void loop() {
  if(myString.input_string() ){//alternate between input.string() and input_xbee() 
      //myString.print_input();
      switch(myString.pin()){
        //X-Yaxis
        case 12:
          //writeAPin(myString.pin(),myString.val() );
          axis1.write(myString.val() );
          break;
        case 11:
          //writeAPin(myString.pin(),myString.val() );
          axis2.write(myString.val() );
          break;
          
        //ServoArm
        case 9:
          myServo0.write(myString.val());
          myServo1.write(180 - myString.val());
          break;
        case 8:
          myServo2.write(myString.val());
          break;
        case 7:
          myServo3.write(myString.val());
          break;
        case 6:
          myServo4.write(myString.val());
          break;
        case 5:
          myServo4.write(myString.val());
          break;

        //Relay Arm
        case 22:
          //writeDPin(myString.pin(),myString.val() );
          Arm0.relay_button(myString.val() ,0);
          break;
        case 23:
          Arm0.relay_button(0,myString.val());
          break;

        case 24:
          //writeDPin(myString.pin(),myString.val() );
          Arm1.relay_button(myString.val() ,0);
          break;
        case 25:
          Arm1.relay_button(0,myString.val());
          break;

        case 26:
          writeDPin(myString.pin(),myString.val() );
          //Arm2.relay_button(myString.val() ,0);
          break;
        case 27:
          Arm2.relay_button(0,myString.val());
          break;
        
      }
  }
  
}
