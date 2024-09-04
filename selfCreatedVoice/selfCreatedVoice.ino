/* Talkie library  Copyright 2011 Peter Knight
   Talkie is a speech synthesiser that works from a fixed vocabulary.

   Demo put together by Gadget Reboot

   Original library:  https://github.com/going-digital/Talkie/tree/master/Talkie
   Updated library:   https://github.com/ArminJo/Talkie

   Voice PWM output pins for different ATmegas:
    ATmega328 (Uno and Nano): non inverted at pin 3, inverted at pin 11.
    ATmega2560: non inverted at pin 6, inverted at pin 7.
    ATmega32U4 (Leonardo): non inverted at pin 10, inverted at pin 9.
    ATmega32U4 (CircuitPlaygound): only non inverted at pin 5.

   Connect speaker between pin 3 and pin 11

   Compiled for Uno, using Arduino IDE 1.8.10, Talkie (ArminJo) v1.0.2
   Sketch uses 8202 bytes (25%) of program storage space. Maximum is 32256 bytes.
   Global variables use 145 bytes (7%) of dynamic memory, leaving 1903 bytes for local variables. Maximum is 2048 bytes.


*/
#include <Arduino.h>

#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_US_Clock.h"
#include "Vocab_US_Acorn.h"

Talkie voice;

// custom generated samples
const uint8_t sample1[]   PROGMEM = {0xe8,0x2d,0x09,0x59,0xdd,0x9d,0x84,0xb3,0x2e,0x14,0xb3,0x88,0x13,0xd6,0xe0,0xc8,0xaa,0x22,0x4e,0xe9,0x82,0x15,0x8d,0x0c,0x3b,0x85,0x8f,0xce,0xc2,0xd4,0xe3,0x24,0x3a,0xc6,0x50,0x73,0x8b,0x93,0xd8,0x98,0x22,0x5d,0xc4,0x6c,0x51,0x63,0x4e,0x37,0x15,0x33,0xc9,0x09,0x29,0xdd,0x0d,0xcd,0xa4,0xc0,0xfb,0x30,0x77,0xb0,0x13,0x62,0xa2,0xdd,0x3b,0xc5,0x89,0xf8,0x23,0x30,0xcf,0x11,0x27,0xe2,0x6f,0x48,0xc8,0x5a,0x6d,0x31,0x60,0x09,0x21,0x01,0x4c,0xa9,0xec,0x62,0xe5,0x3b,0x8c,0xa5,0x62,0x88,0x55,0x2b,0x33,0xd3,0x50,0x2e,0xd3,0xb9,0xcd,0x4c,0x4a,0xb9,0xdc,0xa4,0x71,0x37,0x2a,0x65,0x72,0x53,0x3b,0x52,0xb8,0xb4,0x2a,0xe4,0xe8,0x30,0xe4,0x3a,0xac,0x62,0x7d,0xc2,0x10,0xeb,0xa2,0x1a,0xbe,0x54,0x22,0x4d,0x8c,0x1a,0xb0,0x5b,0xd1,0xd9,0x0a,0x6a,0xc1,0x6e,0x45,0x63,0x3b,0xa8,0x05,0x6b,0x0c,0x8d,0xed,0xa2,0x16,0xcc,0x0d,0x72,0xb6,0x83,0x7a,0xb0,0x3a,0xd4,0x38,0x36,0x00,0x00,0x00,0x00,0x00,0xfa,0x44,0xcc,0x52,0x92,0xc8,0x86,0x53,0x3b,0x92,0xc5,0xec,0x14,0xd6,0xb5,0xa8,0x4a,0x93,0xdc,0x58,0x5f,0xa2,0x7b,0xdc,0x4a,0xe1,0x6c,0xf1,0xca,0x64,0x3a,0x8e,0x87,0x27,0x53,0x47,0xdc,0x38,0x01,0x3e,0x8f,0x48,0x4f,0x92,0x44,0x3a,0x2c,0x23,0xcc,0x4a,0x32,0xc4,0xf0,0xc8,0x70,0x33,0xce,0x25,0x37,0xdd,0xd3,0x42,0x39,0x0f,0xdf,0x30,0x0b,0x0b,0x95,0x02,0xd6,0xca,0x4d,0x2d,0x74,0x8a,0x44,0xf3,0x10,0x71,0x31,0x29,0x92,0xcd,0x83,0xd5,0xc4,0xa4,0x58,0xf4,0x70,0x12,0x0d,0x1d,0x62,0xb1,0x5d,0x55,0x55,0x8c,0x8b,0xd9,0x51,0x33,0x75,0xa9,0x2a,0x02,0x5f,0x4d,0x5d,0x6d,0xab,0x88,0xf1,0x6d,0x2b,0xb1,0x64,0xa2,0x0c,0x2c,0xb5,0xd5,0xa6,0x88,0x8c,0xd8,0x16,0x05,0x4b,0x04,0xa2,0xae,0x53,0x00,0xa2,0x90,0x93,0xb8,0x68,0x02,0xb6,0x62,0x04,0x67,0xa7,0x43,0x29,0x54,0x11,0x6c,0x8f,0xea,0x0e,0x29,0x45,0x30,0xdd,0xab,0x2a,0xcc,0x24,0x59,0x0d,0xcf,0x08,0x33,0x13,0x54,0x34,0xd3,0x35,0x35,0xb6,0xb2,0xf0,0x6c,0xc7,0x12,0x2b,0x2a,0xa0,0x62,0xcb,0x9d,0x63,0x1b,0x3f,0x43,0x71,0x2f,0x4e,0x14,0x4c,0x92,0x27,0xc5,0x34,0x52,0xd0,0xd9,0xcc,0x50,0x37,0x9b,0xca,0xa0,0xdb,0xda,0x95,0x6c,0x33,0x13,0x0f,0x99,0x14,0x91,0x2d,0x54,0x72,0xa5,0x4d,0x45,0x8d,0xe1,0xe9,0xd1,0x52,0x63,0xb7,0x89,0x96,0xc5,0xdb,0x4c,0xed,0x17,0xd2,0xa7,0xac,0x54,0x4a,0xd2,0xa8,0x90,0xb3,0xc6,0xd9,0x4a,0x61,0x7d,0xcd,0xee,0x32,0x29,0x41,0xd0,0xb9,0x47,0x59,0xad,0x06,0x45,0xb6,0x2e,0x35,0x37,0x13,0x4c,0x99,0x26,0x2d,0xb2,0x96,0x29,0x0a,0x90,0xe9,0x64,0x3a,0x0c,0xd8,0x0c,0x4d,0x00,0x5b,0x8a,0xa5,0xc0,0xab,0x4c,0x33,0x89,0x95,0x02,0x13,0x23,0xd4,0x2c,0x62,0x8a,0x74,0xf4,0x50,0x33,0x53,0x2e,0x46,0xc9,0x43,0xcd,0x23,0xa9,0x04,0xd4,0x74,0x2d,0x6d,0xac,0x12,0xd0,0xd3,0xb5,0xb4,0x91,0x8a,0x41,0x0f,0xb7,0xd2,0x46,0x26,0x02,0xd5,0xc2,0xd3,0x52,0x9b,0x10,0x74,0x0f,0x4f,0x4b,0xec,0x7c,0x52,0x3d,0x3c,0x3d,0x72,0x70,0x94,0x57,0xcf,0xf6,0xd8,0xc1,0x0d,0x8e,0xcd,0x33,0xec,0xba,0x80,0x84,0x0c,0x0f,0x8d,0x24,0x62,0x90,0xaa,0x32,0xc8,0x16,0xfa,0x81,0xc9,0xee,0x22,0x59,0xa8,0x07,0xaa,0xaa,0x52,0x24,0xa1,0xdb,0x40,0x8f,0xec,0x88,0x05,0xe8,0xe7,0xd4,0x59,0xc3,0xa2,0x98,0xb7,0x32,0x53,0x37,0xa9,0x9c,0x0c,0xa1,0xd2,0x33,0xbd,0x4e,0xd1,0xa3,0xf1,0x70,0x95,0xc8,0x41,0xb7,0x3e,0xc2,0x4d,0xcd,0x28,0x9b,0x98,0x6a,0x33,0x8d,0xc3,0x3c,0xe0,0xbb,0xdd,0xa5,0x09,0x8a,0xc0,0xac,0x54,0xb3,0xba,0x26,0x0e,0xc9,0x85,0x42,0xec,0x98,0x30,0x44,0x67,0x4a,0x75,0x62,0x3c,0x51,0xc2,0xa4,0x3c,0x56,0x30,0x5d,0x09,0x77,0xb7,0x58,0x85,0xf5,0x25,0x6a,0x52,0x63,0x17,0x3a,0x05,0x8d,0x75,0xae,0x95,0x28,0xdf,0x52,0xda,0xc5,0x54,0xa1,0x7c,0x6d,0xa9,0x94,0xd0,0x85,0xf1,0xad,0xb4,0xc2,0x22,0x27,0xc5,0x4c,0xcf,0xf2,0x88,0x92,0x4c,0x35,0x2d,0xcb,0xcd,0x6a,0x71,0x4d,0xf7,0xaa,0x74,0xb1,0x29,0x54,0x79,0xdc,0x93,0xa2,0x84,0x98,0xf5,0x36,0x0d,0x89,0x69,0x52,0x38,0xcb,0xc4,0x25,0x14,0xc9,0x41,0xbf,0x60,0x25,0x3b,0xaa,0xb6,0xc0,0x3a,0xca,0x6c,0x99,0x5a,0x83,0x98,0x48,0xb3,0xe5,0x72,0x62,0x6e,0x58,0x39,0x61,0x48,0xe9,0x58,0x63,0x37,0xcb,0x21,0xa1,0xab,0x4d,0xcc,0x6d,0x87,0x94,0xec,0x32,0x35,0xb7,0xed,0x52,0x7c,0x5a,0xc5,0xdd,0xb6,0x49,0xd0,0x6d,0x96,0x70,0xc9,0x26,0x42,0xa7,0x95,0x3d,0xa4,0x18,0x1f,0xcf,0x6d,0x22,0x33,0xab,0x1c,0xb6,0x6e,0x19,0x30,0x8e,0x72,0xd8,0xbc,0x15,0xc0,0x38,0xc2,0x65,0x75,0x97,0x51,0xe2,0xa0,0x98,0xbf,0x69,0x24,0xb5,0x02,0x00,0x4c,0x12,0x33,0x53,0xcd,0xc4,0x24,0x49,0x4f,0xeb,0xea,0x30,0x53,0x14,0xd3,0xad,0xb3,0x32,0x74,0xd1,0xd5,0xb0,0xec,0x8c,0xc8,0x49,0x17,0x2b,0x3c,0xdb,0xad,0x24,0x43,0x2c,0x8f,0x2a,0xb7,0x12,0x74,0x76,0x3c,0x3c,0x55,0x92,0x53,0xd0,0x09,0xd7,0x14,0x39,0x46,0x02,0xb7,0x42,0xcb,0xe4,0x1a,0x11,0xdc,0x09,0x4a,0x73,0x6a,0x04,0xf8,0x26,0x28,0xcd,0xa9,0xe2,0xe1,0xdb,0xc0,0xf2,0x64,0x8a,0x83,0x6f,0x83,0x33,0xec,0x2a,0x0e,0xfe,0x71,0x4d,0xb7,0x2b,0x38,0xf8,0xcb,0x25,0x5d,0x1d,0xe3,0xe0,0xdb,0x62,0x2f,0xeb,0x44,0x04,0x6f,0x5d,0x33,0xa3,0x22,0x11,0xbc,0x0c,0xad,0x70,0x0c,0x20,0xe6,0xe8,0xcc,0xa3,0x3c,0xb2,0x61,0x4d,0x50,0xaf,0xf4,0x38,0x85,0x96,0x45,0x2b,0x32,0xd3,0x0e,0x32,0x24,0x0f,0x2f,0x93,0xdd,0x88,0x50,0xab,0xa3,0xcd,0x66,0x21,0x43,0xb7,0x8c,0x56,0x49,0x85,0x0a,0x43,0xb3,0x4a,0x2d,0x17,0x36,0x54,0x8b,0x2a,0xb6,0x9b,0x14,0xbd,0xc2,0xcc,0xa5,0x49,0x30,0xc4,0x8c,0x08,0xa7,0x34,0xc2,0x83,0xc7,0xca,0x98,0x12,0x93,0x18,0x3c,0x8d,0x72,0xb6,0xcd,0x6e,0xde,0x69,0xca,0xd5,0x8e,0x4a,0xd9,0xd2,0x8c,0x30,0x33,0x29,0x36,0xc3,0x32,0xc2,0x24,0xa7,0xc4,0x75,0xeb,0x08,0x95,0x1d,0x12,0xd7,0xac,0x3d,0x58,0x8e,0xc9,0x6c,0x8a,0x14,0x27,0xb5,0x2a,0x57,0x59,0x53,0x09,0xd3,0x88,0x42,0x25,0x4d,0x41,0x4c,0x22,0x6a,0x13,0x34,0x94,0xa0,0x09,0xab,0x4d,0x52,0x57,0x82,0xa4,0xac,0x36,0xd1,0xdc,0x08,0xea,0xb2,0xd6,0xeb,0xd0,0x08,0xb0,0x42,0xa6,0x80,0x4c,0xa5,0x24,0x0a,0xda,0x1c,0x36,0x56,0x37,0x3b,0xe8,0x0f,0x58,0x59,0x4d,0x63,0xa3,0x26,0x60,0x15,0x35,0xb5,0x83,0x9a,0x84,0x95,0xc5,0xd8,0x0e,0xfa,0x33,0x36,0x12,0x13,0x31};
void setup() {

}

void loop() {


// VM61002/3/4/5 ROMs, male US voice
  voice.say(sp2_DANGER);
  voice.say(sp2_DANGER);
  voice.say(sp2_RED);
  voice.say(sp2_ALERT);
  delay(500);


  // custom created samples
  voice.say(sample1);
  delay(500);
  //

  voice.say(sp5_INSTRUMENTS);
  voice.say(sp5_BREAKING);
  voice.say(sp5_DOWN);
  delay(500);
  //

   

}