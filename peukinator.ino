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
unsigned long idleTimeOut = 0; // last time idle
unsigned long lastIdleCycle = 0; // last time cycled through an idle state
unsigned long idleState = 0;
unsigned long minIdleTime = 30000; // 30 seconds

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

  if (!pressValue < 100)
  {
    idleTimeOut = millis();
    startGame(currentMotivation);
    return;
  }
}

int checkPot() {
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
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Green;
      }
      break;
    }
    case 2:
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CRGB::Red;
      }
    }
    case 3:
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CRGB::Blue;
      }
    }
  }
  FastLED.show();
}