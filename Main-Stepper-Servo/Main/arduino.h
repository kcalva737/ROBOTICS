#ifndef ARDUINO_H
#define ARDUINO_H

#include <SoftwareSerial.h>
SoftwareSerial xbee(2,3);

class SerialString{
  //#B13-1234N
  // 0123456789
  private:
  
    int maxlength;
    
    int myPin;
    int myValue;
    char myCommand;
    
    char *myString;
 
 public:
    SerialString(){
      maxlength = 9;
      myString = new char[maxlength];  
    }   
    int pin(){
      return myPin;
    }
    int val(){
      return myValue;  
    }
    char command(){
      return myCommand;
    }

    bool input_string();
    bool input_xbee();
    bool pin_assign();

    void test();
    void print_input();
    void intro();
    
};

bool SerialString::input_string(){
  int i;
  char tempOne = Serial.read();
  char tempTwo = Serial1.read();
  delay(10);
  
  if(Serial.available() >= maxlength-1 && tempOne == '#'){
    for(i=0;i<maxlength-1;i++){
      myString[i] = Serial.read();
    }
    myString[8] = '\0';
    //Serial.println("input_string() One");
    return true;
  }
  else if(Serial1.available() >= maxlength-1 && tempTwo == '#'){
    for(i=0;i<maxlength-1;i++){
      myString[i] = Serial1.read();
    }
    myString[8] = '\0';
    Serial.println("input_string() Two");
    return true;
  }
  else if(tempOne == '?' || tempTwo == '?'){
    //Serial.println("input_string() Two");
    intro();
    return false;
  }
  else{
    return false;
  }
}

bool SerialString::input_xbee(){
    int i;
    byte temp;
    char tempOne = xbee.read();
    delay(10);
    if(xbee.available() >=  maxlength-1 &&  tempOne == '#'){
      for(i=0;i < maxlength-1;i++){
        temp = xbee.read();
        myString[i] = temp;
      }
      myString[maxlength-1] = '\0';
      
      return true;
    }
    else if( temp == '?' ){
      intro();
      return false;
    }
    else{
      return false;
    }
}

bool SerialString::pin_assign(){ //from the input string, this function retrieves values
  int i;
  
  char str2[3];//pin
  char str3[5];//value
  //#D12-1234N
  // 0123456789
  if(isalpha(myString[0]) ){
    myCommand = myString[0];
  }
  else{
    return false;
  }

  for(i=0;i<2;i++){
    if(isdigit(myString[1+i]) ){
      str2[i] = myString[1+i];
    }
    else{
      return false;
    }
  }
  str2[2] = '\0';
  
  for(i=0;i<4;i++){
    if(isdigit(myString[4+i]) ){
      str3[i] = myString[4+i];
    }
    else{
      return false; 
    }
  }
  str3[4] = '\0';

  myPin = atoi(str2);
  myValue = atoi(str3);

  return true;
}

void SerialString::test(){ //Debugging code
  Serial.println(myString);  
  
  Serial.println(myCommand);
  Serial.println(myPin);
  Serial.println(myValue);
}
void SerialString::print_input(){//prints input for the code
  Serial.print(" Input: ");
  Serial.print(myCommand);
  Serial.print(myPin);
  Serial.print("-");
  Serial.println(myValue);  
}

void SerialString::intro(){//this code runs on start up 
  Serial.print("\nHello, This code is written by SHPE RED 2018.");
  Serial.println("Intro for using this code...\n");
  Serial.println("Commands are inputed in this form:");
  Serial.println(" '#w09-1000'");
  Serial.println(" w = Write Analog pin:3,5,6,9,10,11 Value:(0-255)");
  Serial.println(" d = Write digital");
  Serial.println(" r = Read Digital");
  Serial.println(" a = Read Analog");
  Serial.println(" m = servoMove");
  Serial.println(" T = moveStepper ClockWise: Value = length");
  Serial.println(" t = moveStepper Counter-ClockWise: Value = length");
  Serial.println();
  
}

#endif
