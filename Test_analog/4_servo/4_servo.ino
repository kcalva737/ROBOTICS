#include "pinValue.h"
#include "changeVal.h"

pinValue pin;
int val;
void setup(){
  Serial.begin(9600);
  pin.set_analog( 9,physics(analogRead(A0) ));

}
void loop(){
  val = analogRead(A0);
  val = physics(val);
  
  val = pin.return_analog(9) + val;
  pin.set_analog(9, val);
  
  pin.print_analog();
  delay(500);//Good time frame for real physics
}
