/*
This is a simulation code for a servo controlled by the distance measured by an ultrasonic sensor
if the distance < 20cm then the servo opens with a green led as an indicator to show the servo is open
else distance > 20cm the the servo closes with a red a led on to indicate the closed position
This project can be incorporated into smart dustbin where the servo is connected with the lid of the bin.

*/
#include <Servo.h> // include the servo library

const int trigPin = 8; // trigger pi
const int echoPin = 7; // echo pin

int servoPin = 9; // 

int greenLedPin = 12;
int redLedPin = 13;

int closedAngle = 0;
int openAngle = 175;

float duration, distance;
float thresholdDistance = 20; // minimum distance required for the servo to reacte

Servo servo; // naming my servo servo

void setup() {
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT); // set the trigger pin as an output
  pinMode(echoPin, INPUT); // set the echo pin as an input
  pinMode(greenLedPin, OUTPUT); // set the led as an output
  pinMode(redLedPin, OUTPUT); // set the led as an output
  Serial.begin(9600); // begin serial communication

}

void loop() {
  digitalWrite(trigPin, LOW); //set the trigger pin not to send any wave
  delayMicroseconds(2); // delay for 2 micro-seconds
  digitalWrite(trigPin, HIGH);// set the trigger pin to release waves
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  duration = pulseIn(echoPin, HIGH); // get the time for the wave journey
  distance = (duration * 0.0343) / 2; // get the distance if the object

  if (distance >= thresholdDistance) {
    servo.write(closedAngle); // set the servo arm to 0 angle position
    digitalWrite(greenLedPin, LOW); // green led off
    digitalWrite(redLedPin, HIGH); // red led on
    Serial.print("Closed\n"); // prints the string closed on the serial monitor
    Serial.println(distance); // prints the value of the actual distance of the object
  }
  else{
    servo.write(openAngle); // set the servo arm to open position
    digitalWrite(greenLedPin, HIGH); // green led on
    digitalWrite(redLedPin, LOW); // green led off
    Serial.print("Open\n"); // prints the  string open on the serial monitor
    Serial.println(distance); // prints the actual distance of the object
  }
  delay(100); // delay for 100 milli-seconds
}
