int directionLeftPin = 12;
int directionRightPin = 13;
int powerLeftPin = 3;
int powerRightPin = 11;

void setup() {
    pinMode(directionLeftPin, OUTPUT);
    pinMode(directionRightPin, OUTPUT);
    pinMode(powerLeftPin, OUTPUT);
    pinMode(powerRightPin, OUTPUT);
}

void loop() {
    digitalWrite(directionLeftPin, LOW);
    digitalWrite(directionRightPin, LOW);
    analogWrite(powerLeftPin, 0);
    analogWrite(powerRightPin,0);
    delay(250);

    digitalWrite(directionLeftPin, HIGH);
    digitalWrite(directionRightPin, LOW);
    analogWrite(powerLeftPin, 255);
    analogWrite(powerRightPin, 255);
    delay(250);

    digitalWrite(directionLeftPin, LOW);
    digitalWrite(directionRightPin, HIGH);
    analogWrite(powerLeftPin, 255);
    analogWrite(powerRightPin, 255);
    delay(250);
}
