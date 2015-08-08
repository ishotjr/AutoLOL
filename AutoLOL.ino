/*
 * -----------------------------------------------------------------------------
 *
 * AutoLOL - An attempt to reduce road rage and increase *Auto*motive courtesy 
 * using *L*ots *O*f *L*EDs! :D
 *
 * -----------------------------------------------------------------------------
 *
 * Requires https://github.com/jprodgers/LoLshield by @jprodgers
 *
 * -----------------------------------------------------------------------------
 *
 * 0.2 - Add ability to set message via serial (non-persistent)
 *
 * -----------------------------------------------------------------------------
 *
 */

// for LoL Shield
#include <Charliplexing.h>
#include <Myfont.h>

// string to display - note \0 termination
// TODO #define/const array size?
unsigned char message[40] = "Honk if you can read this - thanks!:)\0";
int messageLength = 38;
unsigned char newMessage[40] = "\0";
byte newMessageLength = 0;
boolean newlineReceived = false;

void setup() {
  
  LedSign::Init();
  
  // initialize serial
  Serial.begin(9600);
  
  Serial.println("setup complete");
}

void loop() {

  Serial.println("begin loop");

  Serial.println(newlineReceived);
  
  // update message on newline receipt
  if (newlineReceived) {

    //strncpy
    memcpy(message, newMessage, 40);
    
    Serial.println("message updated");//String(newMessage)); 
    
    newMessage[0] = '\0';
    newlineReceived = false;
    
    messageLength = newMessageLength;

    newMessageLength = 0;
  }

  // this works since Arduino unsigned char size is 1 byte
  //messageLength = sizeof(message);

  Serial.println(messageLength);
  
  // message must be unsigned char*
  Myfont::Banner(messageLength, message);

  //Serial.println(newlineReceived);

  Serial.println("end loop");

}

void serialEvent() {
  
  Serial.println("serialEvent()");

  while (Serial.available()) {
    
    char readChar = Serial.read();
    
    Serial.println("read:");
    Serial.println(readChar);

    unsigned char newChar = (unsigned char)readChar;//Serial.read();
    
    // TODO: prevent > 40
    
    newMessageLength++;
    newMessage[newMessageLength] = newChar;
    
    if (newChar == '\n') {
      
      Serial.println("newline received");

      // replace \n with \0
      newMessage[newMessageLength] = '\0';
      newlineReceived = true;
    }
    
    
  }  
}
