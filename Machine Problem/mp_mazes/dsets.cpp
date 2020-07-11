#include <vector>
#include "dsets.h"

using namespace std;

void DisjointSets::addelements(int num) {
    int i = 0;
    do {
        arr_.push_back(-1);
        i++;
    }
    while(i<num);
}

int DisjointSets::find(int elem) {
  if (arr_[elem] > 0) {
    int root = find(arr_[elem]);
    arr_[elem] = root;
    return root;
  } 
    return elem;
}

void DisjointSets::setunion(int a, int b) {
  int circle_first = find(a);
  int circle_second = find(b);

  int total = arr_[circle_first] + arr_[circle_second];


  if (arr_[circle_first] >= arr_[circle_second]) {
    arr_[circle_first] = circle_second;
    arr_[circle_second] = total;
  } else if (arr_[circle_first] < arr_[circle_second]) { 
    arr_[circle_second] = circle_first;
    arr_[circle_first] = total;
  } 
}

int DisjointSets::size(int elem) {
  int size = find(elem);
  return -(arr_[size]);
}