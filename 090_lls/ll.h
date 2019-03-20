#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList
{  // fields
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;

    Node() : next(NULL), prev(NULL) {}
    Node(const T & d) : data(d), next(NULL), prev(NULL) {}
    Node(const T & d, Node * n, Node * p) : data(d), next(n), prev(p) {}
  };

  Node * head;
  Node * tail;
  int size;

 public:
  // default constructor
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  // destructor
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
    size = 0;
  }

  // addFront
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  // addBack
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  // remove
  bool remove(const T & item) {
    Node * curr = head;
    while (curr != NULL && curr->data != item) {
      curr = curr->next;
    }
    if (curr == NULL) {
      return false;
    }
    // item found, only one node
    if (head == tail) {
      head = NULL;
      tail = NULL;
    }
    else if (curr == head) {
      head->next->prev = NULL;
      head = head->next;
    }
    else if (curr == tail) {
      tail->prev->next = NULL;
      tail = tail->prev;
    }
    else {
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
    }
    delete curr;
    size--;
    return true;
  }
  // extension of exception class
  /*ass LLException: public std::exception {
  public:
    
  };*/

  // index operator
  T & operator[](int index) {
    // index out of bound or empty list
    if (index < 0 || index > size - 1 || head == NULL) {
      throw std::exception();
    }
    // index in the range
    else {
      Node * ptr = head;
      int count = 0;
      while (count != index) {
        ptr = ptr->next;
        count++;
      }
      return ptr->data;
    }
  }

  // const index operator
  const T & operator[](int index) const {
    if (index < 0 || index > size - 1 || head == NULL) {
      throw std::exception();
    }
    // index in the range
    else {
      Node * ptr = head;
      int count = 0;
      while (count != index) {
        ptr = ptr->next;
        count++;
      }
      return ptr->data;
    }
  }

  // find
  int find(const T & item) const {
    // empty list
    if (head == NULL) {
      return -1;
    }
    // list with elements in it
    else {
      Node * ptr = head;
      size_t count = 0;
      while (ptr->data != item && ptr != tail) {
        ptr = ptr->next;
        count++;
      }
      if (ptr == tail && ptr->data != item) {
        return -1;
      }
      else {
        return count;
      }
    }
  }

  // getSize
  int getSize() const { return size; }

  // copy constructor
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    for (int i = 0; i < rhs.size; i++) {
      addBack(rhs[i]);
    }
  }

  // operator=
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      // delete all the elements first
      while (size != 0) {
        Node * temp = head->next;
        delete head;
        head = temp;
        size--;
      }
      tail = NULL;

      // put elements from rhs into the list
      for (int i = 0; i < rhs.size; i++) {
        addBack(rhs[i]);
      }
    }
    return *this;
  }
};

#endif
