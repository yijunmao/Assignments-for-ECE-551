#include <cstdlib>

#include "bstset.h"

int main() {
  BstSet<int> set1;

  //test insertion
  set1.add(60);
  set1.add(11);
  set1.add(4);
  set1.add(1);
  set1.add(25);
  set1.add(21);
  set1.add(35);
  set1.add(93);
  set1.add(84);
  set1.add(70);
  set1.add(86);

  set1.printPreorder();

  set1.remove(86);
  set1.printPreorder();
  std::cout << set1.contains(86);
  std::cout << set1.contains(60);

  set1.remove(4);
  set1.printPreorder();
  std::cout << set1.contains(4);
  std::cout << set1.contains(86);
  std::cout << set1.contains(60);

  set1.remove(11);
  set1.printPreorder();
  std::cout << set1.contains(11);
  std::cout << set1.contains(4);
  std::cout << set1.contains(86);
  std::cout << set1.contains(25);

  // test assignement operator
  BstSet<int> set2;
  set2.add(74);
  set2.add(59);
  set2.add(99);
  set2.contains(60);

  BstSet<int> set3 = set2;
  set3.printPreorder();

  set3 = set1;
  set3.printPreorder();

  return 0;
}
