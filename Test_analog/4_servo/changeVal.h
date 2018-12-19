#ifndef _CHANGEVAL_
#define _CHANGEVAL_
int physics(int value){
  double temp;
  double deadZone = 3;
  temp = constrain(value,0,1023);
  temp = temp-511.0;

  Serial.println(temp);
  if(temp < 0.0 - deadZone){
    //Serial.print("valueOne: ");
    //Serial.println(temp);
    
    temp = (temp / 51.0)*(temp / 51.0) + 1.0;
    return -1 * temp;
  }
  else if(temp > 0.0 + deadZone){
    //Serial.print("valueTwo: ");
    //Serial.println(temp);
    temp = (temp / 51.0)*(temp / 51.0) + 1.0;
    //Serial.println(temp);
    return temp;
  }
  else{
    return temp;
  }
}
#endif _CHANGEVAL_
