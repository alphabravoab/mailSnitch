#include <GSM.h>

GSM gsmAccess; 
#define PINNUMBER ""
GSM_SMS sms;
char senderNumber[20];

void setup()
{
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("SMS Messages Receiver");
    bool notConnected = true;
    while (notConnected) {
      Serial.println("entering pin");
      if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
        
        notConnected = false;
        
      } else {
  
        Serial.println("Not connected");
  
        delay(1000);
  
      }
    }
    Serial.println("GSM initialized");

    Serial.println("Waiting for messages");
}

void loop()
{
char c;

  // If there are any SMSs available()

  if (sms.available()) {

    Serial.println("Message received from:");

    // Get remote number

    sms.remoteNumber(senderNumber, 20);

    Serial.println(senderNumber);

    // An example of message disposal

    // Any messages starting with # should be discarded

    if (sms.peek() == '#') {

      Serial.println("Discarded SMS");

      sms.flush();

    }

    // Read message bytes and print them

    while (c = sms.read()) {

      Serial.print(c);

    }

    Serial.println("\nEND OF MESSAGE");

    // Delete message from modem memory

    sms.flush();

    Serial.println("MESSAGE DELETED");

  }

  delay(1000);

}
