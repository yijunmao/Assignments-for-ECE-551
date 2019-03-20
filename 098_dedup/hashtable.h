#include <list>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template<typename Hasher>
class HashTable
{
 private:
  vector<list<pair<string, string> > > * table;
  Hasher hash;
  unsigned int buckets;
  //unsigned int count;

 public:
  // default constructor
  HashTable() : hash(std::hash<string>()), table(NULL), buckets(2000) { table->resize(2000); }

  // helper contain method
  // given the hash value, return a string
  // if found, return the value of the found element(filename)
  // if not found, return an empty string
  // add method
  string contains(list<pair<string, string> > & targetList, string & key) {
    typename list<pair<string, string> >::iterator it;
    for (it = targetList.begin(); it != targetList.end(); ++it) {
      if (key == it->first) {
        return it->second;
      }
    }
    string empty_str;
    return empty_str;
  }

  string add(const string & key, string & value) {
    // hash function
    unsigned int h = hash(key);
    h = h % (buckets);

    string oldDir = contains((*table)[h], key);
    // case1: same element found in the table
    if (oldDir.size() != 0) {
      return oldDir;
    }
    // case2: it's a new element
    else {
      (*table)[h].push_front(pair<string, string>(key, value));
    }
  }
};
