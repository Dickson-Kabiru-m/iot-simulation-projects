/*
This is a simple iot projects using ultrasonic to measure distance.
The ultrasonic used in this project is the HC-SR04.
Ultrasonic works by the trigger sending soundwave which the bounces of an objects and are received by the echo pin.
The distance for the sound wave to bounce of an object and back to the ultrasonic is measured.
N.B Ultrasonic are digital sensors thereby connected to the digital part of the arduino.
*/
const int trigPin = 13; 
const int echoPin = 7;
float duration, distance;
void setup() {
  
  pinMode(trigPin, OUTPUT); //trigger pin is set as an output
  pinMode(echoPin, INPUT); // echo pin is set as an input
  Serial.begin(9600); // to start serial communication

}

void loop() {
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); // to get the time of the wave 
  distance = (0.0343 * duration)/ 2; // to get the distance of one journey of the wave

  Serial.print("distance:"); // prints the string "distance at the serial monitor"
  Serial.println(distance); // print the actual value of the distance
  delay(300); // delay 300 millisecond for the next distance value to be printed

}
