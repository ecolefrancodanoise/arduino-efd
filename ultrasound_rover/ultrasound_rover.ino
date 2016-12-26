#include <Servo.h>

int servoPin = 9;
Servo myservo;

//Motor pins
int directionLeftPin = 12;
int directionRightPin = 13;
int powerLeftPin = 3;
int powerRightPin = 11;

//Ultrasonic sensor pins
int inputPin  = 4;    // define pin for sensor echo
int outputPin = 5;    // define pin for sensor trig

void setup() {
    Serial.begin(9600);
    myservo.attach(servoPin);
    pinMode(directionLeftPin, OUTPUT);
    pinMode(directionRightPin, OUTPUT);
    pinMode(powerLeftPin, OUTPUT);
    pinMode(powerRightPin, OUTPUT);
    pinMode(inputPin, INPUT);
    pinMode(outputPin, OUTPUT);
}

/*
 * Return the distance read by the ultrasound sensor
 */
 float readDistance() {
    digitalWrite(outputPin, LOW);   // ultrasonic sensor transmit low level signal 2μs
    delayMicroseconds(2);
    digitalWrite(outputPin, HIGH);  // ultrasonic sensor transmit high level signal10μs, at least 10μs
    delayMicroseconds(10);
    digitalWrite(outputPin, LOW);    // keep transmitting low level signal
    float pingTime = pulseIn(inputPin, HIGH);  // read the time in between
    float distance = pingTime / 58.1;
    return distance;
}

/**
 * Turns the rover by angle (positive is left, negative is right)
 */
void turn(const float angle) {
    if (angle > 0) {
        digitalWrite(directionLeftPin, LOW);
        digitalWrite(directionRightPin, HIGH);
        analogWrite(powerLeftPin, 200);
        analogWrite(powerRightPin,200);
        delay(10 * angle);
    } else {
        digitalWrite(directionLeftPin, HIGH);
        digitalWrite(directionRightPin, LOW);
        analogWrite(powerLeftPin, 200);
        analogWrite(powerRightPin,200);
        delay(10 * (-angle));
    }
    analogWrite(powerLeftPin, 0);
    analogWrite(powerRightPin,0);
}

/**
 * Move forward by distance
 */
void moveFwd(const float distance) {
    digitalWrite(directionLeftPin, HIGH);
    digitalWrite(directionRightPin, HIGH);
    analogWrite(powerLeftPin, 200);
    analogWrite(powerRightPin,200);
    delay(50 * distance);
    analogWrite(powerLeftPin, 0);
    analogWrite(powerRightPin,0);
}

/**
 * Return the angles the rover should turn based on the distance readings
 */
void determineDirectionAndMove() {
    myservo.write(90);
    delay(1000);
    float distanceFwd = readDistance();
    myservo.write(45);
    delay(1000);
    float distanceFwdLeft = readDistance();
    myservo.write(135);
    delay(1000);
    float distanceFwdRight = readDistance();
    if (distanceFwd > 20.0 && distanceFwdLeft > 20.0 && distanceFwdRight > 20.0) {
       moveFwd(5.0);
    } else if (distanceFwdLeft > 40.0) {
        turn(-45.0);
    } else if (distanceFwdRight > 40.0) {
        turn(45.0);
    } else {
        turn(180.0);
    }
}

void loop() {
    determineDirectionAndMove();
}
