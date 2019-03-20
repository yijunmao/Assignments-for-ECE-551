#include <cstdlib>
#include <iostream>

#include "map.h"

// this class inherits from the map class

template<typename K, typename V>
class BstMap : public Map<K, V>
{
 private:
  // fields include node and pointer called root
  class Node
  {
    // fields of a node
   public:
    K key;
    V value;
    Node * left;
    Node * right;

    // default constructor
    Node() : left(NULL), right(NULL) {}
    // constructor
    Node(const K & p, const V & q) : key(p), value(q), left(NULL), right(NULL) {}
    // destructor
    ~Node() {}
  };

  Node * root;

 public:
  // default constructor
  BstMap() : root(NULL) {}

  // insertion, using pointer to pointer
  virtual void add(const K & key, const V & value) {
    Node ** temp = &root;
    while (*temp != NULL) {
      // the added Node has a smaller key
      if (key < (*temp)->key) {
        temp = &(*temp)->left;
      }
      // the added Node has a larger key
      else if (key > (*temp)->key) {
        temp = &(*temp)->right;
      }
      // the added Node has the same key
      else {
        (*temp)->value = value;
        break;
      }
    }
    if (*temp == NULL) {
      *temp = new Node(key, value);
    }
  }

  // lookup, using pointer to pointer
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * const * temp = &root;
    while (*temp != NULL) {
      if (key < (*temp)->key) {
        temp = &(*temp)->left;
      }
      else if (key > (*temp)->key) {
        temp = &(*temp)->right;
      }
      else {
        return (*temp)->value;
      }
    }
    throw std::invalid_argument("No key found in the map.");
  }

  // helper method to find the minimum node in a tree
  Node * FindMin(Node * base) {
    while (base->left != NULL) {
      base = base->left;
    }
    return base;
  }

  // helper method to remove nodes
  Node * remove(Node * base, const K & key) {
    if (base == NULL) {
      return base;
    }
    else if (key < base->key) {
      base->left = remove(base->left, key);
      return base;
    }
    else if (key > base->key) {
      base->right = remove(base->right, key);
      return base;
    }
    else {
      // case 1: no children
      if (base->left == NULL && base->right == NULL) {
        delete base;
        base = NULL;
        return base;
      }
      // case 2: one right child
      else if (base->left == NULL) {
        Node * temp = base;
        base = base->right;
        delete temp;
        return base;
      }
      // case 3: one left child
      else if (base->right == NULL) {
        Node * temp = base;
        base = base->left;
        delete temp;
        return base;
      }
      // case 4: two children
      // step 1: find minimum in right subtree
      // step 2: replace root key and data with that one
      // step 3: remove the minimum
      else {
        Node * temp = FindMin(base->right);
        base->key = temp->key;
        // base value
        base->value = temp->value;
        base->right = remove(base->right, temp->key);
        return base;
      }
    }
  }

  // remove method
  virtual void remove(const K & key) { remove(root, key); }

  // helper method for copy
  void copy_helper(Node * current) {
    if (current != NULL) {
      add(current->key, current->value);
      copy_helper(current->left);
      copy_helper(current->right);
    }
  }

  // destroy method
  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }

  // copy constructor
  BstMap(const BstMap & rhs) : root(NULL) { copy_helper(rhs.root); }

  // assignment operator
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = NULL;
      copy_helper(rhs.root);
    }
    return *this;
  }

  // using swap to have strong exception guarantee
  /*
BstMap temp(rhs);
std::swap(temp root, root);
   */
  // destructor
  // traverse in postorder and delete nodes
  ~BstMap() { destroy(root); }

 public:
  void printPreorder() const { printPreorder(root); }

 private:
  void printPreorder(const Node * current) const {
    if (current != NULL) {
      std::cout << current->key << " ";
      printPreorder(current->left);
      printPreorder(current->right);
    }
  }
};
