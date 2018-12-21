#ifndef _ARDUINOPIN_
#define _ARDUINOPIN_

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

#endif
