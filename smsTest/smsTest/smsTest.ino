#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); //A6 Tx & Rx is connected to Arduino #3 & #2
int trigPin = 11;
int echoPin = 12;
int mailFlap=20;
long duration, cm;

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin, INPUT);  
    Serial.println("Initializing..."); 
    delay(1000);
  
    mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
    updateSerial();
    mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
    updateSerial();
    mySerial.println("AT+CMGS=\"+31629093188\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial();
}

void loop() {
  setEcho();
}

void setEcho(){
 digitalWrite(trigPin,LOW);
 delayMicroseconds(5);
 digitalWrite(trigPin,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin,LOW);
 pinMode(echoPin, INPUT);
 duration=pulseIn(echoPin,HIGH);
 cm=(duration/2)/29.1;
}

void checkMail() {
   if(cm<=mailFlap){
      sendMessage();
   } else{ 
    
  }
}

void sendMessage() {
    mySerial.print("You've got mail"); //text content
    // mySerial.print("Last Minute Engineers | lastminuteengineers.com"); //text content
    updateSerial();
    mySerial.write(26);
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
