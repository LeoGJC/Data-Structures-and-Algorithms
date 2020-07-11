
#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze kop;
    kop.makeMaze(70, 40);

    PNG* mypng = kop.drawCreativeMaze();
    mypng->writeToFile("creative.png");
    std::cout << "drawMaze complete" << std::endl;
    return 0;
}