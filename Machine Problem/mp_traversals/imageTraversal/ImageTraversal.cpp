#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
    across = NULL;
    begin_ = Point(0, 0);
    beginpt = Point(0, 0);
    png_ = PNG();
    tolerance_=0;
}

ImageTraversal::Iterator::Iterator(PNG & png, Point & start, double tolerance, ImageTraversal* tra) {
    png_ = png;
    begin_ = start;
    beginpt = begin_;
    tolerance_ = tolerance;
    across = tra;

    unsigned i = 0;
    do{
      explored_.push_back(false);
      i++;
    }
    while (i < png_.width() * png_.height()); 
    if (!ableExplored(begin_)) {
        tail = true;
    }
        explored_[begin_.x + begin_.y * png_.width()] = !tail;
        route_.push_back(begin_); 
}



ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (ableExplored(Point(begin_.x + 1, begin_.y))) across->add(Point(begin_.x + 1, begin_.y));
  if (ableExplored(Point(begin_.x, begin_.y + 1))) across->add(Point(begin_.x, begin_.y + 1));
  if (ableExplored(Point(begin_.x - 1, begin_.y))) across->add(Point(begin_.x - 1, begin_.y));
  if (ableExplored(Point(begin_.x, begin_.y - 1))) across->add(Point(begin_.x, begin_.y - 1));
  
  Point follow = across->pop();

  while(explored_[follow.x + follow.y * png_.width()]) {
    if (across->empty()) {
        tail=true;
        return *this;
    } else {
      follow = across->pop();
    }
  }

  if (!across->empty()) {
  begin_ = follow;
  explored_[begin_.x + begin_.y * png_.width()] = true;
  route_.push_back(begin_);
  return *this;
  }
  if (across->empty()) {
    tail=true;
    return *this;
  }
  return *this;
}



bool ImageTraversal::Iterator::ableExplored(Point point) {
    if (point.y >= png_.height()) {
        return false;
    }
    if (point.x >= png_.width()){
      return false;
    }
    HSLAPixel& start = png_.getPixel(beginpt.x, beginpt.y);
    HSLAPixel& Point = png_.getPixel(point.x, point.y);
    if (calculateDelta(start, Point) <= tolerance_) {
        return true;
    } else {
      return false;
    }
    
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return begin_;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return (tail != other.tail);
}
