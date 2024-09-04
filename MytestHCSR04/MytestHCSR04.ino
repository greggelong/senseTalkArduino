#include <HCSR04.h>

HCSR04 hc(5, 6); //initialisation class HCSR04 (trig pin , echo pin)

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    //get distance
    float d = hc.dist();
    Serial.println(d); // return curent distance in serial
    if (d<10){
      Serial.println("WARNING!");
    }
    delay(200);                 // we suggest to use over 60ms measurement cycle, in order to prevent trigger signal to the echo signal.
}