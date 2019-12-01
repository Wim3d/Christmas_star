// Christmas star, neopixels, driven by ESP-01
// written by W. Hoogervorst, december 2019
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            2

#define BRIGHTNESS 100

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      50

#define PARTS          5    // equal parts in the figure

#define OFFSET         -5    // offset to start if not starting at pixel 0

#define NUMPATTERNS   17

#define  RED           0xff0000
#define  GREEN         0x00ff00
#define  BLUE          0x0000ff
#define  OFF           0x000000

long lastReconnectAttempt, lastBlink = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t COLOR[] = {RED, GREEN, BLUE, RED, GREEN, BLUE, RED, GREEN, BLUE, RED, GREEN, BLUE}; // this array should be > NUMPIXELS/PARTS
int delayval = 500; // delay for half a second

long randNumber, randNumber2;
int pattern, repetitions;
int switcher = 0, repeater = 1;

void setup() {
  strip.begin(); // This initializes the NeoPixel library.
  strip.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(0));
}

void loop()
{
  randNumber = random(1, NUMPATTERNS);
  randNumber2 = random(2, 4);
  switcher = randNumber;
  repeater = randNumber2;

  switch (switcher)
  {
    case 1: changecolors(repeater); break;
    case 2: colorchase(repeater); break;
    case 3: RGBcolorsfromcenter(repeater); break;
    case 4: colorsfromtip2(repeater); break;
    case 5: colorsfromtip(repeater); break;
    case 6: RGBcolorstocenter(repeater); break;
    case 7: fadecolors(repeater); break;
    case 8: colorsfromtip2(repeater); break;
    case 9: rainbowCycle(10, repeater); break;
    case 10: blinkcolors(repeater); break;
    case 11: steadycolors(repeater); break;
    case 12: rotatetips(repeater); break;
    case 13: fillfromcenter(repeater); break;
    case 14: fillfromtip(repeater); break;
    case 15: colorsfromcenter(repeater); break;
    case 16: colorrun(repeater); break;
    case 17: colorfill(repeater); break;
  }
  /*
    switcher++;
    if (switcher > NUMPATTERNS)
    switcher = 0;
  */
}

// From Adafruit library
void rainbowCycle(uint8_t wait, int repeat) {
  //client.publish(status_topic, "rainbow cycle");
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
  stripoff();
  //client.publish(status_topic, "colorsfromtip");
  // vanaf de punt van de ster naar beide dalen, kleur neemt over
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

void colorsfromcenter(int repeat)
{
  stripoff();
  //from center to tip, starting with LEDs off
  for (int k = 0; k < repeat; k++)
  {
    for (int color = 0; color < 3; color++)
    {
      for (int i = 0; i < ((NUMPIXELS / PARTS / 2) + 1); i++)
      {
        for (int j = 0; j < (PARTS + 1); j++)
        {
          strip.setPixelColor(OFFSET + (NUMPIXELS / PARTS / 2) + (j * (NUMPIXELS / PARTS) + i), COLOR[color]);
          strip.setPixelColor((OFFSET + (NUMPIXELS / PARTS / 2) + (j + 1) * (NUMPIXELS / PARTS) - i), COLOR[color]);
          strip.show();
        }
        delay(delayval);
        stripoff();
      }
    }
  }
}

void fillfromcenter(int repeat)
{
  stripoff();
  //client.publish(status_topic, "colorsfromtip");
  // vanaf de punt van de ster naar beide dalen, kleur neemt over
  //from center to tip, starting with LEDs off
  for (int k = 0; k < repeat; k++)
  {
    for (int color = 0; color < 3; color++)
    {
      for (int i = 0; i < ((NUMPIXELS / PARTS / 2) + 1); i++)
      {
        for (int j = 0; j < (PARTS + 1); j++)
        {
          strip.setPixelColor(OFFSET + (NUMPIXELS / PARTS / 2) + (j * (NUMPIXELS / PARTS) + i), COLOR[color]);
          strip.setPixelColor((OFFSET + (NUMPIXELS / PARTS / 2) + (j + 1) * (NUMPIXELS / PARTS) - i), COLOR[color]);
          strip.show();
        }
        delay(delayval);
      }
      stripoff();
    }
  }
}

void fillfromtip(int repeat)
{
  stripoff();
  //client.publish(status_topic, "colorsfromtip");
  // vanaf de punt van de ster naar beide dalen, kleur neemt over
  //from center to tip, starting with LEDs off
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
      stripoff();
    }
  }
}

void rotatetips(int repeat)
{
  stripoff();
  // one total tip is lit, rotating
  for (int k = 0; k < repeat; k++)
  {
    for (int color = 0; color < 3; color++) //cycle through colors
    {
      for (int j = 0; j < (PARTS); j++)
      {
        for (int i = 0; i < ((NUMPIXELS / PARTS / 2) + 1); i++)
        {
          strip.setPixelColor(OFFSET + (NUMPIXELS / PARTS / 2) + (j * (NUMPIXELS / PARTS) + i), COLOR[color]);
          strip.setPixelColor((OFFSET + (NUMPIXELS / PARTS / 2) + (j + 1) * (NUMPIXELS / PARTS) - i), COLOR[color]);
          if ((OFFSET + (NUMPIXELS / PARTS / 2) + (j + 1) * (NUMPIXELS / PARTS) - i) > NUMPIXELS - 1)
            strip.setPixelColor(0, COLOR[color]);
          strip.show();
        }
        delay(delayval);
        stripoff();
      }
    }
  }
}

void fadecolors(int repeat)
{
  //fade in and out
  //client.publish(status_topic, "fade colors");
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
        }
        strip.show();
        delay(20);
      }
      for (int fade = BRIGHTNESS / 2; fade > 0; fade--)
      {
        for (int i = 0; i < NUMPIXELS; i++)
        {
          strip.setBrightness(fade * 2);
          strip.setPixelColor(i, COLOR[color]);
        }
        strip.show();
        delay(20);
      }
    }
  }
  strip.setBrightness(BRIGHTNESS);
}

void blinkcolors(int repeat) 
{
    //client.publish(status_topic, "blink colors");
  for (int j = 0; j < repeat; j++)
  { for (int color = 0; color < 3; color++)
    {
      for (int i = 0; i < NUMPIXELS; i++)
      {
        strip.setPixelColor(i, COLOR[color]);
      }
      strip.show();
      delay(delayval);
      stripoff();
      delay(delayval);
    }
  }
}

void colorrun(int repeat)
{
  stripoff();
  //client.publish(status_topic, "color run");
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
        stripoff();
      }
    }
  }
}
void colorfill(int repeat)
{
  stripoff();
  //client.publish(status_topic, "colorfill");
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
  stripoff();
  //client.publish(status_topic, "colorsfrom tip2");
  // vanaf de punt van de ster naar beide dalen, met lege ruimte er tussen.
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
        stripoff();
      }
    }
  }
}

void colorsfromtip3(int repeat)
{
  stripoff();
  // vanaf de punt van de ster naar beide dalen, red -> green -> blue -> red -> green -> blue -> red -> green -> blue
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
    stripoff();
    delay(delayval);
  }
}
void steadycolors(int repeat)
{
  //client.publish(status_topic, "steady colors");
  for (int i = 0; i < ((NUMPIXELS / PARTS / 2) + 1); i++)
  {
    for (int j = 0; j < (PARTS + 1); j++)
    {
      strip.setPixelColor(OFFSET + (j * (NUMPIXELS / PARTS) + i), COLOR[i]);
      strip.setPixelColor((OFFSET + (j + 1) * (NUMPIXELS / PARTS) - i), COLOR[i]);
      strip.show();
    }
  }
  delay(delayval * repeat * 4);
}

void colorchase(int repeat)
{
  stripoff();
  //client.publish(status_topic, "color chase");
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
  stripoff();
  //client.publish(status_topic, "change colors");
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

void RGBcolorstocenter(int repeat)
{
  stripoff();
  //client.publish(status_topic, "colors to center");
  // R G B vanaf de punt van de ster naar beide dalen
  for (int m = 0; m < repeat * 2; m++) {
    for (int k = 3; k > 0; k--)
    {
      for (int i = ((NUMPIXELS / PARTS / 2) + 1); i >= 0; i--)
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
void RGBcolorsfromcenter(int repeat)
{
  stripoff();
  //client.publish(status_topic, "colors from center");
  // R G B vanaf de dalen van de ster naar de punt,
  for (int m = 0; m < repeat * 2; m++) {
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


void stripoff(void)
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    strip.setPixelColor(i, OFF);
  }
  strip.show();
}
