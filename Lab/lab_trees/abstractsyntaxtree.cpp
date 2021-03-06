#include "abstractsyntaxtree.h"
using namespace std;

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return eval(root);

}
double AbstractSyntaxTree::eval(AbstractSyntaxTree::Node* node) const {
	if (node->elem == "+") {
        return eval(node->left) + eval(node->right);
    } else if (node->elem == "-") {
        return eval(node->left) - eval(node->right);
    } else if (node->elem == "*") {
        return eval(node->left) * eval(node->right);
    } else if (node->elem == "/") {
        return eval(node->left) / eval(node->right);
    } else {
        return std::stod(node->elem);
    }
}