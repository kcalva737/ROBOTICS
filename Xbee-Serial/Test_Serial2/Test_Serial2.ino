#include <SoftwareSerial.h>

SoftwareSerial xbee(2,3);

const int maxlength = 9;
int pin;
int value;
char command;
char myString[maxlength];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xbee.begin(9600);
  intro();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(input_string() ){ //if valid string has been detected
    
    pin_assign(command,pin,value);//function that returns char command ,int pin, int value
    //test();
    //print_input()
    
    
    switch(command){ //swtich statetment

    case 'w':      // If received 'w'
    case 'W':      // or 'W'
      writeAPin(pin,value); // Write analog pin
      break;
    case 'd':      // If received 'd'
    case 'D':      // or 'D'
      writeDPin(pin,value); // Write digital pin
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
      //customCode(pin,value); //code for this has not been implemented yet
      break;
    }
  }
}

bool input_string(){//Reads input from the serial communication
  //D12-1234N
  //0123456789
  int i;
  if(Serial.available() >= maxlength && Serial.read() == '#'){
    for(i=0;i<maxlength-1;i++){
      myString[i] = Serial.read();
      //Serial.println(myString[i] );
    }
    /*
    if(myString[3] != '-'){
      Serial.println(myString[3] );
      return false;
    }
    */
    
    return true;
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

void pin_assign(char &command, int &pin, int &value){ //from the input string, this function retrieves values
  int i;
  //char str1;
  char str2[3];//pin
  char str3[5];//value
  //#D12-1234N
  // 0123456789
  
  command = myString[0];

  for(i=0;i<2;i++){
    str2[i] = myString[1+i];
  }
  str2[i] = '\0';
  
  for(i=0;i<4;i++){
    str3[i] = myString[4+i];
  }
  str3[i] = '\0';

  pin = atoi(str2);
  value = atoi(str3);
  
}



void writeDPin(int pin, int val) //this function writes a digital signal to pin 1-13
{
  pinMode(pin, OUTPUT); // Set pin as an OUTPUT
  digitalWrite(pin, val); // Write pin accordingly
}

void writeAPin(int pin, int val) //this function writes an analog value for pin:3,5,6,9,10,11
{
  pinMode(pin, OUTPUT); // Set pin as an OUTPUT
  analogWrite(pin, val); // Write pin accordingly
}

void readDPin(int pin) //This function will read a value for pin 0-13
{
  pinMode(pin, INPUT); // Set as input
  Serial.println(digitalRead(pin));
}

void readAPin(int pin) //this function will read a value from the analog pins A0-A5
{
  Serial.println(analogRead(pin));
}

void test(){ //Debugging code
  Serial.println(myString);  
  
  Serial.println(command);
  Serial.println(pin);
  Serial.println(value);
}
void print_input(){//prints input for the code
  Serial.print(command);
  Serial.print("");
  Serial.print(pin);
  Serial.print("-");
  Serial.println(value);  
}

void intro(){//this code runs on start up 
  Serial.print("Hello, This code is written by SHPE RED 2018.");
  Serial.println("Intro for using this code...\n");
  Serial.println("Commands are inputed in this form:");
  Serial.println(" '#w09-1000'");
  Serial.println(" w = Write Analog pin:3,5,6,9,10,11 Value:(0-255)");
  Serial.println(" d = Write digital");
  Serial.println(" r = Read Digital");
  Serial.println(" a = Read Analog\n");
}


