int inputPin  = 4;    // define pin for sensor echo
int outputPin = 5;    // define pin for sensor trig


void setup() {
    Serial.begin(9600);     // Define motor output pin
    pinMode(inputPin, INPUT);    // define input pin for sensor
    pinMode(outputPin, OUTPUT);  // define output pin for sensor  
}

void loop() {
    digitalWrite(outputPin, LOW);   // ultrasonic sensor transmit low level signal 2μs
    delayMicroseconds(2);
    digitalWrite(outputPin, HIGH);  // ultrasonic sensor transmit high level signal10μs, at least 10μs
    delayMicroseconds(10);
    digitalWrite(outputPin, LOW);    // keep transmitting low level signal
    float pingTime = pulseIn(inputPin, HIGH);  // read the time in between
    Serial.print("pingTime: ");
    Serial.print(pingTime);
    Serial.print("\n");
    float distance = pingTime / 58.1;
    Serial.print("distance: ");
    Serial.print(distance);
    Serial.print(" cm\n");
    delay(250);
}
