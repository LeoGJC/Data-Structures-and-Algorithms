#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double h;
  unsigned pix = x*y/2 + x*x/3+ y*y/3;
  h = 280 - (pix % 250);
  HSLAPixel pixel(h, 1, 0.4);
  return pixel;
}
