#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h> //Ultrasonic sensor function library. You must install this library
#include <L298N.h>


//our L298N control pins
const unsigned int IN1 = 7;
const unsigned int IN2 = 6;
const unsigned int ENA = 9; 

const unsigned int IN3 = 5;
const unsigned int IN4 = 4;
const unsigned int ENB = 10;

L298N motor1(ENA, IN1, IN2);
L298N motor2(ENB, IN3, IN4);


//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name



void setup(){

  Serial.begin(9600);

  
  servo_motor.attach(10); //our servo pin

  servo_motor.write(90);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  Serial.print("Distance: ");
  Serial.println(distance);

      //moveForward(); 
      //delay(10000);
  
  if (distance <= 20){
    Serial.print("Mpika stin if");
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      moveRight();
      delay(500);
      moveStop();
    }
    else{
      moveLeft();
      delay(500);
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(60);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
  servo_motor.write(120);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();

  Serial.println(cm);
  return cm;
}

void moveForward()
{
    motor1.forward();
    motor2.forward();
}

void moveBackward()
{
    motor1.backward();
    motor2.backward();
}

void moveStop()
{
    motor1.stop();
    motor2.stop();
}

void moveRight()
{
   motor2.forward();
   motor1.stop();
}

void moveLeft()
{
   motor1.forward();
   motor2.stop();
}

//void servo move
