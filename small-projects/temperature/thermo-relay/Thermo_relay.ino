#include <math.h>
 
int sensorPin = A0; // select the input pin for the potentiometer
int tempgoal = 30;
int led = 13;
int CH1 = 8;
 
double Thermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0*((1024.0/RawADC-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
   //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
   return Temp;
}
 
void setup() {
 Serial.begin(9600);
 pinMode(led, OUTPUT); 
 pinMode(CH1, OUTPUT);

}
 
void loop() {
 int readVal=analogRead(sensorPin);
 double temp =  Thermistor(readVal);
 
 if(temp <tempgoal){ 
    digitalWrite(led, HIGH); 
    digitalWrite(CH1, HIGH);
 }
 else{
    digitalWrite(led, LOW);
    digitalWrite(CH1, LOW);
 }
 
 Serial.println(temp);  // display tempature
 //Serial.println(readVal);  // display tempature
 
 delay(500);
 
}

