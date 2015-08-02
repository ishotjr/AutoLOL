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
 * 0.1 - Initial PoC to test outdoor LED visibility
 *
 * -----------------------------------------------------------------------------
 *
 */

// for LoL Shield
#include <Charliplexing.h>
#include <Myfont.h>

// string to display - note \0 termination
unsigned char message[] = "Honk if you can read this - thanks!:)\0";
int messageLength = 0;

void setup() {
  
  LedSign::Init();
  
  // this works since Arduino unsigned char size is 1 byte
  messageLength = sizeof(message);
  // no need to do this every time during loop...
}

void loop() {
  Myfont::Banner(messageLength, message);
}
