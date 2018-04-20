#include "FastLED.h"
#include <SoftwareSerial.h>

//Use Software Serial to Read from Cortex
SoftwareSerial mySerial(10, 11); // RX, TX

// How many leds per strip
#define NUM_LEDS 23

// Data pins for led strips
#define DATA1_PIN 3
#define DATA2_PIN 6

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

//Store Current Count
int count = 0;

//Store Team Value (0 BLUE,1 RED)
int team = 0;

//Store Cone Mode
int coneMode = 0;

// for incoming serial data
int incomingByte = 0;

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
      FastLED.setBrightness(50); 
}

//Display Cone Stacking Mode on Upper Leds
void coneModeLed(){
    switch(coneMode) {
       case 0:
         leds[NUM_LEDS-1].setRGB( 0, 0, 0); 
         break;
       case 1:
         leds[NUM_LEDS-1].setRGB( 0, 100, 0); 
         break;
       case 2:
         leds[NUM_LEDS-1].setRGB( 100, 0, 0); 
         break;
       case 3:
         leds[NUM_LEDS-1].setRGB( 0, 0, 100); 
         break;
       default:
          break;
    }  
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void updateLEDs() {
   for(int i = 0; i < NUM_LEDS; i = i + 1) {
    if(i<count){
      //Set Color Based on Team
      if(team==0){
        leds[i].setRGB( 0, 0, 100);
      }
      else if(team==1){
        leds[i].setRGB( 0, 100, 0);
      }
      //Otherwise Off
    } else {
      leds[i].setRGB( 0, 0, 0);
    }
   }
   coneModeLed();
}

void loop(){
        if (mySerial.available() > 0) {
                // Read the incoming byte:
                incomingByte = mySerial.read();

                //Serial.print("I received: ");
                //Serial.println(incomingByte-97, DEC);

                //Switch Based of Letter Receieved
                switch(incomingByte) {
                  case 'u':
                    coneMode =0;
                    break;
                  case 'v':
                    coneMode =1;
                    break;
                  case 'w':
                    coneMode =2;
                    break;
                  case 'x':
                    coneMode =3;
                    break;
                  //Change to Blue Team
                  case 'y':
                    team =0;
                    break;
                  //Change to Red Team
                  case 'z':
                    team =1;
                    break;                    
                  default:
                    break;
                }
                //Set Count to What is Recieved
                if(incomingByte-'a'<16){
                    count = incomingByte-'a';
                }
                updateLEDs();            
        }
        delay(100);
        FastLED.show();
}


