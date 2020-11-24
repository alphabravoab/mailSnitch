#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); //A6 Tx & Rx is connected to Arduino #3 & #2
int rate = 9600;
void setup() {
    Serial.begin(rate);
    mySerial.begin(rate);

    Serial.println("Initializing..."); 
    delay(1000);

    mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
    updateSerial();
        mySerial.println("AT+CPIN=0000");
    delay(1000);
//    mySerial.write(26);
    mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
    updateSerial();
    mySerial.println("AT+CTZR?");
    updateSerial();
    mySerial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
    updateSerial();
}

void loop() {
   updateSerial();

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
