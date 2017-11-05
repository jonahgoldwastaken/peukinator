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

#define LED_PIN 7
#define NUM_LEDS 30

#define TRIG_PIN D5
#define ECHO_PIN D6
#define MAX_DISTANCE 400

CRGB leds[NUM_LEDS];

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

HardwareSerial mp3 = D3;

void setup()
{
  
}

void loop()
{
	
}
