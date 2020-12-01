 
int trigPin = 11;
int echoPin = 12;
int buttonPin = 4;
int buttonState = 0;
int ledPin = 13;
long duration, cm;
bool youveGotMail = false;
int mailFlap=20;
int prevState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin, INPUT);  
  pinMode(buttonPin,INPUT);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  setEcho();
  checkMail();
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  if(buttonState == HIGH) {
    youveGotMail = false;
  }
  if(youveGotMail == true){
    digitalWrite(ledPin , HIGH);
  }
  if(youveGotMail == false){
    digitalWrite(ledPin , LOW);
  }

  if (buttonState == 0 && prevState!=buttonState){
    Serial.println("button is pressed");
    youveGotMail = false;
  }
  delay(250);
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
      youveGotMail=true;
   } else{ 
    
  }
}
