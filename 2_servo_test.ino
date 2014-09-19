#include <Servo.h> 

Servo servoLeft;
Servo servoRight;

int stillSpeed = 91;
int forwardSpeed = 180;
int backwardSpeed = 0;

void setup() 
{ 
  servoRight.attach(6);
  servoLeft.attach(7);
} 

void loop() {

	forward();
	delay(1000);
	still();
	delay(1000);
	backward();
	delay(1000);
} 

void still()
{
	servoRight.write(stillSpeed);
	servoLeft.write(stillSpeed);
}

void forward()
{
	servoRight.write(forwardSpeed);
	servoLeft.write(180 - forwardSpeed);
}

void backward()
{
	servoRight.write(backwardSpeed);
	servoLeft.write(180 - backwardSpeed);
}
