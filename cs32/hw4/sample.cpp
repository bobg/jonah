#include <iostream>
#include <vector>

using namespace std;

class Item {};

template <typename T>
void frobFirst(vector<T>& v, void frob(T&)) {
  return frob(v[0]);
}

void frobItem(Item& item) {}
void frobItemPtr(Item* item) {}

int main() {
  vector<Item> v;
  frobFirst(v, frobItem);

  vector<Item*> vp;
  frobFirst<Item*>(vp, frobItemPtr);
}
