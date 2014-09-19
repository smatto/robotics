// States
#define IDLE          0
#define FORWARD       1
#define REVERSE       2
#define FORWARD_LEFT  3
#define FORWARD_RIGHT 4
#define REVERSE_LEFT  5
#define REVERSE_RIGHT 6

//define pins
#define startPin      0
#define forwardPin    3
#define reversePin    5
#define leftPin       8
#define rightPin      9


#define STRAIGHT_TIME 200
#define TURN_TIME     200
#define DECEL_TIME    200
#define SPEED         75

int state = IDLE;
boolean returning = false;
boolean start = false;
unsigned long nextAction;

void  setup() 
{                
  Serial.begin(9600);
  pinMode(forwardPin, OUTPUT); // forward
  pinMode(reversePin, OUTPUT); // backward
  pinMode(leftPin, OUTPUT); // left
  pinMode(rightPin, OUTPUT); // right
  pinMode(startPin, INPUT); //start
}
//end setup

void  loop()
{
  int buttonState = digitalRead(startPin);
  
  if(buttonState == 1)
    {
      start = true;
    }
  else
    {
      start = false;
    }

  if(millis() > nextAction)
  {  
    switch(state)
    {
      case IDLE:
        idle();
        if(start == true)
        {
          state = FORWARD;
        }
        else
        { 
          state = IDLE;
        }
      break;
      case FORWARD:
        forward();
        if(returning == false)
        {
          state = FORWARD_RIGHT;
        }
        else
        {
          state = FORWARD_LEFT;
        }
        break;
      case FORWARD_RIGHT:
        forwardRight();
        state = REVERSE_LEFT;
        break;
      case REVERSE_LEFT:
        reverseLeft();
        state = FORWARD;
        returning = true;
        break;
      case FORWARD_LEFT:
        forwardLeft();
        state = REVERSE_RIGHT;
        break;
      case REVERSE_RIGHT:
        reverseRight();
        state = IDLE;
        returning = false;
        break;
      default:
        state = IDLE;
        break;
    }
  }
}
//end loop

void  idle()
{
  state = IDLE;
  Serial.println("Idle");
  analogWrite(forwardPin,0);
  analogWrite(reversePin,0);
  digitalWrite(leftPin,LOW);
  digitalWrite(rightPin,LOW);
  nextAction = millis() + STRAIGHT_TIME;
}

void  forward()
{
  Serial.println("Forward");
  analogWrite(forwardPin,SPEED);
  analogWrite(reversePin,0);
  digitalWrite(leftPin,LOW);
  digitalWrite(rightPin,LOW); 
  state = FORWARD;
  nextAction = millis() + STRAIGHT_TIME;
 }

void  reverse()
{
  Serial.println("Reverse");
  analogWrite(forwardPin,0);
  analogWrite(reversePin,SPEED);
  digitalWrite(leftPin,LOW);
  digitalWrite(rightPin,LOW); 
  state = REVERSE;
  nextAction = millis() + STRAIGHT_TIME; 
}

void  forwardLeft()
{ 
  Serial.println("Forward_Left");
  analogWrite(forwardPin,SPEED);
  analogWrite(reversePin,0);
  digitalWrite(leftPin,HIGH);
  digitalWrite(rightPin,LOW);
  state = FORWARD_LEFT;
  nextAction = millis() + TURN_TIME;
}  

void  forwardRight()
{ 
  Serial.println("Forward_Right");
  analogWrite(forwardPin,SPEED);
  analogWrite(reversePin,0);
  digitalWrite(leftPin,LOW);
  digitalWrite(rightPin,HIGH);
  state = FORWARD_RIGHT;
  nextAction = millis() + TURN_TIME;
}

void  reverseLeft()
{ 
  Serial.println("Reverse_Left");
  analogWrite(forwardPin,0);
  analogWrite(reversePin,SPEED*2);
  digitalWrite(leftPin,LOW);
  digitalWrite(rightPin,HIGH);
  state = REVERSE_LEFT;
  nextAction = millis() + TURN_TIME;
}

void  reverseRight()
{ 
  Serial.println("Reverse_Right");
  analogWrite(forwardPin,0);
  analogWrite(reversePin,SPEED*2);
  digitalWrite(leftPin,LOW);
  digitalWrite(rightPin,HIGH);
  state = REVERSE_RIGHT;
  nextAction = millis() + TURN_TIME;
}
