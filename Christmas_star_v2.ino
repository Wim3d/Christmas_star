// Christmas star, neopixels, driven attiny85
// written by W. Hoogervorst, december 2019
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            0

#define BRIGHTNESS 100

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      50

#define PARTS          5    // equal parts in the figure

#define OFFSET         -5    // offset to start if not starting at pixel 0

#define PIXELPERPART  (NUMPIXELS)/(PARTS)

#define NUMPATTERNS   20

#define  RED           0xff0000
#define  GREEN         0x00ff00
#define  BLUE          0x1111ff     // a little brighter than pure blue
#define  CYAN          0x00ffff
#define  MAGENTA       0xff00ff
#define  OFF           0x000000

//long lastReconnectAttempt, lastBlink = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
uint32_t COLOR[] = {RED, GREEN, BLUE, RED, GREEN, BLUE, RED, GREEN, BLUE, RED, GREEN, BLUE}; // this array should be > NUMPIXELS/PARTS
uint32_t COLOR2[] = {RED, CYAN, GREEN, MAGENTA, BLUE, RED, CYAN, GREEN, MAGENTA, BLUE}; //this array should be > 2* PARTS
int delayval = 500; // delay for half a second

long randNumber, randNumber2;
int pattern, repetitions;
int switcher = 0, repeater = 1;

void setup() {
  strip.begin(); // This initializes the NeoPixel library.
  strip.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(0));
  //Serial.begin(9600);
}

void loop()
{
  randNumber = random(1, NUMPATTERNS + 1);
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
    case 18: rotatetipscolors(repeater); break;
    case 19: rotate5colors(repeater); break;
    case 20: randomfilloff(repeater); break;
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

void randomfilloff(int repeat)
{
  // random fill with colors
  for (int k = 0; k < repeat; k++)
  {
    for (int color = 0; color < 3; color++)
    {
      stripoff();
      int pixelslit = 0;
      while (pixelslit < NUMPIXELS)
      {
        int r = random(0, NUMPIXELS); // random number of LED in the strip
        if (strip.getPixelColor(r) == 0)
        {
          strip.setPixelColor(r, COLOR[color]);
          pixelslit++;
          strip.show();
          delay(delayval / 8);
        }
      }
      while (pixelslit > 0)
      {
        int r = random(0, NUMPIXELS); // random number of LED in the strip
        if (strip.getPixelColor(r) != 0)
        {
          strip.setPixelColor(r, OFF);
          pixelslit--;
          strip.show();
          delay(delayval / 8);
        }
      }
    }
  }
}

void randomfill(int repeat)
{
  // random fill with colors
  for (int k = 0; k < repeat; k++)
  {
    for (int color = 0; color < 3; color++)
    {
      stripoff();
      int pixelslit = 0;
      while (pixelslit < NUMPIXELS)
      {
        int r = random(0, NUMPIXELS); // random number of LED in the strip
        if (strip.getPixelColor(r) == 0)
        {
          strip.setPixelColor(r, COLOR[color]);
          pixelslit++;
          strip.show();
          delay(delayval / 5);
        }
      }
    }
  }
}

void colorsfromtip(int repeat)
{
  stripoff();
  // from the tips the colors are filled over the different colors
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
  //from center to tip with other LEDs off
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
  //fill from center to tip, starting with LEDs off
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
  //fill from center to tip, starting with LEDs off
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
  // one total tip is lit, rotating same color
  for (int k = 0; k < repeat; k++)
  {
    for (int color = 0; color < 3; color++) //cycle through colors
    {
      for (int j = 0; j < (PARTS); j++)
      {
        strip.fill(COLOR[color], OFFSET + NUMPIXELS / PARTS / 2 + j * NUMPIXELS / PARTS, (NUMPIXELS / PARTS) + 1);
        if ((OFFSET + NUMPIXELS / PARTS / 2 + j * NUMPIXELS / PARTS + (NUMPIXELS / PARTS) + 1) > NUMPIXELS) // last part, ligth first LED (0)
          strip.fill(COLOR[color], 0, 1);
        strip.show();
        delay(delayval);
        stripoff();
      }
    }
  }
}

void rotatetipscolors(int repeat)
{
  stripoff();
  // one total tip is lit, rotating with different colors
  for (int k = 0; k < repeat * 2; k++)
  {
    for (int j = 0; j < (PARTS); j++)
    {
      strip.fill(COLOR2[j], OFFSET + NUMPIXELS / PARTS / 2 + j * NUMPIXELS / PARTS, (NUMPIXELS / PARTS) + 1);
      if ((OFFSET + NUMPIXELS / PARTS / 2 + j * NUMPIXELS / PARTS + (NUMPIXELS / PARTS) + 1) > NUMPIXELS) // last part, ligth first LED (0)
        strip.fill(COLOR2[j], 0, 1);
      strip.show();
      delay(delayval);
      stripoff();
    }
  }
}

void rotate5colors(int repeat)
{
  //strip is filled with PARTS different colors which cycle with one increment
  stripoff();
  for (int k = 0; k < repeat; k++)
  {
    for (int h = PARTS; h > 0; h--) // loop through colors
    {
      for (int i = 0; i < PIXELPERPART; i++)
      {
        for (int j = 0; j < PARTS; j++)
        {
          strip.fill(COLOR2[h + j], i + (j * PIXELPERPART), PIXELPERPART);
          if (i + PIXELPERPART + (j * PIXELPERPART) > NUMPIXELS)
            strip.fill(COLOR2[h + j], 0,  i );
        }
        strip.show();
        delay(delayval / 5);
      }
    }
  }
}


void rotatetips_old(int repeat)
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
  //blink colors
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
  // starting at the tips, the PARTS LEDs run after each other
  stripoff();

  for (int k = 0; k < repeat; k++)
  {
    for (int color = 0; color < 3; color++)
    {
      for (int i = 0; i < (NUMPIXELS / PARTS); i++)
      {
        for (int j = 0; j < PARTS + 1; j++)
        {
          strip.setPixelColor(OFFSET + (j * (NUMPIXELS / PARTS) + i), COLOR[color]);
          if (NUMPIXELS > 30)
            strip.setPixelColor(OFFSET + NUMPIXELS / PARTS / 2 + (j * (NUMPIXELS / PARTS) + i), COLOR[color]); //extra LEDs if it is a large object
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
