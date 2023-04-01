//================================================================================
// Example NeoPixel code for Arduino Nano using FastLED library
// Library Manager: FastLED by Daniel Garcia V3.5.0 
//                  https://github.com/FastLED/FastLED
//================================================================================
#include <FastLED.h>

#define NUM_LEDS 60             //<- Number of LEDs on strip
#define DATA_PIN_1 4            //<- Arduino Nano pin for LED strip "Data In"
#define DATA_PIN_2 5            //<- Arduino Nano pin for LED strip "Data In"
#define DATA_PIN_3 6            //<- Arduino Nano pin for LED strip "Data In"
#define DATA_PIN_4 7            //<- Arduino Nano pin for LED strip "Data In"
#define DATA_PIN_5 8            //<- Arduino Nano pin for LED strip "Data In"
#define DATA_PIN_6 9            //<- Arduino Nano pin for LED strip "Data In"
#define DATA_PIN_7 10           //<- Arduino Nano pin for LED strip "Data In"
#define DATA_PIN_8 11           //<- Arduino Nano pin for LED strip "Data In"
#define DATA_PIN_9 3           //<- Arduino Nano pin for LED strip "Data In"
#define DATA_PIN_10 12           //<- Arduino Nano pin for LED strip "Data In"
#define SWITCH_PIN  2           //<- Arduino Nano pin for switch state (INT0)
#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 0x80

enum LEDMode {LED_OFF, LED_RAMP_UP, LED_RAMP_DOWN, LED_SEQUENCE};

CRGB leds[NUM_LEDS];            //<- FastLED required array for LEDs
int CurrentBrightness = 0;      //<- The current Brightness level
LEDMode CurrentLEDMode = LED_OFF;

//___ Function protoypes __________________________________________________________
void LEDStripSequence(int brightness);
void LEDStripRampUpBrightness(int steps, unsigned long msPerStep, int startBrightness, int stopBrightness);
void LEDStripRampDownBrightness(int steps, unsigned long msPerStep, int startBrightness, int stopBrightness);
void LEDRingSequence(int brightness);
void LEDRingRampBrightness(int steps, unsigned long msPerStep, int startBrightness, int stopBrightness);

//=================================================================================
// Setup before main loop
//   - assume AdaFruit NeoPixel (WS2812 / GRB ordering )
//=================================================================================
void setup() 
{ 
  //___ Init serial monitor for debug _____________________________________________
  //Serial.begin(9600);
  //Serial.println("*I* Executing Setup");

  //___ Init random number generator _______________________________________________
  randomSeed(analogRead(0));
  
  //___ Init LEDs off ______________________________________________________________
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(leds, NUM_LEDS);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(leds, NUM_LEDS);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_3>(leds, NUM_LEDS);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_4>(leds, NUM_LEDS);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_5>(leds, NUM_LEDS);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_6>(leds, NUM_LEDS);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_7>(leds, NUM_LEDS);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_8>(leds, NUM_LEDS);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_9>(leds, NUM_LEDS);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_10>(leds, NUM_LEDS);  
  for (int idx = 0; idx < NUM_LEDS; idx++)
  {
      CHSV(HUE_GREEN, 255, 0x0);  
  }
  FastLED.show();

  //___Setup switch and init LED mode ______________________________________________
  pinMode(SWITCH_PIN, INPUT_PULLUP);  
  CurrentLEDMode == LED_OFF;
}

//=================================================================================
// Main loop 
//   - Repeat the LED sequence at the current brightness value
//=================================================================================
void loop() 
{ 

  LEDSetMode();
    
  if (CurrentLEDMode == LED_SEQUENCE)
  {
    LEDStripSequence(CurrentBrightness);  
    CurrentBrightness = MAX_BRIGHTNESS;     
  }
  else if (CurrentLEDMode == LED_RAMP_UP)
  {
    Serial.println("*I* Ramping Up");    
    LEDStripRampUpBrightness(16, 300, MIN_BRIGHTNESS, MAX_BRIGHTNESS);  
    CurrentBrightness = MAX_BRIGHTNESS;     
    CurrentLEDMode = LED_SEQUENCE;    
  }
  else if (CurrentLEDMode == LED_RAMP_DOWN)
  {
    Serial.println("*I* Ramping Down");    
    LEDStripRampDownBrightness(16, 300, MAX_BRIGHTNESS, MIN_BRIGHTNESS); 
    CurrentBrightness = MIN_BRIGHTNESS; 
    CurrentLEDMode = LED_OFF;    
  }
  else if (CurrentLEDMode == LED_OFF)
  {
        
  }
 
}



