#include "FastLED.h"
#include <SoftwareSerial.h>

//Use Software Serial to Read from Cortex
SoftwareSerial mySerial(10, 11); // RX, TX

// How many leds are in the strip?
#define NUM_LEDS 10

// Data pin that led data will be written out over
#define DATA_PIN 7

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

//Store Current Count
int count = 0;

int incomingByte = 0;   // for incoming serial data

// This function sets up the leds and tells the controller about them
void setup() {
      mySerial.begin(9600);
	    // sanity check delay - allows reprogramming if accidently blowing power w/leds
      delay(2000);
      FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void updateLEDs() {
   for(int i = 0; i < NUM_LEDS; i = i + 1) {
    if(i<count){
      leds[i].setRGB( 255, 255, 0);
    } else {
      leds[i].setRGB( 0, 0, 0);
    }
   }
   delay(100);
   FastLED.show();
}

void loop(){
        if (mySerial.available() > 0) {
                // Read the incoming byte:
                incomingByte = mySerial.read();

                //Serial.print("I received: ");
                //Serial.println(incomingByte-97, DEC);

                //Set Count to What is Recieved
                count = incomingByte-97;
        }
        //Update LEDs
        updateLEDs();
}


