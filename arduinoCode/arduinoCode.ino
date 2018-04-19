#include "FastLED.h"
#include <SoftwareSerial.h>

//Use Software Serial to Read from Cortex
SoftwareSerial mySerial(11, 12); // RX, TX

// How many leds are in the strip?
#define NUM_LEDS 26

// Data pin that led data will be written out over
#define DATA1_PIN 3
#define DATA2_PIN 6

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
      
      pinMode(2, OUTPUT);
      pinMode(4, OUTPUT);
      pinMode(5, OUTPUT);
      pinMode(7, OUTPUT);
      
      digitalWrite(2, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(7, LOW);
      
      FastLED.addLeds<WS2812B, DATA1_PIN, RGB>(leds, NUM_LEDS);
      FastLED.addLeds<WS2812B, DATA2_PIN, RGB>(leds, NUM_LEDS);
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


