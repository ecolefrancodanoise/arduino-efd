#include <SoftwareSerial.h>
#define BT_SERIAL_TX 10 //* to communicate with the Bluetooth module's TXD pin */
#define BT_SERIAL_RX 11 //* to communicate with the Bluetooth module's RXD pin */

SoftwareSerial BluetoothSerial(BT_SERIAL_TX, BT_SERIAL_RX); //* Initialise the software serial port */

int sensorPin = A0;
int sensorValue = 0;
int maxthreshold = 730;
int minthreshold = 600;
int mu = 65; // 1 morsecode unit

void setup() {
  BluetoothSerial.begin(9600); 
  delay(1000);
  Serial.begin(9600); 
  BluetoothSerial.print("Starting ...");
}

void loop() {
  Serial.print("sensor = " );  
  sensorValue = analogRead(sensorPin); 
  Serial.println(sensorValue);

  BluetoothSerial.print("Moisture: ");
  BluetoothSerial.print(sensorValue);
  BluetoothSerial.print("\n");
  
  if(sensorValue >maxthreshold){ // To much water = Blinker screaming
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(25);                      
    digitalWrite(LED_BUILTIN, LOW);  
    delay(25);
  } else if(sensorValue <minthreshold){ // To little water = Morsecode for S.O.S.
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(mu);
      digitalWrite(LED_BUILTIN, LOW);
      delay(mu);
    }
    delay(2*mu);
    for (int i = 0; i < 3; i++){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(3*mu);
      digitalWrite(LED_BUILTIN, LOW);
      delay(mu);
    }
    delay(2*mu);  
    for (int i = 0; i < 3; i++){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(mu);
      digitalWrite(LED_BUILTIN, LOW);
      delay(mu);
    }
    delay(20*mu);
    }
    else { // Right amount of water = No light
      digitalWrite(LED_BUILTIN, LOW);    
  }
  delay(1000);
}

