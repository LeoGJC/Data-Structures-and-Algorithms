#include "maze.h"
#include "dsets.h"
#include <stdlib.h> // rand
#include <queue>
#include <map>
#include <algorithm> // std::random_shuffle
#include <cmath> 

using namespace std;

SquareMaze::SquareMaze() {
  // do nothing
}

void SquareMaze::makeMaze(int width, int height) {
  height_ = height;
  width_ = width;


  int i = 0;
  do{
    flo_wal.push_back(true);
    rig_wal.push_back(true);
    i++;
  }
  while (i < width * height);

  DisjointSets cir_;
  cir_.addelements(width_*height_);
  int j=0;
  do {
    int del_x = rand() % width;
    int del_y = rand() % height;

  if(rand() % 2) {
    if (del_x < width - 1 && cir_.find(del_y * width + del_x) != cir_.find(del_y * width + del_x + 1)) {
        rig_wal[del_y * width + del_x] = false;
        cir_.setunion(del_y * width + del_x, del_y * width + (del_x + 1));
        j++;
    }
  } else if (del_y < height - 1 && cir_.find(del_y * width + del_x) != cir_.find((del_y + 1) * width + del_x)) {
      flo_wal[del_y * width + del_x] = false;
      cir_.setunion(del_y * width + del_x, (del_y + 1) * width + del_x);
      j++;
  }
  } while (j < width * height - 1);
}



bool SquareMaze::canTravel(int x, int y, int dir) const {
  if (dir == 0) {
    return !rig_wal[x + y * width_];
  }

  if (dir == 1) {
    return !flo_wal[x + y * width_];
  }
  if (dir == 2 && x == 0) {
    return false;
  }
  if (dir == 2 && x != 0) {
    return !rig_wal[x + y * width_ - 1];
  }
  if (dir == 3 && y == 0) {
    return false;
  }
  if (dir == 3 && y != 0) {
    return !flo_wal[x + (y - 1) * width_];
  }
  return false;
}


void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  if (dir == 0) {
    rig_wal[x + y * width_] = exists;
  }
  else if (dir == 1) {
    flo_wal[x + y * width_] = exists;
  }
}

vector<int> SquareMaze::solveMaze() {
  queue<int> q; 
  vector<bool> beento;
  vector<int> endline; // used to trace all the possible path to the end_ row
  map<int, int> ways_togo; // the direction from one cell to another cell

  // BFS traversal
  int i = 0;
  do {
    beento.push_back(false);
    i++;
  }
  while (i < width_ * height_);

  beento[0] = true;
  q.push(0);

  while (!q.empty()) {
    int arr_idx = q.front();
    q.pop();
    int x = arr_idx % width_;
    int y = floor(arr_idx / width_);

    if (y != height_ - 1) { // at the end_ row
      endline=endline;
    } else {
      endline.push_back(arr_idx);
    }

    // 4 different ways_togo
    if (canTravel(x, y, 0)) {
      if (beento[arr_idx+1] == false) {
        beento[arr_idx+1] = true;
        q.push(arr_idx+1);
        ways_togo.insert(pair<int, int> (arr_idx+1, arr_idx));
      }
    }
    if (canTravel(x, y, 1)) {
      if (beento[arr_idx + width_]== false) {
        beento[arr_idx + width_] = true;
        q.push(arr_idx + width_);
        ways_togo.insert(pair<int, int> (arr_idx + width_, arr_idx));
      }
    }
    if (canTravel(x, y, 2)) {
      if (beento[arr_idx - 1] == false) {
        beento[arr_idx - 1] = true;
        q.push(arr_idx - 1);
        ways_togo.insert(pair<int, int> (arr_idx-1, arr_idx));
      }
    }
    if (canTravel(x, y, 3)) {
      if (beento[arr_idx - width_]==false) {
        beento[arr_idx - width_] = true;
        q.push(arr_idx - width_);
        ways_togo.insert(pair<int, int> (arr_idx - width_, arr_idx));
      }
    }
  }

  vector<int> path;
  int end_ = width_ - 1;
  while (endline[end_] == endline[end_ - 1]) {
    end_ -= 1; // goes to the cell with smallest x in the end_ row
  }
  int begin_ = endline[end_];
  while (begin_ != 0) { // trace back
    int prev = ways_togo[begin_];
    if (begin_ != prev + 1) {
      path = path;
    } else {
      path.push_back(0);
    }
    
    if (begin_ != prev + width_) {
      path = path;
    } else {
      path.push_back(1);
    }
    
    if (begin_ != prev - 1) {
      path = path;
    } else {
      path.push_back(2);
    }
    
    if (begin_ != prev - width_) {
      path = path;
    } else {
      path.push_back(3);
    }
    begin_ = prev;
  }
  reverse(path.begin(), path.end()); 
  return path;
}



int SquareMaze::find_loc(int x, int y) const
{
return y * width_ + x;
}


PNG * SquareMaze::drawMaze() const {
  int x_togo;
  int y_togo;
  PNG * com_maze = new PNG( 10 * width_ + 1, 10 * height_ +1);
  HSLAPixel bla_whi(0,0,0);


int i = 0;
while (i < 10 * height_ +1) {
  HSLAPixel & pixel = com_maze->getPixel(0, i);
pixel.h = bla_whi.h;
pixel.s = bla_whi.s;
pixel.l = bla_whi.l;
i++;
}
int j =10;
while (j < 10 * width_ +1) {
  HSLAPixel & pixel = com_maze->getPixel(j, 0);
pixel.h = bla_whi.h;
pixel.s = bla_whi.s;
pixel.l = bla_whi.l;
j++;
}

  int y = 0;

  do {
    int x = 0;
    do {
            if (flo_wal[ find_loc(x, y) ] ) {
        int i = 0; 
        do {
          y_togo = ( y + 1 ) * 10;
          x_togo = x * 10 + i;

          HSLAPixel & pixel = com_maze->getPixel(x_togo, y_togo);
          pixel.h = bla_whi.h;
          pixel.s = bla_whi.s;
          pixel.l = bla_whi.l;
          i++;
        }
        while (i <= 10); 
      }

      if ( rig_wal[ find_loc(x, y) ] ) {
        int i = 0;
        do {
          y_togo = y * 10 + i;
          x_togo = (x + 1) * 10;
          HSLAPixel & pixel = com_maze->getPixel(x_togo, y_togo);
          pixel.h = bla_whi.h;
          pixel.s = bla_whi.s;
          pixel.l = bla_whi.l;
          i++;
        }
        while (i <= 10); 
      }
      x++;
    }
    while (x < width_);

    y++;
  }
    while (y < height_);
  
  return com_maze;
}




PNG * SquareMaze::drawMazeWithSolution(){
  vector<int> ans_ = solveMaze();
// get unsolved maze
  PNG * com_maze = drawMaze();

// draw the ans_ on top of it
  int y_togo = 5;
  int x_togo = 5;

  HSLAPixel red(0,1,0.5);
  HSLAPixel white(0,0,1);
  unsigned i= 0;
  do {
     if ( ans_[i] == 0 ){
      for (int j = 0; j <= 10;  ){
        HSLAPixel & pixel = com_maze->getPixel(x_togo + j, y_togo);
        pixel.h = red.h;
        pixel.s = red.s;
        pixel.l = red.l;
        j++;
      }
      x_togo += 10;
      }
      else if ( ans_ [i] == 2){
      for (int j = 0; j <= 10; ){
        HSLAPixel & pixel = com_maze->getPixel(x_togo - j, y_togo);
        pixel.h = red.h;
        pixel.s = red.s;
        pixel.l = red.l;
        j++;
      }
      x_togo -= 10;
    }
    else if ( ans_ [i] == 3){
      for (int j = 0; j <= 10; ){
        HSLAPixel & pixel = com_maze->getPixel(x_togo, y_togo - j);
        pixel.h = red.h;
        pixel.s = red.s;
        pixel.l = red.l;
        j++;
      }
      y_togo -= 10;
    }
   
    
     else if ( ans_ [i] == 1){
      for (int j = 0; j <= 10; ){
        HSLAPixel & pixel = com_maze->getPixel(x_togo, y_togo + j);
        pixel.h = red.h;
        pixel.s = red.s;
        pixel.l = red.l;
        j++;
      }
      y_togo += 10;
    }
    i++;
  } while (i < ans_.size());
 
  for (int i = 1; i < 10; i++){
    HSLAPixel & pixel = com_maze->getPixel(x_togo - 5 + i, y_togo + 5);
      pixel.l = 1.0;
  }
  return com_maze;
}



PNG* SquareMaze::drawCreativeMaze() {
  PNG* com_maze = new PNG(width_*10+1, height_*10 + 1);



int i = 0;
while (i < 10 * height_ +1) {
  HSLAPixel & pixel = com_maze->getPixel(0, i);
pixel.h = 29;
pixel.s = 0.8;
pixel.l = 0.4;
i++;
}
int j =10;
while (j < 10 * width_ +1) {
  HSLAPixel & pixel = com_maze->getPixel(j, 0);
pixel.h = 29;
pixel.s = 0.8;
pixel.l = 0.4;
j++;
}





int y = 0;
int x_togo;
int y_togo;
  do {
    int x = 0;
    do {
            if (flo_wal[ find_loc(x, y) ] ) {
        int i = 0; 
        do {
          y_togo = ( y + 1 ) * 10;
          x_togo = x * 10 + i;

          HSLAPixel & pixel = com_maze->getPixel(x_togo, y_togo);
          pixel.h = 29;
          pixel.s = 0.8;
          pixel.l = 0.4;
          i++;
        }
        while (i <= 10); 
      }

      if ( rig_wal[ find_loc(x, y) ] ) {
        int i = 0;
        do {
          y_togo = y * 10 + i;
          x_togo = (x + 1) * 10;
          HSLAPixel & pixel = com_maze->getPixel(x_togo, y_togo);
          pixel.h = 29;
          pixel.s = 0.8;
          pixel.l = 0.4;
          i++;
        }
        while (i <= 10); 
      }
      x++;
    }
    while (x < width_);

    y++;
  }
    while (y < height_);

  vector<int> ans_ = solveMaze();
  y_togo = 5;
  x_togo = 5;
  unsigned kop=0;
  i = 0;
  do {
     if ( ans_[kop] == 0 ){
      for (int j = 0; j <= 10;  ){
        HSLAPixel & pixel = com_maze->getPixel(x_togo + j, y_togo);
        pixel.h = 29;
        pixel.s = 0.8;
        pixel.l = 0.4;
        j++;
      }
      x_togo += 10;
      }
      else if ( ans_ [kop] == 2){
      for (int j = 0; j <= 10; ){
        HSLAPixel & pixel = com_maze->getPixel(x_togo - j, y_togo);
        pixel.h = 29;
        pixel.s = 0.8;
        pixel.l = 0.4;
        j++;
      }
      x_togo -= 10;
    }
    else if ( ans_ [kop] == 3){
      for (int j = 0; j <= 10; ){
        HSLAPixel & pixel = com_maze->getPixel(x_togo, y_togo - j);
        pixel.h = 29;
        pixel.s = 0.8;
        pixel.l = 0.4;
        j++;
      }
      y_togo -= 10;
    }
   
    
     else if ( ans_ [kop] == 1){
      for (int j = 0; j <= 10; ){
        HSLAPixel & pixel = com_maze->getPixel(x_togo, y_togo + j);
        pixel.h = 29;
        pixel.s = 0.8;
        pixel.l = 0.4;
        j++;
      }
      y_togo += 10;
    }
    kop++;
  } while (kop < ans_.size());

  for (int i = 1; i < 10; i++)
{
HSLAPixel & pixel = com_maze->getPixel(x_togo - 5 + i, y_togo + 5);
pixel.h = 29;
pixel.s = 0.8;
pixel.l = 0.4;
}

return com_maze;
}



