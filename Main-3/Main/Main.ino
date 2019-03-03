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
relayControl ballLoad(12,13);

void setup(){
  Serial.begin(9600);
  xbee.begin(9600);
  //myString.intro();
}
void loop() {
  if(myString.input_xbee() ){//alternate between input.string() and input_xbee() 
      myString.print_input();
      switch(myString.pin()){
        case 13:
          //writeDPin(myString.pin(),myString.val() );
          ballLoad.relay_button(myString.val() ,0);
          break;
        case 12:
          ballLoad.relay_button(0,myString.val());
          break;
        case 11:
          analogWrite(myString.pin(), myString.val() ); 
        case 9:
          writeAPin(myString.pin(),myString.val() );
        
        //idea code for driving robot
        /*case 64: //send xval code of 64- xvalue
         * int tempVal = input.value;
         * while(!input.Xbee){};
         * case 65: send yval code of 65 - yvalue
         * int tempval2 = input.value
         *  drive car(xvalue, y value);
         * default:
         *  break; faulty code
         *  
         * new ideal code:
         * case 64:
         *  tempVal = pinRead:
         * case 65:
         *  tempVal2 = pinRead
         *  move the robot(tempVal, tempVal2);
        */
        
      }
  }
  
}

/*
relayControl(int re1,int re2)//rel: pin of relay 1, re2:pin of relay 2
  void relay_button(int buttonUP, int buttonDN){
writeDPin(myString.pin(),myString.val() )

*/
