
//=================================================================================
// Determine the state of the pin and set the LED operating mode
//=================================================================================
void LEDSetMode()
{
  //___ Get current switch state __________________________________________________  
  int switchState = digitalRead(SWITCH_PIN);
  
  if ((switchState == HIGH) && (CurrentLEDMode == LED_SEQUENCE))
  {
    CurrentLEDMode = LED_RAMP_DOWN;
  }
  else if ((switchState == LOW) && (CurrentLEDMode != LED_SEQUENCE))
  {
    CurrentLEDMode = LED_RAMP_UP;
  }
  
}

//=================================================================================
// Operating sequence for LED Strip (random brightness variation of green)
//=================================================================================
void LEDStripSequence(int brightness)
{
  int targetLED = random(0, 30);
  int rndBrightness = random(MIN_BRIGHTNESS, brightness);

  leds[targetLED] = CHSV(HUE_GREEN, 255, rndBrightness);
  leds[targetLED+30] = CHSV(HUE_GREEN, 255, rndBrightness);
  FastLED.show();
    
}

//=====================================================================================
// Ramp up the brigthness of the LED strip sequence over the specified number of timed steps
//=====================================================================================
void LEDStripRampUpBrightness(int steps, 
                              unsigned long msPerStep, 
                              int startBrightness, 
                              int stopBrightness)
{
  //___ Brightness ________________________________________________________________
  bool done = false;
  int brightnessStep = (stopBrightness - startBrightness) / steps;
  int brightness = startBrightness;
     
  for (int stepIdx = 0; stepIdx <= steps; stepIdx++)
  {
    unsigned long startTime = millis();
    done = false;
    
    //___ Run the sequence for at least the specified time ________________________
    while (done == false)
    {
      //___ Execute a sequence ____________________________________________________          
      LEDStripSequence(brightness);
      if (millis()-startTime >= msPerStep)
      {
        done = true;        
      }      
    }
    //___ Adjust brightness for next step _________________________________________
    brightness = brightness + brightnessStep; 

    //___ Error check the brightness (must be 0 to 0xFF) __________________________
    if (brightness < 0)
    {           
      brightness = 0;
    }
    if (brightness > 0xFF)
    {           
      brightness = 0xFF;
    }

  }
}

//=====================================================================================
// Ramp up the brigthness of the LED strip sequence over the specified number of timed steps
//=====================================================================================
void LEDStripRampDownBrightness(int steps, 
                                unsigned long msPerStep, 
                                int startBrightness, 
                                int stopBrightness)
{
  //___ Brightness ________________________________________________________________
  bool done = false;
  int brightnessStep = (stopBrightness - startBrightness) / steps;
  int brightness = startBrightness;


  for (int stepIdx = 0; stepIdx <= steps; stepIdx++)
  {
    unsigned long startTime = millis();
    done = false;

    //___ Init the LED to random with new max brightness ____________________________
    for (int idx = 0; idx < NUM_LEDS; idx++)
    {
      int rndBrightness = random(MIN_BRIGHTNESS-5, brightness); 
      if (rndBrightness < 0)
      {
        rndBrightness = 0;              
      }                               
      leds[idx] = CHSV(HUE_GREEN, 255, rndBrightness);                                    
    }                        

    //___ Run the sequence for at least the specified time ________________________
    while (done == false)
    {
      //___ If ramping down limit the current values to new max ___________________         
      if (brightnessStep < 0)
      {
      }
      //___ Execute a sequence ____________________________________________________          
      LEDStripSequence(brightness);
      if (millis()-startTime >= msPerStep)
      {
        done = true;        
      }      
    }
    //___ Adjust brightness for next step _________________________________________
    brightness = brightness + brightnessStep; 

    //___ Error check the brightness (must be 0 to 0xFF) __________________________
    if (brightness < 0)
    {           
      brightness = 0;
    }
    if (brightness > 0xFF)
    {           
      brightness = 0xFF;
    }

  }
}


