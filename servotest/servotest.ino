#include <Servo.h>

int servoPin = 9;
Servo myservo;

void setup() {
    Serial.begin(9600);
    myservo.attach(servoPin);
}

void loop() {
    myservo.write(90);
    delay(1000);
    myservo.write(45);
    delay(1000);
    myservo.write(135);
    delay(1000);
}
