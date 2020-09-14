/***********************************************************************************
  Arduino Engineering Kit Ultrasonic Range Sensor Test
  This sketch demonstrates some APIs exposed by the MKR Motor Shield library.
  For the complete list, visit the reference page on https://www.arduino.cc/en/Reference/MKRMotorShield
  This example code is in the public domain.

  Description: Uses the seed ultrasonic range sensor connected to IN1 or IN2 and plot the values
  in serial monitor
 ****************************************************************************************/

// this constant won't change. It's the pin number of the sensor's output:

//const int pingPin = A6; // IN1
//const int pingPin = A1; // IN2
//const int pingPin = A5; // IN3
const int pingPin = A2; // IN4

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm, mm;

  // The sensor is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the bounced signal: The latency of this HIGH pulse
  //represents the flight time of the sound wave in microsencods.

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  mm = microsecondsToMilimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm, ");
  Serial.print(mm);
  Serial.print("mm");
  Serial.println();

  delay(100);
}

long microsecondsToInches(long microseconds) {
  // There are 73.746 microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the soundwave, back and forth,
  // We divice the total time by 2 to get the distance to the object.
  return microseconds / 74 / 2;
}

long microsecondsToMilimeters(long microseconds) {
  // The speed of sound is 340 m/s or 2.9 microseconds per milimeter.
  // We divice the total time by 2 to get the distance to the object.
  return microseconds / 2.9 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // We divice the total time by 2 to get the distance to the object.
  return microseconds / 29 / 2;
}
