#include <Servo.h>

#define headLight 16
#define breakLight 5
#define mot1En 2
#define mot1For 0
#define mot1Back 4
#define mot2En 14
#define mot2For 13
#define mot2Back 12
Servo steer;
void setup() {
  // put your setup code here, to run once:
pinMode(headLight,OUTPUT);
pinMode(breakLight,OUTPUT);
pinMode(mot1En,OUTPUT);
pinMode(mot1For,OUTPUT);
pinMode(mot1Back,OUTPUT);
pinMode(mot2En,OUTPUT);
pinMode(mot2For,OUTPUT);
pinMode(mot2Back,OUTPUT);
steer.attach(15);
steer.write(90);
digitalWrite(headLight,LOW);
digitalWrite(breakLight,LOW);
digitalWrite(mot1En,HIGH);
digitalWrite(mot1For,LOW);
digitalWrite(mot1Back,LOW);
digitalWrite(mot2En,HIGH);
digitalWrite(mot2For,LOW);
digitalWrite(mot2Back,LOW);
Serial.begin(9600);
}

void loop() {
  
    while(Serial.available()==0){
      //Serial.println("...");  
    }int command=0;
    command=Serial.parseInt();
    Serial.println(command);
  switch(command){
    case 1:
      Serial.println("HeadLight on");
      digitalWrite(headLight,HIGH);
      delay(1000);
      break;
    case 2:
      Serial.println("HeadLight off");
      digitalWrite(headLight,LOW);
      delay(1000);
      break;
    case 3:
      Serial.println("BreakLight on");
      digitalWrite(breakLight,HIGH);
      delay(1);
      break;
    case 4:
      Serial.println("BreakLight off");
      digitalWrite(breakLight,LOW);
      delay(1);
      break;
    case 5:
      Serial.println("Moving forward");
      digitalWrite(mot1For,HIGH);delay(1);
      digitalWrite(mot1Back,LOW);delay(1);
      digitalWrite(mot2For,HIGH);delay(1);
      digitalWrite(mot2Back,LOW);delay(1);
      break;
    case 6:
      Serial.println("Moving backward");
      digitalWrite(mot1For,LOW);delay(1);
      digitalWrite(mot1Back,HIGH);delay(1);
      digitalWrite(mot2For,LOW);delay(1);
      digitalWrite(mot2Back,HIGH);delay(1);
      break;
    case 7:
      Serial.println("Stoping car");
      digitalWrite(mot1For,LOW);delay(1);
      digitalWrite(mot1Back,LOW);delay(1);
      digitalWrite(mot2For,LOW);delay(1);
      digitalWrite(mot2Back,LOW);delay(1);
      break;
    case 9:
      Serial.println("Turning left");
      steer.write(65);
      break;
    case 10:
      Serial.println("Turning right");
      steer.write(115);
      break;
     default:digitalWrite(headLight,LOW);break;
  }
}
