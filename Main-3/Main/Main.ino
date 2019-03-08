//ROBOT
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
relayControl Arm0(13,12); //initialize relayControl with input pins for relays
relayControl Arm1(11,10); //initialize relayControl with input pins for relays
relayControl Arm2(9,8); //initialize relayControl with input pins for relays

Servo myServo9;
Servo myServo6;
Servo myServo5;
Servo myServo3;
int myNumber[10] = {0,0,0,0,0,0,0,0,0};

void setup(){
  Serial.begin(9600);
  xbee.begin(9600);

  myServo9.attach(9);
  myServo6.attach(6);
  myServo5.attach(5);
  myServo3.attach(3);
}
void loop() {
  //  for(unsigned int i=0;i<10;i++){
  //    myNumber[i] = constrain(myNumber[i],1,224);
  //  }
  
  if(myString.input_xbee() ){//alternate between input.string() and input_xbee() 
    
      myString.print_input();
      switch(myString.pin()){
        case 13: //linear actuator
          ballLoad.relay_button(myString.val() ,0);
          break;
        case 12:
          ballLoad.relay_button(0,myString.val());
          break;
          
        case 8: //linear actuator
          Arm.relay_button(myString.val() ,0);
          break;
        case 7:
          Arm.relay_button(0,myString.val());
          break;

        case 4: //linear actuator
          Arm2.relay_button(myString.val() ,0);
          break;
        case 2:
          Arm2.relay_button(0,myString.val());
          break;


        case 11://X axis
          writeAPin(myString.pin(),myString.val() );
          break;
        case 10://y axis
          writeAPin(myString.pin(),myString.val() );
          break;


        case 9:
          myServo9.write(myString.val() );
          break;
        case 6:
          myServo6.write(myString.val() );
          break;
        case 5:
          myServo5.write(myString.val() );
          break;
        case 3:
          myServo3.write(myString.val() );
          break; 
          //writeAPin(myString.pin(),myString.val() );
          //myServo.servoMove(myString.pin(),myString.val());//use the original code, a bit glitchy

        /*
        case 11:
          analogWrite(myString.pin(), myString.val() ); 
        case 9:
          writeAPin(myString.pin(),myString.val() );
        */
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
