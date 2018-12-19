/*This program has been written with the purpose to implement Serial.read and Xbee.read.
 * 
 * This code will be used by low level language and has the extent to be used with higher level languages such as python. The serial communicatoin renders the Arduino to be a slave.
 * The Arduino will be able to execute any code given to it through serial communication.
 * 
 * 
 */
#include "arduino.h"
#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial xbee(2,3);
Servo myservo;

const int maxlength = 9;
int pin;
int myValue;
char command;
char myString[maxlength];

void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  xbee.begin(9600);
  
  //delay(500);
  //Serial.print("Test One");
  //while(!Console);
  intro();
}
void loop() {
  if(input_string() ){
    //print_input();
      if(pin_assign(command,pin,myValue) ){
        //test();
        print_input();
        
        switch(command){ //swtich statetment

        case 'w':      // If received 'w'
        case 'W':      // or 'W'
          writeAPin(pin,myValue); // Write analog pin
          break;
        case 'd':      // If received 'd'
        case 'D':      // or 'D'
          writeDPin(pin,myValue); // Write digital pin
          break;
        case 'r':      // If received 'r'
        case 'R':      // or 'R'
          readDPin(pin);  // Read digital pin
          break;
        case 'a':      // If received 'a'
        case 'A':      // or 'A'
          readAPin(pin);  // Read analog pin
          break;
        case 'M':
        case 'm':
          servoMove(pin,myValue);
          break;
        }
      }
  }
}








bool input_string(){//Reads input from the serial communication
  //#D12-1234N
  // 0123456789
  int i;
  //char temp;
  //if(Serial.available() ){
  //   temp = Serial.read();
  //  Serial.println(char(temp) );
  //  Serial.println(Serial.available() );
  //}
  char temp = Serial.read();
  if(Serial.available() >= maxlength-1 && temp == '#'){
    for(i=0;i<maxlength-1;i++){
      myString[i] = Serial.read();
      //Serial.println(myString[i] );
    }
    myString[8] = '\0';
    
    //Serial.println(myString);
    
    return true;
  }
  else if(temp == '?'){
  intro();
  return false;
  }
  else{
    return false;
  }
}

bool input_xbee(){
    if(xbee.available() >=  9 && xbee.read() == '#'){
    int i;
    byte temp;
    for(i=0;i < maxlength-1;i++){
      temp = xbee.read();
      myString[i] = temp;
    }
    myString[maxlength-1] = '\0';
    //Serial.println(myString);
    return true;
  }
  return false;
}






bool pin_assign(char &command, int &pin, int &myValue){ //from the input string, this function retrieves values
  int i;
  //char str1;
  char str2[3];//pin
  char str3[5];//value
  //#D12-1234N
  // 0123456789
  if(isalpha(myString[0]) ){
    command = myString[0];
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

  pin = atoi(str2);
  myValue = atoi(str3);

  return true;
}

void servoMove(int pin, int myValue){
  myservo.attach(pin);
  myservo.write(myValue);  
  return;
}

void writeDPin(int pin, int val) //this function writes a digital signal to pin 1-13
{
  pinMode(pin, OUTPUT); // Set pin as an OUTPUT
  digitalWrite(pin, val); // Write pin accordingly
  return;
}

void writeAPin(int pin, int val) //this function writes an analog value for pin:3,5,6,9,10,11
{
  pinMode(pin, OUTPUT); // Set pin as an OUTPUT
  analogWrite(pin, val); // Write pin accordingly
  return;
}

void readDPin(int pin) //This function will read a value for pin 0-13
{
  pinMode(pin, INPUT); // Set as input
  Serial.println(digitalRead(pin));
  return;
}

void readAPin(int pin) //this function will read a value from the analog pins A0-A5
{
  Serial.println(analogRead(pin));
  return;
}

void test(){ //Debugging code
  Serial.println(myString);  
  
  Serial.println(command);
  Serial.println(pin);
  Serial.println(myValue);
}
void print_input(){//prints input for the code
  Serial.print(command);
  Serial.print("");
  Serial.print(pin);
  Serial.print("-");
  Serial.println(myValue);  
}

void intro(){//this code runs on start up 
  Serial.print("Hello, This code is written by SHPE RED 2018.");
  Serial.println("Intro for using this code...\n");
  Serial.println("Commands are inputed in this form:");
  Serial.println(" '#w09-1000'");
  Serial.println(" w = Write Analog pin:3,5,6,9,10,11 Value:(0-255)");
  Serial.println(" d = Write digital");
  Serial.println(" r = Read Digital");
  Serial.println(" a = Read Analog");
  Serial.println(" m = servoMove");
}

