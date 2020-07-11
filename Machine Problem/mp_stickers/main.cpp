#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image baseImage;
	baseImage.readFromFile("shooting.png");

	Image sticker1;
	sticker1.readFromFile("hacki.png");
	sticker1.scale(0.2);

	Image sticker2;
	sticker2.readFromFile("A+.png");
  sticker2.scale(0.1);


	Image sticker3;
	sticker3.readFromFile("225.png");
  sticker3.scale(0.5);

  StickerSheet goal(baseImage, 3);
  goal.addSticker(sticker1,330,35);
  goal.addSticker(sticker2,600,180);
  goal.addSticker(sticker3,460,110);

  Image outImage;
  outImage = goal.render();
  outImage.writeToFile("myImage.png");

  return 0;
}
