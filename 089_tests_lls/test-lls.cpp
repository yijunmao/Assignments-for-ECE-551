#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

#include "ll.h"

typedef LinkedList<int> IntList;

void testList(void) {
  //test default constructor//
  IntList LL1;
  //check size, head and tail
  assert(LL1.getSize() == 0 && LL1.head == NULL && LL1.tail == NULL);
  //check remove from an empty list
  assert(LL1.remove(12) == false);
  //check index out of bound
  bool isException = false;
  try {
    int a = LL1[3];
    std::cout << "LL1[3]is" << a << std::endl;
  }
  catch (std::exception & e) {
    std::cout << e.what() << std::endl;
    isException = true;
  }
  assert(isException == true);

  //test copy constructor//
  //test copy from a default constructed ll
  IntList LL2(LL1);
  assert(LL2.size == 0 && LL2.head == NULL && LL2.tail == NULL);

  //test addFront//
  LL2.addFront(4);
  assert(LL2.head->data == 4 && LL2.tail->data == 4 && LL2.getSize() == 1 &&
         LL2.head->next == NULL && LL2.head->prev == NULL);

  LL2.addBack(5);

  LL2.addFront(3);

  //test addFront and addBack//
  //check head, tail, and ll size
  assert(LL2.head->data == 3 && LL2.tail->data == 5 && LL2.getSize() == 3);
  //check node connection
  assert(LL2.head->next->data == 4 && LL2.head->next->prev->data == 3);
  assert(LL2.tail->prev->data == 4 && LL2.tail->prev->next->data == 5);

  //test copy from a ll with elements in it
  IntList LL3(LL2);
  //check size
  assert(LL3.getSize() == LL2.getSize());
  //check elements
  for (int i = 0; i < LL3.getSize(); i++) {
    assert(LL3[i] == LL2[i]);
  }

  //check assignment operator case 1
  IntList LL4;
  LL4.addFront(7);
  LL4.addBack(8);
  LL4 = LL3;
  //check size
  assert(LL4.getSize() == LL3.getSize());
  //check elements
  for (int i = 0; i < LL4.getSize(); i++) {
    assert(LL4[i] == LL3[i]);
  }

  //check assignment operator case 2
  LL4 = LL1;
  assert(LL1.getSize() == 0 && LL1.head == NULL && LL1.tail == NULL);

  //test find
  // find sth exists
  int index = LL2.find(3);
  assert(index == 0);
  std::cout << "3 has index" << index << std::endl;
  index = LL2.find(5);
  assert(index == 2);
  std::cout << "5 has index" << index << std::endl;
  index = LL2.find(4);
  assert(index == 1);
  std::cout << "4 has index" << index << std::endl;

  // find sth does not exist
  assert(LL2.find(6) == -1);

  //test remove
  LL3.addBack(6);
  LL3.addBack(7);
  LL3.addFront(-1);
  LL3.addBack(5);  //-1 3 4 5 6 7 5

  //remove sth exists
  assert(LL3.remove(5) == true);
  assert(LL3.remove(5) == true);
  assert(LL3.remove(-1) == true);
  assert(LL3.remove(2) == false);
  assert(LL3.remove(5) == false);
  //3 4 6 7

  //check pointers after removing elements
  assert(LL3.head->data == 3 && LL3.head->prev == NULL && LL3.head->next->next->data == 6 &&
         LL3.head->next->next->prev->data == 4 && LL3.tail->next == NULL);
  //test index and index out of bound, getSize
  assert(LL3[0] == 3 && LL3[1] == 4 && LL3[2] == 6 && LL3[3] == 7);
  bool isException3 = false;
  try {
    //int b = LL3[4];
    //std::cout << "LL3[4] is" << b;
  }
  catch (std::exception & e) {
    std::cout << e.what() << std::endl;
    isException3 = true;
  }
  //assert(isException3);

  assert(LL3.getSize() == 4);
}

int main(void) {
  testList();

  return EXIT_SUCCESS;
}
