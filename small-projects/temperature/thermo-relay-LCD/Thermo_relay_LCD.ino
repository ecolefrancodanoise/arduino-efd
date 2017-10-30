#include <math.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

 
int sensorPin = A1; // select the input pin for the potentiometer
int tempgoal = 30;
int led = 13;
int CH1 = 3;
int lcd_key     = 0;
int adc_key_in  = 0;
int count = 0;
int tempdelay = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
/*
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  
*/
 // For V1.0 comment the other threshold and use the one below:

 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   



 return btnNONE;  // when all others fail, return this...
}
 
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
 {
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Temperature"); // print a simple message
}

}
 
void loop() {
  

 
 int readVal=analogRead(sensorPin);
 double temp =  Thermistor(readVal);
 
 if(temp <tempgoal){
  if(tempdelay == 50){
    digitalWrite(led, HIGH); 
    digitalWrite(CH1, HIGH);
    delay(temp*10);
    tempdelay = 0;
  }
   else {
    digitalWrite(CH1, LOW);
    tempdelay ++;
    delay (100);
   }
 }
 else{
    digitalWrite(led, LOW);
    digitalWrite(CH1, LOW);
 }
 
 delay(100);
 
 lcd.setCursor(0,1);            // move cursor to second line "1" and 9 spaces over
if (count<10){
count ++;}
if (count==10){
   lcd.print(temp,1);
   count = 0;}
   
 lcd.setCursor(7,1); 
 lcd_key = read_LCD_buttons();
 switch (lcd_key){
   case btnUP:{
          delay(200);
         tempgoal +=1;
         lcd.print("Goal:");
          lcd.setCursor(12,1);
     lcd.print(tempgoal);
     break;
     delay(200);
    }
  case btnDOWN:{
         delay(200);
    tempgoal -=1;
    lcd.print("Goal:");
          lcd.setCursor(12,1);
     lcd.print(tempgoal);
     break;
     delay(200);
  }
 
 }
}
