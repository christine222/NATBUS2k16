#define rightSensor 14 //outside one 
#define leftSensor 15   //inside one

//helper function for speed (can assign turning)

//implement something that makes the car keep on turning until it sees the line 

#define rightWheelInput1 9
#define rightWheelInput2 10

#define leftWheelInput3 3
#define leftWheelInput4 4

#define enablePinLeft 22
#define enablePinRight 23

#define LED 13
//22 and 23 are our EN1 and EN2

 int sensorRight = 0;
 int sensorLeft = 0;

 int rightSpeed = 0;
 int leftSpeed = 0;

 int rightError = 0;
 int leftError = 0;

 int rightBaseline = 0;
 int leftBaseline = 0;

 double KpRight = 0.3;
 double KpLeft = 0.3;
 int leftTolerance = 50;
 int rightTolerance = 50;

 int maxSpeed = 100; //maxSpeed = 70, KpRight = 0.3, KpLeft = 0.5
                      //maxSpeed = 100; KpRight = 0.3, KpLeft = 0.3

 int delaytime = 100;

void setup() {
  Serial.begin(9600);

  

  pinMode(rightSensor, INPUT);
  pinMode(leftSensor, INPUT);

  pinMode(rightWheelInput1, OUTPUT);
  pinMode(rightWheelInput2, OUTPUT);

  pinMode(leftWheelInput3, OUTPUT);
  pinMode(leftWheelInput4, OUTPUT);

  pinMode(enablePinRight, OUTPUT);
  pinMode(enablePinLeft, OUTPUT);

  for(int i = 0; i < 200; i++){
     rightBaseline += analogRead(rightSensor);
     leftBaseline += analogRead(leftSensor);
  }

  rightBaseline /= 200;
  leftBaseline /= 200;



  pinMode(LED, OUTPUT);
}


/*void pedalToTheMetal(int side, int error){

  rightSpeed = map(error,0,rightBaseline,0, rightBaseline);
  leftSpeed = map(
  
  if(side == 0){ //right side
    
  }

  if(side == 1){ //left side
    
  }
}*/

void loop() {

/*
  Serial.print("RightBaseline: ");
  Serial.println(rightBaseline);
  Serial.print("LeftBaseline: ");
  Serial.println(leftBaseline);
  Serial.println();
 */

  rightSpeed = maxSpeed;
  leftSpeed = maxSpeed;
  
  sensorRight = analogRead(rightSensor);
  sensorLeft = analogRead(leftSensor);

  rightError = sensorRight - rightBaseline;
  leftError = sensorLeft - leftBaseline;





  if(rightError < 0){
    rightError *= -1;
  }
  if(leftError < 0){
    leftError *= -1;
  }

  //rightError *=(255/1023);
  //leftError *=(255/1023);



  if(rightError > rightTolerance){
    rightSpeed -= (KpRight*rightError);
    leftSpeed += (KpLeft*rightError);
  }
  else if(leftError > leftTolerance){
    rightSpeed += (KpRight*leftError);
    leftSpeed -= (KpLeft*leftError);
  }
  else{
    rightSpeed= maxSpeed;
    leftSpeed= maxSpeed;
  }

  //don't want it to be negative
  if (rightSpeed < 0){
    rightSpeed  = 0;
  }
  if (leftSpeed < 0){
    leftSpeed = 0;
  }

  //don't want it to exceed 255
  if (rightSpeed >maxSpeed){
    rightSpeed = maxSpeed;
  }
  if (leftSpeed >maxSpeed){
    leftSpeed = maxSpeed;
  }

/*  Serial.print("Right: ");
  Serial.println(sensorRight);
  Serial.print("Left: ");
  Serial.println(sensorLeft);
  Serial.println();

 */

  Serial.print("rightError: ");
  Serial.println(rightError);
  Serial.print("leftError: ");
  Serial.println(leftError);
  Serial.println();

  //this makes it go forward: having rightWheelInput1: HIGH, rightWheelInput2: LOW
  //this makes it go forward: having leftWheelInput3: HIGH, leftWheelInput4: LOW
  digitalWrite(rightWheelInput1, HIGH);
  digitalWrite(rightWheelInput2, LOW);

  digitalWrite(leftWheelInput3, HIGH);
  digitalWrite(leftWheelInput4, LOW);


  /*if(sensorRight > 700){

    rightSpeed = 50;
    
  }

  if(sensorLeft > 700){,
    leftSpeed = 50;
  }
*/
analogWrite(enablePinRight, rightSpeed);
Serial.print("Right Wheel: ");
Serial.println(rightSpeed);

analogWrite(enablePinLeft, leftSpeed);
Serial.print("Left Wheel: ");
Serial.println(leftSpeed);
Serial.println();
  digitalWrite(LED, HIGH); 

  delay(delaytime);
}
