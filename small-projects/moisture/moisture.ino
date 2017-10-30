int sensorPin = A0;
int sensorValue = 0;
int maxthreshold = 730;
int minthreshold = 600;
int mu = 65; // 1 morsecode unit

void setup() {

  Serial.begin(9600); //  (Saving for datalogging)
}
void loop() {
              
  Serial.print("sensor = " );  //  (Saving for datalogging)
  sensorValue = analogRead(sensorPin); 
  Serial.println(sensorValue); // (Saving for datalogging)

  if(sensorValue >maxthreshold){
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(25);                      
    digitalWrite(LED_BUILTIN, LOW);  
    delay(25);
  } else if(sensorValue <minthreshold){
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
    else {
      digitalWrite(LED_BUILTIN, LOW);    
  }
}
