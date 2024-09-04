#include <Arduino.h>
#include "Talkie.h"
#include "Vocab_US_Large.h"

// Initialize Talkie
Talkie voice;

// Define an array of pointers to the sound data
const uint8_t* const commandData[] PROGMEM = {
    sp4_AFFIRMATIVE, sp4_NEGATIVE, sp4_MAYDAY, sp4_WARNING, sp4_ICING,
    sp4_DANGER, sp4_EMERGENCY, sp4_ROGER, sp4_HERTZ, sp4_SECURITY,
    sp4_TARGET, sp4_TARGET_1, sp4_VECTORS, sp4_LIGHT, sp4_FRONT,
    sp4_WAY, sp4_GLIDE, sp4_OPEN, sp4_OPEN_1, sp4_LIGHTS,
    sp4_ON, sp4_GUNDISH, sp4_R_NAV, sp4_SELECT, sp4_FILED,
    sp4_MIG, sp4_ALERT, sp4_ZONE, sp4_TERMINAL, sp4_RADIOS,
    sp4_SPEED, sp4_KNOTS, sp4_EXPECT, sp4_ACTION, sp4_RADIAL,
    sp4_POWER, sp4_GAS, sp4_INFORMATION, sp4_TRUE, sp4_PRESSURE,
    sp4_CHECK, sp4_CHECK_1, sp4_DECREASE, sp4_ADVISE, sp4_YOU,
    sp4_HAVE, sp4_ERROR2, sp4_ALL, sp4_LONG, sp4_LONG_1,
    sp4_NO, sp4_IMMEDIATELY, sp4_FINAL, sp4_PLEASE, sp4_START,
    sp4_COURSE, sp4_RADAR, sp4_PLAN, sp4_WINDOWS, sp4_WATCH,
    sp4_USE, sp4_TURN, sp4_TRAFFIC, sp4_SLOW, sp4_SLOW_1,
    sp4_RELEASE, sp4_KEY, sp4_IGNITION, sp4_DEGREE, sp4_RAIN,
    sp4_REPAIR, sp4_CANCEL, sp4_VERIFY, sp4_READY, sp4_USE2,
    sp4_OUT, sp4_OTHER, sp4_OIL, sp4_OFF, sp4_NEAR,
    sp4_GREAT, sp4_MIXTURE, sp4_MUCH, sp4_GREAT2, sp4_IS,
    sp4_CAUTION, sp4_BELOW, sp4_CYLINDER, sp4_CONTACT, sp4_AND,
    sp4_FUEL, sp4_FOR, sp4_SEQUENCE, sp4_SIDE, sp4_TO,
    sp4_RICH, sp4_PUMPS, sp4_LEVEL, sp4_LEVEL_1, sp4_LOWER,
    sp4_REAR, sp4_HOLD, sp4_LEFT, sp4_RIGHT, sp4_STRAY,
    sp4_CLOSE, sp4_EVACUATE, sp4_FAILURE, sp4_SERVICE, sp4_ABORT,
    sp4_IDEMTIFY, sp4_TOO_LOW, sp4_CENTRE, sp4_AREA, sp4_BASE,
    sp4_CONTROL, sp4_MEASURED, sp4_D, sp4_THE, sp4_VACUUM,
    sp4_ABEAN
};

// Function to get a random command index
int getRandomCommandIndex() {
    int numElements = sizeof(commandData) / sizeof(commandData[0]); // Calculate number of elements
    return random(numElements); // Get random index
}

void setup() {
    Serial.begin(9600);
    while (!Serial) { // Wait for Serial Monitor to open
        ; 
    }
    Serial.println("Serial Monitor is open.");
     // Seed the random number generator
    randomSeed(analogRead(A0));
}

void loop() {
    int index = getRandomCommandIndex(); // Get random command index
    Serial.print("Random index: ");
    Serial.println(index); // Print the random index for debugging

    // Get the command data from program memory
    const uint8_t* command = (const uint8_t*)pgm_read_word(&(commandData[index]));

    // Play the sound using Talkie
    voice.say(command);

    delay(3000); // Delay for demonstration
}


