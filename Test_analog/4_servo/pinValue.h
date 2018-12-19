#ifndef _PINVALUE_
#define _PINVALUE_

class pinValue{
  private:
    int pin;
    
    bool *myPin;
    int *myAnalog;
    bool *digit;

  public:
    pinValue(){
      int i;
      pin = 13;
      myPin = new bool[pin]; //Store on/off
      myAnalog = new int[pin];//store analog value
      digit = new bool[pin]; //store if pin is being used as digital or analog
      
      for(i=0;i<pin;i++){
        myPin[i] = 0;
        myAnalog[i] = 0;
        digit[i] = 0;
      }
    }
    bool return_pin(int index){
      return myPin[index+1];
    }
    int return_analog(int index){
      return myAnalog[index+1];
    }
    bool return_digit(int index){
      return digit[index+1];
    }
    
    void set_analog(int index, int value){
        //value = value - 511;
        value = constrain(value,-511,511);
        myAnalog[index+1] = value;
        return;
    }

    
    void print_pin(){
      int i;
      for(i=0;i<pin;i++){
        Serial.print(myPin[i] );
        Serial.print(", ");
      }
      Serial.println();
    }
    void print_analog(){
      int i;
      for(i=0;i<pin;i++){
        Serial.print(myAnalog[i] );
        Serial.print(", ");
      }
      Serial.println();
    }
    void print_digit(){
      int i;
      for(i=0;i<pin;i++){
        Serial.print(digit[i] );
        Serial.print(", ");
      }
      Serial.println();
    }
};



#endif
