/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include "binarytree.h"
#include <iostream>
#include <vector>
using namespace std;

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
    cout<<endl;

}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    if(subRoot == NULL || (subRoot->left == NULL && subRoot->right == NULL))
        return;
    
    Node* temp = subRoot->left;
    subRoot->left=subRoot->right;
    subRoot->right=temp;
    mirror(subRoot->left);
    mirror(subRoot->right);
}



/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    InorderTraversal<T> inorder(root);
    bool ordered = true;
    T temp;
    int count=0;
    for (typename TreeTraversal<T>::Iterator itr = inorder.begin(); itr != inorder.end(); ++itr) {

        if (count !=0){
            if ((*itr)->elem < temp) {
                ordered = false;
            }
        }
        count++;
        temp=(*itr)->elem;
    }
    return ordered;
}



// template <typename T>
// bool BinaryTree<T>::isOrderedIterative() const
// {
//     // your code here
//     InorderTraversal<T> inorder(root);
//     bool ordered = true;
//     for (typename TreeTraversal<T>::Iterator itr = inorder.begin(); itr != inorder.end(); ++itr) {
//         typename TreeTraversal<T>::Iterator itr1 = inorder.end();
//         if ((*itr) == prev((*itr1),2)) {
//             break;
//         }
//         if ((*itr)->elem > next((*itr),1)->elem) {
//             ordered = false;
//         }
//     }
//     return ordered;
// }




/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    vector<T> array;
    isOrderedRecursive(root, array);
    bool ordered = true;
    for (unsigned i = 0; i < array.size(); i++) {
        if (array[i] >= array[i+1]) {
            ordered = false;
        }
    }
    return ordered;
}


template <typename T>
void BinaryTree<T>::isOrderedRecursive(Node* subRoot, vector<T> &array)const{
    if(subRoot == NULL){
      return;
    }
    isOrderedRecursive(subRoot->left, array);
    array.push_back(subRoot->elem);
    isOrderedRecursive(subRoot->right, array);
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */

template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    vector<T> temp;
    getPaths(root, paths, temp);
}


template <typename T>
void BinaryTree<T>::getPaths(const Node* node, std::vector<std::vector<T>>& paths, vector<T> array) const
{
    if (node == NULL) {
        return;
    }
    array.push_back(node->elem);
    if (node->left==NULL&&node->right==NULL) {
        paths.push_back(array);
    }
    getPaths(node->left,paths,array);
    getPaths(node->right,paths,array);
    array.pop_back();
}



/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */

template <typename T>
int BinaryTree<T>::sumDistances() const
{
    return sumDistances(root, 0);
}
template <typename T>
int BinaryTree<T>::sumDistances(Node *subRoot, unsigned longitude) const{
  if (subRoot == NULL){
      return 0;
    }
    unsigned longitude1= sumDistances(subRoot->right, longitude + 1);
    unsigned longitude2= sumDistances(subRoot->left, longitude + 1);
  return longitude + longitude1 + longitude2 ;
}

