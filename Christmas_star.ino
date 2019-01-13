// Christmas star, neopixels, driven by Attigny85
// written by W. Hoogervorst, december 2018
#include <Adafruit_NeoPixel.h>

#define PIN            0    // The pin on the Arduino is connected to the NeoPixels

#define BRIGHTNESS 50       // set brightness

#define NUMPIXELS      25   // Number of NeoPixels are attached to the microcontroller?

#define PARTS          5    // equal parts in the figure/star

#define OFFSET         -3    // offset to start if not starting at pixel 0

#define  RED           0xff0000
#define  GREEN         0x00ff00
#define  BLUE          0x0000ff
#define  OFF           0x000000

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t COLOR[] = {RED, GREEN, BLUE, RED, GREEN, BLUE};
int delayval = 500; // delay for half a second
long randNumber, randNumber2;

void setup() {
  strip.begin(); // This initializes the NeoPixel library.
  strip.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(0));
}

void loop()
{
  randNumber = random(1, 13);     // generate random number to select the pattern
  randNumber2 = random(2, 4);     // generate random number to select the repetitions

  switch (randNumber)
  {
    case 1: changecolors(randNumber2); break;
    case 2: colorchase(randNumber2); break;
    case 3: colorsfromcenter(randNumber2); break;
    case 4: colorsfromtip2(randNumber2); break;
    case 5: colorsfromtip(randNumber2); break;
    case 6: colorstocenter(randNumber2); break;
    case 7: fadecolors(randNumber2); break;
    case 8: colorsfromtip2(randNumber2); break;
    case 9: rainbowCycle(10, randNumber2); break;
    case 10: blinkcolors(randNumber2); break;
    case 11: steadycolors(randNumber2); break;
    case 12: colorrun(randNumber2); break;
    case 13: colorfill(randNumber2); break;
  }
}

// rainbow cycle from adafruit example
void rainbowCycle(uint8_t wait, int repeat) {
  uint16_t i, j;

  for (j = 0; j < 256 * repeat; j++) { // repeat cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

void colorsfromtip(int repeat)
{
  for (int k = 0; k < repeat; k++)
  {
    for (int color = 0; color < 3; color++)
    {
      for (int i = 0; i < ((NUMPIXELS / PARTS / 2) + 1); i++)
      {
        for (int j = 0; j < (PARTS + 1); j++)
        {
          strip.setPixelColor(OFFSET + (j * (NUMPIXELS / PARTS) + i), COLOR[color]);
          strip.setPixelColor((OFFSET + (j + 1) * (NUMPIXELS / PARTS) - i), COLOR[color]);
          strip.show();
        }
        delay(delayval);
      }
    }
  }
}
void fadecolors(int repeat)
{
  //fade in and out
  for (int j = 0; j < repeat; j++)
  {
    for (int color = 0; color < 3; color++)
    {
      for (int fade = 0; fade < BRIGHTNESS / 2; fade++)
      {
        for (int i = 0; i < NUMPIXELS; i++)
        {
          strip.setBrightness(fade * 2);
          strip.setPixelColor(i, COLOR[color]);
          strip.show();
        }
        delay(1);
      }
      for (int fade = BRIGHTNESS / 2; fade > 0; fade--)
      {
        for (int i = 0; i < NUMPIXELS; i++)
        {
          strip.setBrightness(fade * 2);
          strip.setPixelColor(i, COLOR[color]);
          strip.show();
        }
        delay(1);
      }
    }

  }
  strip.setBrightness(BRIGHTNESS);
}

void blinkcolors(int repeat) {
  for (int j = 0; j < repeat; j++)
  { for (int color = 0; color < 3; color++)
    {
      for (int i = 0; i < NUMPIXELS; i++)
      {
        strip.setPixelColor(i, COLOR[color]);
        strip.show();
      }
      delay(delayval);
      for (int i = 0; i < NUMPIXELS; i++)
      {
        strip.setPixelColor(i, OFF);
        strip.show();
      }
      delay(delayval);
    }
  }
}

void colorrun(int repeat)
{
  for (int k = 0; k < repeat; k++)
  {
    for (int color = 0; color < 3; color++)
    {
      for (int i = 0; i < (NUMPIXELS / PARTS); i++)
      {
        for (int j = 0; j < PARTS + 1; j++)
        {
          strip.setPixelColor(OFFSET + (j * (NUMPIXELS / PARTS) + i), COLOR[color]);

        }
        strip.show();
        delay(delayval / 2);
        for (int i = 0; i < NUMPIXELS; i++)
        {
          strip.setPixelColor(i, OFF);
        }
        strip.show();
      }
    }
  }
}
void colorfill(int repeat)
{
  for (int k = 0; k < repeat; k++)
  {
    for (int color = 0; color < 3; color++)
    {
      for (int i = 0; i < (NUMPIXELS / PARTS); i++)
      {
        for (int j = 0; j < PARTS + 1; j++)
        {
          strip.setPixelColor(OFFSET + (j * (NUMPIXELS / PARTS) + i), COLOR[color]);
          strip.show();
        }
        delay(delayval);
      }
    }
  }
}
void colorsfromtip2(int repeat)
{
  for (int k = 0; k < repeat; k++)
  {
    for (int color = 0; color < 3; color++)
    {
      for (int i = 0; i < ((NUMPIXELS / PARTS / 2) + 1); i++)
      {
        for (int j = 0; j < (PARTS + 1); j++)
        {
          strip.setPixelColor(OFFSET + (j * (NUMPIXELS / PARTS) + i), COLOR[color]);
          strip.setPixelColor((OFFSET + (j + 1) * (NUMPIXELS / PARTS) - i), COLOR[color]);
          strip.show();
        }
        delay(delayval);
        for (int i = 0; i < NUMPIXELS; i++)
        {
          strip.setPixelColor(i, OFF);
          strip.show();
        }
      }
    }
  }
}

void colorsfromtip3(int repeat)
{
  for (int k = 0; k < repeat; k++)
  {

    for (int i = 0; i < ((NUMPIXELS / PARTS / 2) + 1); i++)
    {
      for (int j = 0; j < (PARTS + 1); j++)
      {
        strip.setPixelColor(OFFSET + (j * (NUMPIXELS / PARTS) + i), COLOR[i]);
        strip.setPixelColor((OFFSET + (j + 1) * (NUMPIXELS / PARTS) - i), COLOR[i]);
        strip.show();
      }
      delay(delayval);
    }
    for (int i = 0; i < NUMPIXELS; i++)
    {
      strip.setPixelColor(i, OFF);
      strip.show();
    }
    delay(delayval);
  }
}
void steadycolors(int repeat)
{

  for (int i = 0; i < ((NUMPIXELS / PARTS / 2) + 1); i++)
  {
    for (int j = 0; j < (PARTS + 1); j++)
    {
      strip.setPixelColor(OFFSET + (j * (NUMPIXELS / PARTS) + i), COLOR[i]);
      strip.setPixelColor((OFFSET + (j + 1) * (NUMPIXELS / PARTS) - i), COLOR[i]);
      strip.show();
    }

  }
  delay(delayval * repeat);
}

void colorchase(int repeat)
{
  for (int m = 0; m < repeat; m++) {
    for (int k = 0; k < 3; k++)
    {
      for (int i = 0; i < NUMPIXELS; i++)
      {
        strip.setPixelColor(i, COLOR[k]);
        strip.show();
        delay(delayval / 10);
      }
    }
  }
}

void changecolors(int repeat)
{
  for (int m = 0; m < repeat; m++) {
    for (int k = 0; k < 3; k++)
    {
      for (int i = 0; i < NUMPIXELS; i++)
      {
        strip.setPixelColor(i, COLOR[k]);

      }
      strip.show();
      delay(delayval);
    }
  }
}

void colorstocenter(int repeat)
{
for (int m = 0; m < repeat; m++) {
    for (int k = 3; k > 0; k--)
    {
      for (int i = 3; i >= 0; i--)
      {
        for (int j = 0; j < (PARTS + 1); j++)
        {
          strip.setPixelColor(OFFSET + (j * (NUMPIXELS / PARTS) + i), COLOR[k + i]);
          strip.setPixelColor((OFFSET + (j + 1) * (NUMPIXELS / PARTS) - i), COLOR[k + i]);
        }
      }
      strip.show();
      delay(delayval);
    }
  }
}
void colorsfromcenter(int repeat)
{ 
  for (int m = 0; m < repeat; m++) {
    for (int k = 0; k < 3; k++)
    {

      for (int i = 0; i < ((NUMPIXELS / PARTS / 2) + 1); i++)
      {
        for (int j = 0; j < (PARTS + 1); j++)
        {
          strip.setPixelColor(OFFSET + (j * (NUMPIXELS / PARTS) + i), COLOR[k + i]);
          strip.setPixelColor((OFFSET + (j + 1) * (NUMPIXELS / PARTS) - i), COLOR[k + i]);
          strip.show();
        }

      }
      delay(delayval);
    }
  }
}
