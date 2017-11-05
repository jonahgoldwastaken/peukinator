// Importing an unnecessary amount of libraries
#include <NewPing.h>

#include <HardwareSerial.h>
#include <MP3Player_KT403A.h>

#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <FastLED.h>
#include <fastpin.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <fastspi.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

// Led pins and amount
#define LED_PIN 7
#define NUM_LEDS 30

// Other pins used
#define PRESS_PIN A0
#define POT_PIN D6

// Defining leds
CRGB leds[NUM_LEDS];

// Defining mp3
HardwareSerial mp3 = D5;

// Delay & Intervals
unsigned long idleTimeOut = 0;     // last time idle
unsigned long lastIdleCycle = 0;   // last time cycled through an idle state
unsigned long idleState = 0;       // the current idle state
unsigned long minIdleTime = 30000; // 30 seconds
unsigned long idleLoopStep = 0;    // current led on strip to execute code on if necessary

// bud counts for data analysation
int tenMinuteCount;
int halfHourCount;
int hourCount;

// Variable keeping track of the game state
// 0 = idle
// 1 = playing
// 2 = won
// 3 = lost
int gameState = 0;

void setup()
{
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

  pinMode(POT_PIN, INPUT);

  Serial.begin(115200);
  mp3.begin(115200);

  // Code voor verbinden met Adafruit
}

void loop()
{
  int currentMotivation = checkPot();
  Serial.print('Motivatie: ');
  Serial.println(currentMotivation);

  int pressValue = analogRead(PRESS_PIN);
  int pirValue = digitalRead(PIR_PIN);

  if (!pressValue < 100)
  {
    if (4294967296 - millis() <= minIdleTime)
      minIdleTime = (4294967296 - millis());
    else
      minIdleTime = millis();

    gameState = 1;
    startGame(currentMotivation);
    return;
  }

  if (millis() - idleTimeOut > minIdleTime)
  {
    gameState = 0;
    idle();
    return;
  }
}

int checkPot()
{
  int potValue = digitalRead(POT_PIN);

  if (potValue < 100)
  {
    return 1;
  }
  else if (potValue < 200)
  {
    return 2;
  }
  else if (potValue < 300)
  {
    return 3;
  }
}

void startGame(int motivation)
{
  SpecifyMusicPlay(motivation);
  PlayResume();

  switch (motivation)
  {
  case 1:
  {
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Green;
    break;
  }
  case 2:
  {
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Red;
  }
  case 3:
  {
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Blue;
  }
  }
  FastLED.show();
}

void idle()
{
  if (millis() - lastIdleCycle < 100)
    return;

  switch (idleState)
  {
  case 0:
  {
    if (4294967296 - millis() <= 100)
      lastIdleCycle = (4294967296 - millis());
    else
      lastIdleCycle = millis();
    leds[idleLoopStep] = CRGB::DarkOrange;
    FastLED.show();
    idleLoopStep++;
    break;
  }
  case 1:
  {
    if (4294967296 - millis() <= 100)
      lastIdleCycle = (4294967296 - millis());
    else
      lastIdleCycle = millis();
    int currentLed = NUM_LEDS - 1 - idleLoopStep;
    leds[currentLed] = CRGB::White;
    FastLED.show();
    idleLoopStep++;
    break;
  }
  case 2:
  {
    if (4294967296 - millis() <= 100)
      lastIdleCycle = (4294967296 - millis());
    else
      lastIdleCycle = millis();
    leds[idleLoopStep] = CRGB::Black;
    FastLED.show();
    idleLoopStep++;
    break;
  }
  case 3:
  {
    if (millis() - lastIdleCycle > 1000)
    {
      if (4294967296 - millis() <= 1000)
        lastIdleCycle = (4294967296 - millis());
      else
        lastIdleCycle = millis();
      for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CRGB::White;
      FastLED.show();
      idleState++;
      break;
    }
  }
  case 4:
  {
    if (millis() - lastIdleCycle > 1000)
    {
      if (4294967296 - millis() <= 1000)
        lastIdleCycle = (4294967296 - millis());
      else
        lastIdleCycle = millis();
      for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CRGB::Black;
      FastLED.show();
      idleState++;
      break;
    }
  }
  case 5:
  {
    if (4294967296 - millis() <= 100)
      lastIdleCycle = (4294967296 - millis());
    else
      lastIdleCycle = millis();
    leds[idleLoopStep] = CRGB::Green;
    FastLED.show();
    leds[idleLoopStep] = CRGB::Black;
    idleLoopStep++;
    break;
  }
  case 6:
  {
    if (4294967296 - millis() <= 100)
      lastIdleCycle = (4294967296 - millis());
    else
      lastIdleCycle = millis();
    int currentLed = NUM_LEDS - 1 - idleLoopStep;
    leds[currentLed] = CRGB::Red;
    FastLED.show();
    leds[currentLed] = CRGB::Black;
    idleLoopStep++;
    break;
  }
  case 7:
  {
    if (4294967296 - millis() <= 100)
      lastIdleCycle = (4294967296 - millis());
    else
      lastIdleCycle = millis();
    leds[idleLoopStep] = CRGB::Blue;
    FastLED.show();
    idleLoopStep++;
    break;
  }
  case 8:
  {
    if (millis() - lastIdleCycle > 500)
    {
      if (4294967296 - millis() <= 500)
        lastIdleCycle = (4294967296 - millis());
      else
        lastIdleCycle = millis();
      for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CRGB::Green;
      FastLED.show();
      idleState++;
      break;
    }
  }
  case 9:
  {
    if (millis() - lastIdleCycle > 500)
    {
      if (4294967296 - millis() <= 500)
        lastIdleCycle = (4294967296 - millis());
      else
        lastIdleCycle = millis();
      for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CRGB::Red;
      FastLED.show();
      idleState++;
      break;
    }
  }
  case 10:
  {
    if (millis() - lastIdleCycle > 500)
    {
      if (4294967296 - millis() <= 500)
        lastIdleCycle = (4294967296 - millis());
      else
        lastIdleCycle = millis();
      for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CRGB::Blue;
      FastLED.show();
      idleState++;
    }
  }
  case 11:
  {
    if (4294967296 - millis() <= 100)
      lastIdleCycle = (4294967296 - millis());
    else
      lastIdleCycle = millis();
    leds[idleLoopStep] = CRGB::Black;
    FastLED.show();
    idleLoopStep++;
    break;
  }
  default:
  {
    idleState = 0;
    break;
  }
  }
  if (idleLoopStep == NUM_LEDS)
  {
    idleLoopStep = 0;
    idleState++;
  }
}