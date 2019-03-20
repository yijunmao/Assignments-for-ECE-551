#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  // char -> Bitstring
  // implement using recursion
  // leaf node
  // How to insert in a map
  // mymap.insert ( std::pair<char,int>('z',500) );
  // case 1: internal node
  if (this->sym == NO_SYM) {
    // assert to help debugging
    assert(this->left != NULL && this->right != NULL);
    // update the left bitstring
    BitString bl = b.plusZero();
    // recurse to left
    this->left->buildMap(bl, theMap);
    // update the right bitstring
    BitString br = b.plusOne();
    // recurse to right
    this->right->buildMap(br, theMap);
  }
  // case 2: leaf node
  else {
    // assert to help debugging
    assert(this->left == NULL && this->right == NULL);
    // update the map
    theMap.insert(std::pair<unsigned, BitString>(this->sym, b));
  }
}
