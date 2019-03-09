const int potX = 0;
const int potY = 1;
const int deadZone = 100;

int valx;
int valy;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  valx = analogRead(potX);
  valy = analogRead(potY);
  /*
  Serial.print("potX: ");
  Serial.println(valx -523);
  Serial.print("potY: ");
  Serial.println(valy - 523);
  */
  Serial.println("------");
  
  delay(200);

  if(abs(valy - 523) < deadZone && valx < deadZone) {
    turnLeft();
  }
  else if(abs(valy - 523) < deadZone && valx > 1023-deadZone){
    turnRight();
  }
  else if(valy > (1023/2)+deadZone){
    backward(0,valy);
  }
  else if(valy < (1023/2)-deadZone){
    forward(0,valy);
  }
  else{
      noMove();
  }
  

}

void turnLeft(){
  Serial.println("turn left\n");  
}
void turnRight(){
 Serial.println("turn right\n");
}
void forward(int valx, int valy){
  Serial.println(abs(valy-523) );
  Serial.println("move forward\n");
}
void backward(int valx, int valy){
  Serial.println(abs(valy-523) );
  Serial.println("move backward\n");
}
void noMove(){
  Serial.println("-nothin-\n");
}
