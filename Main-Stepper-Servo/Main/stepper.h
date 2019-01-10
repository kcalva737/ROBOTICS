#ifndef _STEPPER_
#define _STEPPER_

#include<Stepper.h>

class Stepp{
  private:
  //values
  int Large_Potpin;// = 0;
  int Button1_Large_Pin;// = 52;
  int Button2_Large_Pin;// = 50;


  //assigning stepper drive pin number
  int Stepper_Large_ENA;// = 23;
  int Stepper_Large_IN1;// = 25;  //Pull+
  int Stepper_Large_IN2;// = 27;  //pull-
  int Stepper_Large_IN3;// = 29;  //dir+
  int Stepper_Large_IN4;// = 31;  //dir-
  int Stepper_Large_ENB;// = 35;

  int valLarge;// = 0;
  int Button1_Large;// = 0;
  int Button2_Large;// = 0;

  public:
  Stepp(int pot, int button1, int button2, int ENA, int IN1, int IN2, int IN3, int IN4, int ENB){
    Large_Potpin = pot;
    Button1_Large_Pin = button1;
    Button2_Large_Pin = button2;

    Stepper_Large_ENA = ENA;
    Stepper_Large_IN1 = IN1;
    Stepper_Large_IN2 = IN2;
    Stepper_Large_IN3 = IN3;
    Stepper_Large_IN4 = IN4;
    Stepper_Large_ENB = ENB;
  }
  void step_start(){
    pinMode(Button1_Large_Pin, INPUT);
    pinMode(Button2_Large_Pin, INPUT);

    pinMode(Stepper_Large_ENA,OUTPUT);
    pinMode(Stepper_Large_IN1,OUTPUT);
    pinMode(Stepper_Large_IN2,OUTPUT);
    pinMode(Stepper_Large_IN3,OUTPUT);
    pinMode(Stepper_Large_IN4,OUTPUT);
    pinMode(Stepper_Large_ENB,OUTPUT);  
  }
  void step_loop(){
    valLarge = analogRead(Large_Potpin);
    Button1_Large = digitalRead(Button1_Large_Pin);
    Button2_Large = digitalRead(Button2_Large_Pin);
  }

  void step_print(){
    Serial.print("valLarge: ");
    Serial.println(valLarge);
    Serial.print("Button1_Large: ");
    Serial.println(Button1_Large);
    Serial.print("Button2_Large: ");
    Serial.println(Button2_Large);
    //delay(1000);
  }

  void step_move(){
    controlStepper(valLarge, Button1_Large, Button2_Large);
  }
  
  
  
  void controlStepper(int valLarge, int Button1_Large, int Button2_Large){
      if( (valLarge > 171) and (valLarge < 831) ){
        if(Button1_Large != 0) {
          forward(10,1);
          delay(1);
        }
        if(Button2_Large != 0) {
          backward(10,1);
          delay(1);
        }
      }
         
      if (valLarge < 171){   
       if(Button1_Large != 0) {
          forward(10,1);
          delay(1);
        }                    // set Sleep mode ON    
      }
      if(valLarge > 831) {
        if(Button2_Large != 0) {
          backward(10,1);
          delay(1);
         }
      }
    
       digitalWrite(Stepper_Large_ENA, HIGH);
       digitalWrite(Stepper_Large_ENB, HIGH);
  }
  
  
  void backward(int i,int j) {
    // set both motors ON
    digitalWrite(Stepper_Large_ENA, HIGH);
    digitalWrite(Stepper_Large_ENB, HIGH);
  
    while (1)   {
      digitalWrite(Stepper_Large_IN1, 0);
      digitalWrite(Stepper_Large_IN2, 1);
      digitalWrite(Stepper_Large_IN3, 0);
      digitalWrite(Stepper_Large_IN4, 1);
      delay(j);
      i--;
      if (i < 1) break; 
  
      digitalWrite(Stepper_Large_IN1, 0);
      digitalWrite(Stepper_Large_IN2, 1);
      digitalWrite(Stepper_Large_IN3, 1);
      digitalWrite(Stepper_Large_IN4, 0);
      delay(j);  
      i--;
      if (i < 1) break;
  
      digitalWrite(Stepper_Large_IN1, 1);
      digitalWrite(Stepper_Large_IN2, 0);
      digitalWrite(Stepper_Large_IN3, 1);
      digitalWrite(Stepper_Large_IN4, 0);
      delay(j);
      i--;
      if (i < 1) break;
  
      digitalWrite(Stepper_Large_IN1, 1);
      digitalWrite(Stepper_Large_IN2, 0);
      digitalWrite(Stepper_Large_IN3, 0);
      digitalWrite(Stepper_Large_IN4, 1);
      delay(j);  
      i--;
      if (i < 1) break;
    }
  
    // set both motors OFF
    digitalWrite(Stepper_Large_ENA, LOW);
    digitalWrite(Stepper_Large_ENB, LOW);
    
  }  
  
  void forward(int i, int j) {
    // Set both motors ON
    digitalWrite(Stepper_Large_ENA, HIGH);
    digitalWrite(Stepper_Large_ENB, HIGH);
  
    while (1)   {
      digitalWrite(Stepper_Large_IN1, 0);
      digitalWrite(Stepper_Large_IN2, 1);
      digitalWrite(Stepper_Large_IN3, 0);
      digitalWrite(Stepper_Large_IN4, 1);
      delay(j);  
      i--;
      if (i < 1) break;
  
      digitalWrite(Stepper_Large_IN1, 1);
      digitalWrite(Stepper_Large_IN2, 0);
      digitalWrite(Stepper_Large_IN3, 0);
      digitalWrite(Stepper_Large_IN4, 1);
      delay(j);
      i--;
      if (i < 1) break;
  
      digitalWrite(Stepper_Large_IN1, 1);
      digitalWrite(Stepper_Large_IN2, 0);
      digitalWrite(Stepper_Large_IN3, 1);
      digitalWrite(Stepper_Large_IN4, 0);
      delay(j);  
      i--;
      if (i < 1) break;
  
      digitalWrite(Stepper_Large_IN1, 0);
      digitalWrite(Stepper_Large_IN2, 1);
      digitalWrite(Stepper_Large_IN3, 1);
      digitalWrite(Stepper_Large_IN4, 0);
      delay(j);
      i--;
      if (i < 2) break;
    }
  
    // set both motors OFF
    digitalWrite(Stepper_Large_ENA, LOW);
    digitalWrite(Stepper_Large_ENB, LOW);
  
  } 

};
#endif
