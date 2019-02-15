#include <Adafruit_NeoPixel.h>
#include <ColorConverter.h>

const int neoPixelPin = 5;   // control pin
const int pixelCount = 7;    // number of pixels

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, neoPixelPin, NEO_GRBW + NEO_KHZ800);
ColorConverter converter;

float intensity = 255;
float change = 2;

void setup() {
  // put your setup code here, to run once:
  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // update strip
  Serial.begin(9600);
}

void loop() {

  if (intensity <= 150 || intensity >= 255) {
    change = -change;
  }
  intensity = intensity +  change;
  float result = sineFade(intensity, 150, 255);


  //back
  strip.setPixelColor(1, 250, 90, 0, result + 5);
  strip.setPixelColor(6, 250, 50, 0, result - 5);
  //middle
  strip.setPixelColor(0, 250, 0, 0, result + 30);
  strip.setPixelColor(2, 250, 0, 0, result + 30);
  strip.setPixelColor(5, 250, 0, 0, result + 30);
  //front
  strip.setPixelColor(3, 250, 50, 0, result + 5);
  strip.setPixelColor(4,250, 90, 0, result - 5);

  strip.show();
  strip.clear();

  Serial.println(result);
}

float sineFade(int inValue, int minValue, int maxValue) {
  float angle = map(inValue, minValue, maxValue, 0, 179);
  float result = (sin((angle * PI / 180) + PI / 2) + 1) * 127.5;
  return result;
}
