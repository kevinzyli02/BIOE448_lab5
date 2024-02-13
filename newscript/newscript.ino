#include <ArduinoBLE.h>
BLEService newService("180A"); // creating the service
BLEByteCharacteristic readChar("shreyaJ", BLERead);
BLEByteCharacteristic writeChar("Tkutch", BLEWrite);
const int trigPin = 8;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;
BLEService uuid("1111111111111111");
void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);


 // unsigned long startTime = millis();
  // while (!Serial && millis() - startTime < 1000);
    if (!BLE.begin()){
    Serial.println("Waiting for ArduinoBLE");
    while(1);
    }
 
  BLE.setDeviceName("hahahahahaahahahahaha");
  BLE.setAdvertisedService(uuid);
  BLE.setLocalName("hhehehehehehehe");
  BLE.setAdvertisedService(newService);
  newService.addCharacteristic(readChar);
  newService.addCharacteristic(writeChar);
  BLE.addService(newService);


  BLE.advertise();
  Serial.println("Bluetooth device active");
}

void loop() {
  // put your main code here, to run repeatedly:


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distanceCm = duration * 1/58;
  distanceInch = duration * 1/148;
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.print(" cm/");
  Serial.print(distanceInch);
  Serial.println(" in");
  delay(1000);


  if (distanceCm <10) {
    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    Serial.print("Distance is less than 10cm");
    }
  else {
    digitalWrite(3, LOW);
    digitalWrite(5, HIGH);  
    Serial.print("Distance is more than 10cm");
    }
  
  
  readChar.writeValue(distanceCm);
  
}



