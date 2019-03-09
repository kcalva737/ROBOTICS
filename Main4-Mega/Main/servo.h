#ifndef SERVO_H
#define SERVO_H

#include <Servo.h>
class myServo{
  private:
    Servo myservo;
    
  public:
    void servoMove(int pin, int myValue){
    myservo.attach(pin);
    myservo.write(myValue);
    return;
    }
 };

#endif
