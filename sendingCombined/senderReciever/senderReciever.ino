#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//constants
RF24 radio(9, 8); // CE, CSN
const byte address[6] = "00001";
const int buttonPin = 4;

//variables
bool isListening = false;
bool isSending = true;
int buttonState = 0;
void setup() {
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) { 
    switchRadio();
  }
}

void sendOrRecieve() {
  while(isListening) {
      listenForMesage();
  }
  while(isSending) {
      sendMessage();
  }

}

void switchRadio() {
  if(isListening)
  {
    radio.stopListening();
    isSending = true;
    isListening = false;
  }
  if(isSending)
  {
    radio.startListening();
    isListening = true;
    isSending = false;
  }
  
}

void listenForMesage() {
    if (radio.available()) {
      char text[32] = {0};
      radio.read(&text, sizeof(text));
      Serial.println(text);
}
}

void sendMessage() {
   const char text[] = "mail";
   radio.write(&text, sizeof(text));
   delay(1000);
}
