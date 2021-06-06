// SbSensor1.ino

#define MyPrintf printf
#define MAIN

//-----------------------------------------------------------------------------
// i2c stuff start
// A4/A5 - i2c pins SDA/SCL on Uno

// I2c registers:
const int R_GENERIC_ID  = (1 << 8) + 0;   // fixed number IDENTIFICATION (read only)
const int R_S1_WATER    = (2 << 8) + 1;   // Watersensor - ADC input, 2 bytes

const int S1_SLAVE_ADDRESS = 0x36/2;      // slave address, any number from 0x01 to 0x7F
const int IDENTIFICATION   = 0x20;        // read-only value of register 0
const int REG_MAP_SIZE     = 4;

#include "I2cSlaveRegisters.h"
// i2c stuff end
//-----------------------------------------------------------------------------

// Setup command interpreter
#include "Commands.h"
TCommand Command(Execute);

// from sensor example https://arduinogetstarted.com/tutorials/arduino-water-sensor
#define POWER_PIN  7
#define SIGNAL_PIN A0
#define SENSOR_MIN 0
#define SENSOR_MAX 521
// example end

//-----------------------------------------------------------------------------
// setup -
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void setup()
{
   Serial.begin(115200);
   fdevopen( &my_putc, 0);  // enable printf: route device 0 (stdout) output to my_putc()
   MyPrintf("Hello SbSensor1 world\n");

   I2cSlaveRegistersInit(S1_SLAVE_ADDRESS);
}

//-----------------------------------------------------------------------------
// loop -
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void loop() {

   Command.Takt(Serial);  // Console command interpreter

   // from sensor example https://arduinogetstarted.com/tutorials/arduino-water-sensor
   digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
   delay(10);                      // wait 10 milliseconds
   int value = analogRead(SIGNAL_PIN); // read the analog value from sensor
   digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

   int level = map(value, SENSOR_MIN, SENSOR_MAX, 0, 4); // 4 levels
   Serial.print("Water level: ");
   Serial.println(level);
   // example end

   RegisterSet(R_S1_WATER, level);   // store result
}

//-----------------------------------------------------------------------------
// Execute - voer commando uit
//-----------------------------------------------------------------------------
// wordt via Command.Takt() aangeroepen als een commando is ontvangen
// via de serial port.
//-----------------------------------------------------------------------------
void Execute(int Param[])
{
   if (Command.Match("?", 0))  Command.Help("SbSensor1\n");
}
