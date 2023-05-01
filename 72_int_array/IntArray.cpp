#include "IntArray.h"

#include <assert.h>

#include <ostream>

#include "IntArray.h"

// default constructor
IntArray::IntArray() {
  numElements = 0;
  data = NULL;
}

// constructor w/ int argument
IntArray::IntArray(int n) {
  numElements = n;
  data = new int[n];
}

// copy constructor
IntArray::IntArray(const IntArray & rhs) {
  numElements = rhs.numElements;
  data = new int[rhs.numElements];

  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}

// destructor
IntArray::~IntArray() {
  delete[] data;
}

// assignment operator
IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}

// const [] operator
const int & IntArray::operator[](int index) const {
  assert(index < this->numElements);
  assert(index >= 0);
  return this->data[index];
}

// [] operator (same code)
int & IntArray::operator[](int index) {
  assert(index < this->numElements);
  assert(index >= 0);
  return this->data[index];
}

// size function
int IntArray::size() const {
  // int size_a = 0;
  // for (int i = 0; i < this->numElements; i++) {
  //   size_a++;
  // }
  // return size_a;
  return numElements;
}

// == operator
bool IntArray::operator==(const IntArray & rhs) const {
  if (this->numElements != rhs.numElements) {
    return 0;
  }
  for (int i = 0; i < this->numElements; i++) {
    if (this->data[i] != rhs.data[i]) {
      return 0;
    }
  }

  return 1;
}

// != operator
bool IntArray::operator!=(const IntArray & rhs) const {
  if (this->numElements != rhs.numElements) {
    return 1;
  }
  for (int i = 0; i < this->numElements; i++) {
    if (this->data[i] != rhs.data[i]) {
      return 1;
    }
  }

  return 0;
}

// << operator
std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() == 0) {
    s << '{' << '}';
    return s;
  }

  s << '{';
  for (int i = 0; i < rhs.size(); i++) {
    if (i == (rhs.size() - 1)) {
      s << rhs[i] << '}';
    }
    else {
      s << rhs[i] << ',' << ' ';
    }
  }

  return s;
}
