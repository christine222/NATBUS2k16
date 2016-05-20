#define rightSensor 14 //outside one 
#define leftSensor 15   //inside one

//helper function for speed (can assign turning)

//implement something that makes the car keep on turning until it sees the line 

#define rightWheelInput1 9
#define rightWheelInput2 10

#define leftWheelInput3 3
#define leftWheelInput4 4

#define enablePinLeft 22 //22 and 23 are our EN1 and EN2
#define enablePinRight 23

#define LED 13


 int sensorRight = 0;    //right and left sensor readings
 int sensorLeft = 0;

 int rightSpeed = 0;     //right and left motor speeds
 int leftSpeed = 0;

 int rightError = 0;     //right and left motor error
 int leftError = 0;

 int rightBaseline = 0;  //right and left motor baseline
 int leftBaseline = 0;

 double kp = 0;          //proportional constant
 double kd = 0;          //derivative constant
 double ki = 0;          //integral constant

 int error = 0;          //error (rightError - leftError)
 int dError = 0;         //derivative error
 int pError = 0;         //previous error
 int integral = 0;       //integral value
 int speedChange = 0;

 int leftTolerance = 50; //right and left sensor tolerance
 int rightTolerance = 50;

 

 int maxSpeed = 100;     //maxSpeed = 70, KpRight = 0.3, KpLeft = 0.5
                         //maxSpeed = 100; KpRight = 0.3, KpLeft = 0.3

 int delaytime = 100;    //time between control loop iterations

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

  // sample and find average value for right and left sensors
  for(int i = 0; i < 200; i++){
     rightBaseline += analogRead(rightSensor);
     leftBaseline += analogRead(leftSensor);
  }

  rightBaseline /= 200;
  leftBaseline /= 200;

  pinMode(LED, OUTPUT);
}


void loop() {
  
  sensorRight = analogRead(rightSensor);     //read right sensor value
  sensorLeft = analogRead(leftSensor);       //read left sensor value

  rightError = sensorRight - rightBaseline;  //calculate right sensor error
  leftError = sensorLeft - leftBaseline;     //calculate left sensor error

  error = rightError - leftError;            //calculate error between sensors
  dError = error - pError;                   //calculate the derivative error
  integral += error;                         //update the integral
  pError = error;                            //update the previous error value
  
  rightSpeed = maxSpeed;                     //set the speed of right motor
  leftSpeed = maxSpeed;                      //set the speed of left motor

  speedChange = (kp*error) + (kd*dError) + (ki*integral); //use PID to calculate the speed change
  rightSpeed -= speedChange;                              //update the right speed
  leftSpeed += speedchange;                               //update the left speed

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

  //update the speed of the right motor to our calculated speed
  analogWrite(enablePinRight, rightSpeed);
  Serial.print("Right Wheel: ");
  Serial.println(rightSpeed);

  //update the speed of the left motor to our calculated speed
  analogWrite(enablePinLeft, leftSpeed);
  Serial.print("Left Wheel: ");
  Serial.println(leftSpeed);
  Serial.println();
  
  digitalWrite(LED, HIGH); 

  delay(delaytime);
}
