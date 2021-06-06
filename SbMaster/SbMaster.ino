// SbMaster.ino -

#define MyPrintf printf
#define MAIN

int my_putc(char c, FILE __attribute__ ((unused)) *t) {
  if (c == '\n') Serial.write('\r');
  return Serial.write(c);
}

//-----------------------------------------------------------------------------
// Toolkit & commands setup.
#include <Wire.h>
#include "I2CmTk.h"

//-----------------------------------------------------------------------------
// setup -
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void setup() {
   Serial.begin(115200);      // start serial

   fdevopen( &my_putc, 0);  // enable printf: route device 0 (stdout) output to my_putc()
   MyPrintf("Hello SbMaster world\n");

   Wire.begin();              // start I2C
}

//-----------------------------------------------------------------------------
// loop -
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void loop()
{
   // 1 second delay
   delay(1000);

   // copied (for now) from slave definion...
   const int R_S1_WATER    = (2 << 8) + 1;   // Watersensor - ADC input, 2 bytes
   const int S1_SLAVE_ADDRESS = 0x36/2;      // slave address, any number from 0x01 to 0x7F

   int Value = I2cRead(S1_SLAVE_ADDRESS, R_S1_WATER);
   MyPrintf("Waarde: %d\n", Value);
}
