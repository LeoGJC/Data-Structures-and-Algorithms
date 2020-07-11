#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;
#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG input;
  PNG output;
  input.readFromFile(inputFile);
  output.readFromFile(inputFile);

  for (unsigned x = 0; x < input.width(); x++) {
    for (unsigned y = 0; y < input.height(); y++) {
      HSLAPixel & pixel = input.getPixel(x, y);
      output.getPixel(x,y) = input.getPixel(input.width() - x - 1, input.height() - y - 1);
    }
  }
  output.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  // unsigned int width = 800;
  // unsigned int height = 800;
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      if (y >= 0 && y < png.height()/4 ) {
        pixel.h = 290;
        pixel.s = 0.2;
        pixel.l = 0.8;
        pixel.a = 1;
      } else if (y >= png.height()/4 && y < png.height()/4*2) {
        pixel.h = 175;
        pixel.s = 0.1;
        pixel.l = 0.9;
        pixel.a = 1;
      } else if (y >= png.height()/2 && y < png.height()/4*3){
        pixel.h = 25;
        pixel.s = 0.3;
        pixel.l = 1;
        pixel.a = 1;
      } else {
        pixel.h = 125;
        pixel.s = 0.4;
        pixel.l = 0.75;
        pixel.a = 1;
      }
    }
  }
  return png;
}
