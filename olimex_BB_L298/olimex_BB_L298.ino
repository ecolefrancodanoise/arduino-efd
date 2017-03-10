/* 
 * Program to test the L298-based motor shield from Olimex
 *
 * Pins on the BB L298
 *  1: VCC
 *  2: ENABLE A
 *  3: IN 1
 *  4: In 2
 *  5: ENABLE B
 *  6: IN 3
 *  7: IN 4
 *  8: GND
 *
 */

const int ENABLE_A = 2;
const int IN_1 = 3;
const int IN_2 = 4;
const int ENABLE_B = 5;
const int IN_3 = 6;
const int IN_4 = 7;

void setup() {
    pinMode(ENABLE_A, OUTPUT);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(ENABLE_B, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);  

    //PWM on the enable pins
    analogWrite(ENABLE_A, 200);
    analogWrite(ENABLE_B, 200);
}

void loop() {
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
}
