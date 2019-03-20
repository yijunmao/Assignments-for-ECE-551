#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  // make a priority queue
  priority_queue_t pq;
  /*Node * left = NULL;
    Node * right = NULL;*/
  //Node * root = NULL;
  // for each character in the input, construct a new node and add it to the queue
  for (int i = 0; i < 257; i++) {
    // frequency must larger than 0
    if (counts[i] > 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  // build the tree
  // step1: check the number of nodes
  while (pq.size() >= 2) {
    // step2: remove the top two nodes
    // pop the lower freq node
    Node * left = pq.top();
    pq.pop();
    // pop the higher freq node
    Node * right = pq.top();
    pq.pop();
    // step3: build a new node out of them
    // step4: put the new node into the queue
    pq.push(new Node(left, right));
    //
  }

  return pq.top();
  // deque if single node
  /*if (pq.size() == 1) {
    root = pq.top();
    pq.pop();
    }*/

  //return root;
}
