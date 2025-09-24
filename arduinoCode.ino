#define trigPin 9
#define echoPin 8
#define MLa 4
#define MLb 5
#define MRa 6
#define MRb 7
#define enableL 3
#define enableR 11
#define greenLED 12   // Green part of RGB
#define blueLED 13    // Blue part of RGB
#define redLED 2      // Separate Red LED

long duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(MLa, OUTPUT);
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);
  pinMode(enableL, OUTPUT);
  pinMode(enableR, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  // Start with Green LED ON, others OFF
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
}

void loop() {
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  // LED Control Logic
  if (distance > 70) {
    digitalWrite(greenLED, HIGH); // Green ON
    digitalWrite(blueLED, LOW);   // Blue OFF
  } else {
    digitalWrite(greenLED, LOW);  // Green OFF
    digitalWrite(blueLED, HIGH);  // Blue ON
  }

  if (distance > 70) {
    moveForward(255);
    digitalWrite(redLED, LOW);  // Red OFF (car moving)
  } else if (distance <= 70 && distance > 55) {
    moveForward(200);
    digitalWrite(redLED, LOW);
  } else if (distance <= 55 && distance > 40) {
    moveForward(150);
    digitalWrite(redLED, LOW);
  } else if (distance <= 40 && distance > 25) {
    moveForward(100);
    digitalWrite(redLED, LOW);
  } else if (distance <= 25 && distance > 10) {
    moveForward(50);
    digitalWrite(redLED, LOW);
  } else if (distance <= 10) {
    stopMotors();
    digitalWrite(redLED, HIGH);  // Red ON (car stops)
  }
  
  delay(100);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 500;
  return duration / 58.2;
}

void moveForward(int speed) {
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);
  analogWrite(enableL, speed);
  analogWrite(enableR, speed);
}

void stopMotors() {
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);
  analogWrite(enableL, 0);
  analogWrite(enableR, 0);
}
