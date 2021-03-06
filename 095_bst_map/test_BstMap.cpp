#include <cstdlib>

#include "bstmap.h"

int main() {
  BstMap<int, int> map1;

  //test insertion
  map1.add(60, 60);
  map1.add(11, 11);
  map1.add(4, 4);
  map1.add(1, 1);
  map1.add(25, 25);
  map1.add(21, 21);
  map1.add(35, 35);
  map1.add(93, 93);
  map1.add(84, 84);
  map1.add(70, 70);
  map1.add(86, 86);

  map1.printPreorder();

  map1.remove(86);
  map1.printPreorder();

  map1.remove(4);
  map1.printPreorder();

  map1.remove(11);
  map1.printPreorder();

  // test assignement operator
  BstMap<int, int> map2;
  map2.add(74, 74);
  map2.add(59, 59);
  map2.add(99, 99);

  BstMap<int, int> map3 = map2;
  map3.printPreorder();

  map3 = map1;
  map3.printPreorder();

  return 0;
}
