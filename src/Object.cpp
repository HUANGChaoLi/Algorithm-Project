#include "Object.h"
#include <iostream>
#include <cmath>
using namespace std;

Object::Object(int d) {
  _d = d;
  _val = new int[_d];
}

Object::~Object() {
  if (_val != NULL) delete [] _val;
}

double Object::distance(Object & a, Object & b) {
  int d = a._d;
  double result = 0;
  for (int i = 0; i < d; ++i) {
    result += pow(a._val[i] - b._val[i], 2);
  }
  return sqrt(result);
}

void Object::setVal(int d, int val) {
  _val[d] = val;
}

int Object::getVal(int d) {
  return _val[d];
}

ostream& operator<<(ostream& os, const Object& obj) {
  int line = sqrt(obj._d);
  for (int i = 0; i < line; ++i) {
    for (int j = 0; j < line; ++j) {
      os << obj._val[i * line + j];
      if (obj._val[i * line + j] >= 100) os << " ";
      else if (obj._val[i * line + j] >= 10) os << "  ";
      else os << "   ";
    }
    os << endl;
  }
  os << endl << endl;
  return os;
}
