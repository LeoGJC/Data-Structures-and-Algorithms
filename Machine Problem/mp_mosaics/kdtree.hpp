/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int sortcurr_) const
{
    /**
     * @todo Implement this function!
     */
    if(first[sortcurr_]!=second[sortcurr_]){
        return first[sortcurr_]<second[sortcurr_];
    }
    return first<second;
}


template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& optimal,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double first_d = 0.0;
    double second_d = 0.0;
    int i = 0;
    while(i<Dim) {
        first_d += (target[i] - optimal[i]) * (target[i] - optimal[i]);
       second_d += (target[i] - potential[i]) * (target[i] - potential[i]);
       i++;
    }
     
    if(first_d  == second_d){
        return (potential<optimal);
    }
    if(first_d <second_d){
        return 0;
    }
    if(first_d >second_d){
        return 1;
    }
    return 0;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    t = newPoints;
    if (newPoints.size() == 1) return;
    else {root=quick_sort(0, t.size()-1,0);}

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::quick_sort(int lt, int rg, int sortcurr_){
    if(lt>rg){
        return 0;
    }
    int half = (lt+rg)/2;
    choosefast(lt,rg,half,sortcurr_);
    KDTreeNode * cur = new KDTreeNode(t[half]);
    cur->left=quick_sort(lt, half-1, (sortcurr_+1)%Dim);
    cur->right=quick_sort(half+1, rg, (sortcurr_+1)%Dim);
    return cur;
}

template <int Dim>
void KDTree<Dim>::choosefast(int lg, int rt, int half_point, int sortcurr_){
    if (lg == rt){
        return;
    }
    int idx = partition(lg, rt, (lg + rt) / 2, sortcurr_);
    if(idx == half_point) return;
    if (idx > half_point){
        choosefast(lg, idx-1, half_point, sortcurr_);
    }
    if (idx < half_point){
        choosefast(idx+1, rt, half_point, sortcurr_);
    }
}

template <int Dim>
int KDTree<Dim>::partition(int l, int r, int half_point, int sortcurr_){
    Point<Dim> mid = t[half_point];
    Point<Dim> temp = mid;
    t[half_point] = t[r];
    t[r] = temp;
    int otherindex = l;
    int i = l;
    do {
        if(smallerDimVal(t[i],mid,sortcurr_)){
            Point<Dim> temp = t[otherindex];
            t[otherindex] = t[i];
            t[i] = temp;
            otherindex++;
        }
        i++;
    }
    while(i<r);
    temp = t[r];
    t[r] = t[otherindex];
    t[otherindex] = temp;
    return otherindex;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  makecopy(other);

}

template <int Dim>
void KDTree<Dim>::makecopy(const KDTree<Dim>& other){
    size=other.size;
    t=other.t;
    root=quick_sort(t, 0, t.size()-1,0);
}
template <int Dim>
void KDTree<Dim>::makeclear(KDTreeNode* root){
    if(root==NULL){
        return;
    }
    makeclear(root->left);
    makeclear(root->right);
    delete root;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this!=&rhs){
      clear(rhs.root);
      root = makecopy(rhs);
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  makeclear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    KDTreeNode* cur = root;
    Point<Dim> optimal = cur->point;
    Point<Dim> temp = query;  //To prevent error
    helper_nearest(optimal,cur,  temp, 0);
    return optimal;
}

template <int Dim>
double KDTree<Dim>::ouqi(const Point<Dim>& one, const Point<Dim>& other) const
{
    double kop = 0.0;
    int r = 0;
    do{
        kop += (one[r]-other[r])*(one[r]-other[r]);
        r++;
    }
    while(r<Dim);
    return kop;
}

template <int Dim>
double KDTree<Dim>::ouqi1(const Point<Dim>& one, const Point<Dim>& other,int r) const
{
    double kop = 0.0;
    kop = (one[r]-other[r])*(one[r]-other[r]);
    return kop;
}

template <int Dim>
void KDTree<Dim>::helper_nearest(Point<Dim> &optimal,KDTreeNode* now, Point<Dim> &query, int dimension) const{
    if(now == NULL){
      return;
    }
    KDTreeNode* next_node = now;
    KDTreeNode* other_node = now;
    if(smallerDimVal(now->point, query, dimension)){
      next_node = now->right;
      other_node = now->left;
    }
    if(!smallerDimVal(now->point, query, dimension)){
      next_node = now->left;
      other_node = now->right;
    }
    helper_nearest( optimal, next_node,query, (dimension + 1) % Dim);


    if(shouldReplace(query, optimal, now->point)){
      optimal = now->point;
    }
    double radius = 0.0;
    radius=ouqi(optimal,query);
    double distance = 0.0;
    distance = ouqi1(now->point,query,dimension);
    if(radius < distance){
    } else {
        helper_nearest( optimal,other_node, query, (dimension + 1) % Dim);
    }
}
