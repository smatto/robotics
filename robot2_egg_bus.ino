#include <Servo.h> 

#define servoLeftPin 	7
#define servoRightPin 	6
#define photoPin		0
#define redPin 	 		11
#define greenPin 		10
#define bluePin  		9

Servo servoLeft;
Servo servoRight;

int stillSpeed = 91;
int forwardSpeed = 180;
int backwardSpeed = 0;
int lightReadingOff;
int lightReadingOn;
int lightReadingDifference;
boolean lightIsOn = false;
boolean isObstacle = false;
int flashTime = 200;
unsigned long timer;


void setup() 
{ 
  Serial.begin(9600);
  servoRight.attach(servoRightPin);
  servoLeft.attach(servoLeftPin);
  pinMode(photoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 

} 

void loop() {
	if (millis() > timer){
		if (lightIsOn){
			lightIsOn = false;
			setColor(255,255,255);
			timer = millis() + flashTime;
		}
		else if(!lightIsOn){
			lightIsOn = true;
			setColor(0,20,20);
			timer = millis() + flashTime;
		}
	}

	if (lightIsOn){
		lightReadingOn = analogRead(photoPin);
		//Serial.print("on value: ");
		//Serial.println(lightReadingOn);
	}
	else if(!lightIsOn){
		lightReadingOff = analogRead(photoPin);
		//Serial.print("off value: ");
		//Serial.println(lightReadingOff);
	}
	
	lightReadingDifference = lightReadingOn - lightReadingOff;
	Serial.println(lightReadingDifference);
	if (lightReadingDifference > 50){
		isObstacle = true;
	}
	else{
		isObstacle = false;
	}

	if (isObstacle){
		still();
	}
	else{
		forward();
	}
} 

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void still()
{
	servoRight.write(stillSpeed);
	servoLeft.write(stillSpeed);
}

void backward()
{
	servoRight.write(forwardSpeed);
	servoLeft.write(180 - forwardSpeed);
}

void forward()
{
	servoRight.write(backwardSpeed);
	servoLeft.write(180 - backwardSpeed);
}
