#ifndef _ARDUINOPIN_
#define _ARDUINOPIN_
extern char channel;

void writeDPin(int pin, int val) //this function writes a digital signal to pin 1-13
{
  pinMode(pin, OUTPUT); // Set pin as an OUTPUT
  digitalWrite(pin, val); // Write pin accordingly
  return;
}

void writeAPin(int pin,int val) //this function writes an analog value for pin:3,5,6,9,10,11
{
  pinMode(pin, OUTPUT); // Set pin as an OUTPUT
  analogWrite(pin, val); // Write pin accordingly
  return;
}

void readDPin(int pin) //This function will read a value for pin 0-13
{ //#BA00-1234
  pinMode(pin, INPUT); // Set as input
  
  Serial.print('#');
  Serial.print(channel);
  Serial.print('R');
  if(pin>9){
    Serial.print(pin);
  }
  else{
    Serial.print(0);
    Serial.print(pin);  
  }
  Serial.print('-');
  Serial.print("000");
  Serial.println(digitalRead(pin));
  return;
}

void readAPin(int pin) //this function will read a value from the analog pins A0-A5
{
  int value = analogRead(pin);
  Serial.print('#');
  Serial.print(channel);
  Serial.print('A');
  if(pin>9){
    Serial.print(pin);
  }
  else{
    Serial.print(0);
    Serial.print(pin);  
  }
  Serial.print('-');
  if(value > 999){
    Serial.println(value);
  }
  else if(value > 99){
    Serial.print("0");
    Serial.println(value);
  }
  else if(value > 9){
    Serial.print("00");
    Serial.println(value);
  }
  else{
    Serial.print("000");
    Serial.println(value);
  }
  return;
}

#endif
