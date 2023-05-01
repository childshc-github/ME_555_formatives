#include "IntMatrix.h"

// default constructor
IntMatrix::IntMatrix() {
  numRows = 0;
  numColumns = 0;
  rows = NULL;
  // rows = new IntArray *[0]();
}

// constructor
IntMatrix::IntMatrix(int r, int c) {
  numRows = r;
  numColumns = c;
  if (numRows == 0) {
    rows = NULL;
    return;
  }
  rows = new IntArray *[r]();
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}

// copy constructor
IntMatrix::IntMatrix(const IntMatrix & rhs) {
  numColumns = rhs.numColumns;
  numRows = rhs.numRows;
  if (numRows == 0) {
    rows = NULL;
  }
  rows = new IntArray *[numRows]();
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(rhs[i]);
  }
}

// destructor
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

// assignment operator
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    // create temp to hold
    IntArray ** temp = new IntArray *[rhs.numRows]();
    for (int i = 0; i < rhs.numRows; i++) {
      // use = operator from IntArray
      temp[i] = new IntArray(rhs[i]);
    }
    // delete columns in each row
    for (int s = 0; s < this->numRows; s++) {
      delete this->rows[s];
    }
    // delete rows
    delete[] rows;
    numColumns = rhs.numColumns;
    numRows = rhs.numRows;
    this->rows = temp;
  }

  // numRows = rhs.numRows;
  // numColumns = rhs.numColumns;
  // if (numRows == 0) {
  //   rows = NULL;
  //   return *this;
  // }
  // rows = new IntArray *[numRows]();
  // for (int i = 0; i < numRows; i++) {
  //   rows[i] = new IntArray(numColumns);
  //   rows[i] = rhs.rows[i];
  // }
  return *this;
}

// get num of rows
int IntMatrix::getRows() const {
  return this->numRows;
}

// get num of columns
int IntMatrix::getColumns() const {
  return this->numColumns;
}

// [] operator
const IntArray & IntMatrix::operator[](int index) const {
  assert(index < this->numRows);
  assert(index >= 0);
  return *this->rows[index];
}

// same [] operator
IntArray & IntMatrix::operator[](int index) {
  assert(index < this->numRows);
  assert(index >= 0);
  return *this->rows[index];
}

// equality overload
bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (this->numRows != rhs.numRows) {
    return false;
  }
  if (this->numColumns != rhs.numColumns) {
    return false;
  }

  for (int i = 0; i < rhs.numRows; i++) {
    if (*rows[i] != rhs[i]) {
      return false;
    }
  }

  return true;
}

// + overload
IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(this->numColumns == rhs.numColumns);
  assert(this->numRows == rhs.numRows);
  IntMatrix answer = IntMatrix(*this);
  for (int i = 0; i < this->numRows; i++) {
    for (int s = 0; s < this->numColumns; s++) {
      answer[i][s] += rhs[i][s];
    }
  }
  return answer;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  // if no entries
  if (rhs.getRows() == 0) {
    s << '[' << ']';
    return s;
  }

  s << '[';
  for (int i = 0; i < rhs.getRows(); i++) {
    if (i == (rhs.getRows() - 1)) {
      s << rhs[i] << ']';
    }
    else {
      s << rhs[i] << ',' << '\n';
    }
  }
  return s;
}
