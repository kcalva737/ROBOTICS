#ifndef _RELAY_CONTROL_
#define _RELAY_CONTROL_

/*
Code has been tested on March 2-2019
 -bugs to fix:
  when switch is activated, it gets interupted by the pressing of the other button
 
 -pros:
  It does not work when both switches are active, counter-mesure of it destorying it self
  
*/
//Code written by Jonny(IEEE member 2019):
//Code revised by Charly(SHPE RED member 2019):

//follow the connection of the schematic drawing of Actuator relay control system
// When relay1 is LOW and relay2 is LOW, then it will be stable
// When relay1 is LOW and relay2 is HIGH, then it will forward
// When relay1 is HIGH and relay2 is LOW, then it will backward
// DON'T SET (relay1 is HIGH and Realy2 is HIGH)

class relayControl{
  private:
  int relay1;// =  8; // output pin for relay1 
  int relay2;// = 9; // output pin for relay2

  public:
  //to implement this class, we need to input which pins the relays are connected to
  //re1 will send 5V to the coil of relay 1
  //re2 will send 5v to the coil of relay2
  //relayControl(pin# of relay1, pin# of relay2)
  relayControl(int re1,int re2){
    relay1 = re1;
    relay2 = re2;
    //button_up = butt1;
    //button_down = butt2;  

    pinMode(relay1, OUTPUT);  
    pinMode(relay2, OUTPUT); 
  }
  //implementation: given a value of 
  //relay_button(value-of-buttonOne,value-of-butonTwo);
  void relay_button(int buttonUP, int buttonDN){
    if((buttonUP == 1) && (buttonDN == 1)){ //both buttons are being pressed, ignore
      //return;
    }
    else if(buttonUP == 1){
      //button_up = buttonUP;//save values, or call function to make changes?
      digitalWrite(relay1, LOW); 
      digitalWrite(relay2, HIGH);
      
    }
    else if(buttonDN == 1){
      //buttonDN ==
      digitalWrite(relay1, HIGH); 
      digitalWrite(relay2, LOW);
      
    }
    else{ //both buttons are off, turn off relays
      digitalWrite(relay1, LOW);  //relay1 and relay2 set to LOW
      digitalWrite(relay2, LOW);
      
    }

    //delay(200);
    return;
  }
};
#endif
