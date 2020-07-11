/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */


template <typename T>
List<T>::List() {
  /// @todo Graded in MP3.1
  head_=NULL;
  tail_=NULL;
  length_=0;
}



template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}



/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */



/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* empty;
  while (head_ != NULL) {
    
    empty = head_;
    head_ = head_->next;
    delete empty;
  }

  head_ = NULL;
  tail_ = NULL;
  empty = NULL;
  length_ = 0;

  
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* empty = new ListNode(ndata);
  if(head_ == NULL){
    head_ = empty;
    head_->prev = NULL;
    head_->next = NULL;
    tail_ = empty;
    
  }
  else{
    empty->next = head_;
    head_->prev = empty;
    empty = NULL;
    head_ = head_->prev;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* empty = new ListNode(ndata);
  if(length_ == 0){
    head_ = empty;
    tail_ = empty;
  }
  else{
    tail_->next = empty;
    empty->prev = tail_;
    tail_ = tail_->next;
    tail_ = empty;
  }
  length_++;
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */


/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode* other_head = start;
  if (splitPoint == 0){
        other_head=start;
        start = nullptr;
        return other_head;
  }
  
  int add = 0;
  while (add <= splitPoint-2) {
    other_head = other_head->next;
    add++;
  }
  ListNode* out_head = other_head->next;
  other_head->next = NULL;
  return out_head;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
    
  ListNode* move = head_;
  while( move != NULL && move->next != NULL){
    ListNode* followed = move->next;
    ListNode* change = move;
    
    if (followed->next == NULL) {
      move = move->next;
      move->next = NULL;
      return;
    } 
    if (followed->next != NULL) {
      change->prev = move->prev;
      ListNode* two_head = followed->next;
      move->next = two_head;
      move = two_head;
      change->next = move;
      move->prev = change;

      tail_->next = followed;
      followed->prev = tail_;
      followed->next = NULL;
      tail_ = tail_->next;
    } 
  }
  return;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */

template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if(startPoint==NULL) {
    return;
  }
  if(endPoint==NULL) {
    return;
  }
  if(startPoint==endPoint) {
    return;
  }
  ListNode * nowptr,* frontptr,* followptr;
  nowptr = startPoint;
  frontptr = nowptr->prev;
  followptr = nowptr->next;
  nowptr->next = endPoint->next;
  nowptr->prev = followptr;
  nowptr = followptr;

  while (nowptr != endPoint) {
    followptr = nowptr->next;
    nowptr->next = nowptr->prev;
    nowptr->prev = nowptr;
    nowptr = followptr;
  }

  endPoint->next = endPoint->prev;
  endPoint->prev = frontptr;

  if (head_ != startPoint) {
    frontptr->next = nowptr;
  } else {
    head_ = endPoint;
  } 
  if (tail_ != endPoint) {
    startPoint->next->prev = startPoint;
  } else {
    tail_ = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
// template <typename T>
// void List<T>::reverseNth(int n) {
//   /// @todo Graded in MP3.2
// }

template <typename T>
void List<T>::reverseNth(int n) {
  ListNode * countbegin = head_;
  ListNode * countend = countbegin;

  while (countbegin != NULL) {
  
      for (int sum = 1; sum < n;++sum) {
        if(countend==tail_) {
          break;
        } else {
          countend = countend->next;
        }
      }
    reverse(countbegin, countend);
    countbegin = countbegin->next;
    countend = countbegin;
  }
}



/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the one sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */


template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * one, ListNode* two) {
  /// @todo Graded in MP3.2
  
  if(!two) return one;
  if(!one) return two;
  
  ListNode* other_head = head_;
  if(two->data< one->data ){
    other_head = two;
    two = two->next;
  }
  else{
    other_head = one;
    one = one->next;
  }

  ListNode* other_end = other_head;

  while(one != NULL && two != NULL){
    if(one->data < two->data){
      one->prev = other_end;
      other_end->next = one;
      one = one->next;
    }
    else{
      two->prev = other_end;
      other_end->next = two;
      two = two->next;
    }
    other_end = other_end->next;
  }
  if(one && two) {
    other_end = NULL;
  }
  if(!two){
    one->prev = other_end;
    other_end->next = one;
  }
  if(!one){
    two->prev = other_end;
    other_end->next = two;
  }
  return other_head;
}



/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */

template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int range) {
if (start->next == NULL || range==1) {return start;}
  	ListNode * minor = split(start, range / 2);
return merge(mergesort(start, range / 2), mergesort(minor, (range / 2)+(range % 2)));
}
