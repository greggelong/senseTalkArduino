#include <HCSR04.h>

#include <Arduino.h>

#include "TalkieUtils.h"
#include "Vocab_US_Large.h" // for timeout
#include "Vocab_Special.h"

Talkie Voice;

HCSR04 hc(5, 6); //initialisation class HCSR04 (trig pin , echo pin)

void setup()
{
    Serial.begin(9600);
}

void loop() {
    Voice.say(sp4_WARNING);
    delay(500);
    Voice.say(sp4_INFORMATION);
    Voice.say(sp2_IS);
    Voice.say(sp2_POWER);
    delay(500);


    int tCentimeter = hc.dist();
    float d = hc.dist();
    delay(60);
    // print distance
    if (tCentimeter >= 300) {
        Serial.println("timeout");

        sayQTimeout(&Voice);
        Voice.sayQ(sp2_OUT);
    } else {
        Serial.print("cm=");
        Serial.println(tCentimeter);

        float tDistanceMeter = tCentimeter / 100.0;
        sayQFloat(&Voice, tDistanceMeter, 2, true, true);
        Voice.sayQ(sp2_METER);
    }

// Using .say() here is another way to block the sketch here and wait for end of speech as you can easily see in the source code of say().
    Voice.sayQ(spPAUSE1);
    while (Voice.isTalking()) {
        ;
    }

}