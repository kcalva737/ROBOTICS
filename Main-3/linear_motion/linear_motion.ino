
//follow the connection of the schematic drawing of Actuator relay control system
// When relay1 is LOW and relay2 is LOW, then it will be stable
// When relay1 is LOW and relay2 is HIGH, then it will forward
// When relay1 is HIGH and relay2 is LOW, then it will backward
// DON'T SET (relay1 is HIGH and Realy2 is HIGH)

class relayControl{
  private:
  int relay1;// =  8; // output pin for relay1 
  int relay2;// = 9; // output pin for relay2
  int button_up;// = A0; // analog input pin for button control forward/upward
  int button_down;// = A1;// analog input pin for button control backward/downward

  public:
  relayControl(int re1,int re2,int butt1,int butt2){
    relay1 = re1;
    relay2 = re2;
    button_up = butt1;
    button_down = butt2;  

    pinMode(relay1, OUTPUT);  
    pinMode(relay2, OUTPUT); 
    pinMode(button_up, INPUT);
    pinMode(button_down, INPUT);
  }

 void button_up(int value){
  }
  void loop()
  {
    
    
    int button_up_val = 0;
    int button_down_val = 0;
    button_up_val = digitalRead(button_up);
    button_down_val = digitalRead(button_down);
  
  //when button_down and button_up aren't pressed, then the actuator will be natural/stable/no moving
  if (button_down_val == 0 && button_up_val == 0){
    digitalWrite(relay1, LOW);  //relay1 and relay2 set to LOW
    digitalWrite(relay2, LOW);
    }
    
  //when button_down pressed, then the actuator will be backward/downward
   if (button_down_val == 1){
    digitalWrite(relay1, HIGH); 
    digitalWrite(relay2, LOW);
      delay(200);
   } 
   delay(100);
  
  //when button_up pressed, then the actuator will be upward/forward
  
   if(button_up_val == 1){
       digitalWrite(relay1, LOW); 
      digitalWrite(relay2, HIGH);
       delay(200);
   }
  
   delay(100);
   
  //Serial.println ("button up ");
  //Serial.println (button_up_val);
  
  //Serial.println ("button down ");
  //Serial.println (button_down_val);
    
  }
};
