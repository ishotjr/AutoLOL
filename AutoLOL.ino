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

// ATmega328 has 512b EEPROM, but 50 chars is plenty (+1 for \0)
#define BUFFER_SIZE 51

// TODO: toggle println via #DEBUG - or...serial?

// string to display - note that string literal *includes* \0 termination
unsigned char message[BUFFER_SIZE] = "Honk if you can read this - thanks!:)";
byte messageLength = 37;
unsigned char newMessage[BUFFER_SIZE] = "";
byte newMessageLength = 0;
boolean newlineReceived = false;

void setup() {
  
  // initialize LoL Shield
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
    memcpy(message, newMessage, BUFFER_SIZE);

    messageLength = newMessageLength;
    
    Serial.println("message updated");//String(newMessage)); 
    
    // reset for the next update
    newMessage[0] = '\0';
    newlineReceived = false;
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
  // TODO: do we have to worry about overflowing the buffer here?
  // *seems to be limited to 64 characters anyway based on experimentation?*
  byte inputLength = 0;
  
  Serial.println("serialEvent()");

  while (Serial.available()) {
    
    char readChar = Serial.read();
    inputLength++;
    Serial.println(inputLength);
    
    Serial.println("read:");
    Serial.println(readChar);

    unsigned char newChar = (unsigned char)readChar;//Serial.read();
    
    // just ignore anything over BUFFER_SIZE for now
    if (inputLength < BUFFER_SIZE) {
      
      // - 1 since 0-index
      newMessage[inputLength - 1] = newChar;

      // terminate the string on newline
      if (newChar == '\n') {
        
        Serial.println("newline received");
  
        // replace \n with \0
        newMessage[inputLength - 1] = '\0';
        newlineReceived = true;
        
        // we don't coun't the \0, so:
        newMessageLength = inputLength - 1;      

      }
    
    } else if (inputLength == BUFFER_SIZE) {
      
      Serial.println("buffer full");
      
      // we're out of space, so pretend it was a newline regardless
      newMessage[inputLength - 1] = '\0';
      newlineReceived = true;
      
      // new message length is as long as it can be!
      newMessageLength = BUFFER_SIZE - 1;      
    } else {
      Serial.println("ignore since > BUFFER_SIZE"); 
    }
    
  }  
}
