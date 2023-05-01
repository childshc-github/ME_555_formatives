#include "IntMatrix.h"

// default constructor
IntMatrix::IntMatrix() {
  numRows = 0;
  numColumns = 0;
  matrix = std::vector<std::vector<int> >();
}

// constructor
IntMatrix::IntMatrix(size_t r, size_t c) {
  numRows = r;
  numColumns = c;
  // matrix = std::vector<std::vector<int> >(r, std::vector<int>(c));
  matrix.resize(r, std::vector<int>(c));
}

// copy constructor
IntMatrix::IntMatrix(const IntMatrix & rhs) {
  // // if empty
  // if (rhs.getRows() == 0) {
  //   numRows = 0;
  //   numColumns = 0;
  //   matrix = std::vector<std::vector<int> >();
  // }

  // // if not empty
  // else {
  //   numRows = rhs.numRows;
  //   numColumns = rhs.numColumns;
  //   matrix = rhs.matrix;
  // }

  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  matrix = rhs.matrix;
}

// destructor (not needed)
IntMatrix::~IntMatrix() {
}

// assignment operator
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    matrix = rhs.matrix;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
  }
  return *this;
}

// return num of rows
size_t IntMatrix::getRows() const {
  // size_t numRows = matrix.size();
  return numRows;
}

// get num of columns
size_t IntMatrix::getColumns() const {
  if (numRows == 0) {
    return 0;
  }
  return numColumns;
  // size_t numColumns = matrix[0].size();
  // return numColumns;
}

// const [] operator
const std::vector<int> & IntMatrix::operator[](size_t index) const {
  // check index valid
  assert(index < matrix.size());
  return matrix[index];
}

// [] operator
std::vector<int> & IntMatrix::operator[](size_t index) {
  // check index valid
  assert(index < matrix.size());
  return matrix[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  // make sure same num rows
  if (matrix.size() != rhs.getRows()) {
    return false;
  }

  // check same num columns
  if (this->getColumns() != rhs.getColumns()) {
    return false;
  }

  // check values of entries
  for (size_t i = 0; i < rhs.getColumns(); i++) {
    for (size_t s = 0; s < rhs.getRows(); s++) {
      if (matrix[s][i] != rhs[s][i]) {
        return false;
      }
    }
  }

  // if equal
  return true;
}

// + operator
IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  // assert same rows/columns
  assert(this->getColumns() == rhs.getColumns());
  assert(this->getRows() == rhs.getRows());

  // return summed matrix
  IntMatrix answer = IntMatrix(*this);
  for (size_t i = 0; i < this->getRows(); i++) {
    for (size_t s = 0; s < this->getColumns(); s++) {
      answer[i][s] += rhs[i][s];
    }
  }
  return answer;
}

// print rows
std::ostream & operator<<(std::ostream & s, const std::vector<int> & rhs) {
  if (rhs.size() == 0) {
    s << '{' << '}';
    return s;
  }

  s << '{';
  for (size_t i = 0; i < rhs.size(); i++) {
    if (i == (rhs.size() - 1)) {
      s << rhs[i] << '}';
    }
    else {
      s << rhs[i] << ',' << ' ';
    }
  }

  return s;
}

// print matrix to ostream
std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  // // if no entries
  // if ((rhs.getRows() == 0) || (rhs.getColumns() == 0)) {
  //   s << '[' << ' ' << ' ' << ']';
  //   return s;
  // }

  // // else if (rhs.getColumns() == 0) {
  // //   for (size_t r = 0; r < rhs.getRows(); r++) {
  // //     s << '{' << rhs[r][0] << '}';
  // //   }
  // // }

  // // if has entries
  // s << '[' << ' ';

  // for (size_t i = 0; i < rhs.getRows(); i++) {
  //   s << '{';
  //   for (size_t r = 0; r < rhs.getColumns(); r++) {
  //     if ((i == (rhs.getRows() - 1)) && (r == (rhs.getColumns() - 1))) {
  //       s << rhs[i][r] << '}' << ' ' << ']';
  //       return s;
  //     }
  //     else if (r == (rhs.getColumns() - 1)) {
  //       s << rhs[i][r] << '}' << ',' << '\n';
  //     }
  //     else {
  //       s << rhs[i][r];
  //       s << ',' << ' ';
  //     }
  //   }
  // }

  // if no entries
  if (rhs.getRows() == 0) {
    s << '[' << ']';
    return s;
  }

  s << '[';
  for (size_t i = 0; i < rhs.getRows(); i++) {
    if (i == (rhs.getRows() - 1)) {
      s << rhs[i] << ']';
    }
    else {
      s << rhs[i] << ',' << '\n';
    }
  }
  return s;
}
