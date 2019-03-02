#ifndef ARDUINO_H
#define ARDUINO_H
extern char channel;

#include <SoftwareSerial.h>
SoftwareSerial xbee(2,3);

void decode(unsigned char *myChar,int& pin, int& value){
  pin=0;//range: [0-65]
  value=0;//range: [0-1023]

  for(unsigned int i=0;i<8;i++){
    value += (myChar[2]&1) * (1<<i);
    myChar[2] = myChar[2]>>1;
  }
  for(unsigned int i=0;i<2;i++){
    value += (myChar[1 ] &1) * (1 << (i+8));
    myChar[1] = myChar[1]>>1;
  }

  for(unsigned int i=0;i<6;i++){
    pin += (myChar[1] & 1) * (1 << i);
    myChar[1] = myChar[1] >>1;
  }

}

class SerialString{
  //#B13-1234N
  // 0123456789
  //public:
  private:
  
    int maxlength;
    
    int myPin;
    int myValue;
    char myCommand;
    //char myChannel;
    
    char *myString;
 
 public:
    SerialString(){
      maxlength = 9;
      myString = new char[maxlength];
      myCommand = '+';
      //myChannel = channel;
    }   
    int& pin(){
      return this->myPin;
    }
    int& val(){
      return this->myValue;  
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
  char temp = Serial.read();
  char tempTwo;
  delay(10);
  
  if(Serial.available() > maxlength-1 && temp == '#'){
    if(Serial.read() != channel){
      return false;
    }
    
    for(i=0;i<maxlength-1;i++){
      myString[i] = Serial.read();
    }
    myString[8] = '\0';
    //Serial.println("input_string() One");
    return true;
  }
  else if(temp == '?'){
    //Serial.println("input_string() Two");
    intro();
    return false;
  }
  else{
    return false;
  }
}

bool SerialString::input_xbee(){//test function, need further test
  unsigned char myChar[4];
  delay(1);
  if(xbee.available() < 3){//if length is less than 3, return false
    return false;
  }
  if(xbee.read() !='#'){//if first char is not #, return false
    return false;
  }
  
  myChar[0] = '#';
  for(unsigned int i=1;i<3;i++){//saving string
    myChar[i] = xbee.read();
  }

  decode(myChar,this->myPin,this->myValue);//convert str to int

  return true;//successfully converted, return true

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
  Serial.println("Intro for using this code...");
  Serial.print("Channel: ");
  Serial.println(channel);
  Serial.println("Commands are inputed in this form:");
  Serial.print(" '#");
  Serial.print(channel);
  Serial.println("w09-1000'");
  Serial.println(" w = Write Analog pin:3,5,6,9,10,11 Value:(0-255)");
  Serial.println(" d = Write digital");
  Serial.println(" r = Read Digital pin: 0-13");
  Serial.println(" a = Read Analog pin: 00 - 07");
  Serial.println(" m = servoMove\n");
}

#endif
