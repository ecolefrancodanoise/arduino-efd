/* symax_rover.ino -- An arduino sketch to test the protocol symax
 *
 */

#include <SPI.h>
#include <symax_protocol.h>

Servo myservo;  // create servo object to control a servo

nrf24l01p wireless; 
symaxProtocol protocol;
const int directionLeftPin1 = 3;
const int directionLeftPin2 = 4;
const int directionRightPin1 = 6;
const int directionRightPin2 = 7;
const int powerLeftPin = 2;
const int powerRightPin =5;

const int csPin = 8;
const int cePin = 9;
const int rf24VCC = 10;

unsigned long time = 0;

void setup() {

  Serial.begin(115200);

  // SS pin must be set as output to set SPI to master !
  pinMode(SS, OUTPUT); //delete?

  wireless.setPins(8,9);
  digitalWrite(rf24VCC, HIGH);
  
  // Set power (PWRLOW,PWRMEDIUM,PWRHIGH,PWRMAX)
  wireless.setPwr(PWRLOW);
  
  protocol.init(&wireless);
  
  time = micros();
  Serial.println("Start");

  //Motor pins
  pinMode(directionLeftPin1, OUTPUT);
  pinMode(directionLeftPin2, OUTPUT);
  pinMode(directionRightPin1, OUTPUT);
  pinMode(directionRightPin2, OUTPUT);
  pinMode(powerLeftPin, OUTPUT);
  pinMode(powerRightPin, OUTPUT);
 
}

/*
 * Function reading throttle and roll (left stick up/down, right stick left/right)
 * to control the rover wheels
 */
void activateMotors(const int throttle, const int roll) {
//  const int leftWheel = throttle - 127 + roll;
//  const int rightWheel = throttle  - 127 - roll;
const int leftWheel = (throttle - 127) * 2;
const int rightWheel = (throttle - 127) * 2;
  Serial.println(leftWheel);
  Serial.println(rightWheel);
  digitalWrite(directionLeftPin1, leftWheel > 0? HIGH : LOW);
  digitalWrite(directionLeftPin2, leftWheel > 0? LOW : HIGH);
  digitalWrite(directionRightPin1, rightWheel > 0? HIGH : LOW);
  digitalWrite(directionRightPin2, rightWheel > 0? LOW : HIGH);
  Serial.println(abs(leftWheel));
  Serial.println(abs(rightWheel));
  analogWrite(powerLeftPin, abs(leftWheel));
  analogWrite(powerRightPin,abs(rightWheel));
}

void testMotors() {
  digitalWrite(directionLeftPin1, LOW);
  digitalWrite(directionLeftPin2, HIGH);
  digitalWrite(directionRightPin1, LOW);
  digitalWrite(directionRightPin2, HIGH);
  analogWrite(powerLeftPin,0);
  analogWrite(powerRightPin,150);

}

rx_values_t rxValues;
unsigned long newTime;

void loop() 
{
  time = micros();
  uint8_t value = protocol.run(&rxValues); 
  newTime = micros();
  activateMotors(128, 0);

  switch( value )
  {
    case  NOT_BOUND:
        Serial.println("Not bound");
    break;

    case  BIND_IN_PROGRESS:
        Serial.println("Bind in progress");
    break;
    
    case BOUND_NEW_VALUES:
      Serial.print(newTime - time);
      Serial.print(" :\t");Serial.print(rxValues.throttle);
      Serial.print("\t"); Serial.print(rxValues.yaw);
      Serial.print("\t"); Serial.print(rxValues.pitch);
      Serial.print("\t"); Serial.print(rxValues.roll);
      Serial.print("\t"); Serial.print(rxValues.trim_yaw);
      Serial.print("\t"); Serial.print(rxValues.trim_pitch);
      Serial.print("\t"); Serial.print(rxValues.trim_roll);
      Serial.print("\t"); Serial.print(rxValues.video);
      Serial.print("\t"); Serial.print(rxValues.picture);
      Serial.print("\t"); Serial.print(rxValues.highspeed);
      Serial.print("\t"); Serial.println(rxValues.flip);
      //time = newTime;
      //hm... yaw is actually roll..
//      activateMotors(rxValues.throttle, rxValues.yaw);
      
    break;

    case BOUND_NO_VALUES:
      //Serial.print(newTime - time); Serial.println(" : ----");
    break;

    default:
    break;

  }

}


