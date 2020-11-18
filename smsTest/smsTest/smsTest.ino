int trigPin = 11;
int echoPin = 12;
int mailFlap=20;
long duration, cm;

void setup() {
    Serial.begin(9600);
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin, INPUT);  

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
  Serial.println("send a message");
}
