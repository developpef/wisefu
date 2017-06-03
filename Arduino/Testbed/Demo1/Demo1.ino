/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

#define PIN_ARBRE 2

Servo myservo;  // create servo object to control a servo 

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(PIN_ARBRE,OUTPUT);
}

void loop() {
  // porte
  myservo.write(20);
  delay(2000);

  // arbre
  digitalWrite(PIN_ARBRE,HIGH);
  delay(1000);
  digitalWrite(PIN_ARBRE,LOW);
  delay(1000);
  digitalWrite(PIN_ARBRE,HIGH);
  delay(1000);
  digitalWrite(PIN_ARBRE,LOW);
  delay(1000);
  digitalWrite(PIN_ARBRE,HIGH);
  delay(1000);
  digitalWrite(PIN_ARBRE,LOW);
  delay(1000);

  // porte
  myservo.write(70);
  delay(2000);
}

