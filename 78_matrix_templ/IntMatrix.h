#ifndef __INT_MATRIX_H__
#define __INT_MATRIX_H__

#include <assert.h>

#include <iostream>
#include <vector>

class IntMatrix {
 private:
  // WRITE ME
  int numRows;
  int numColumns;
  std::vector<std::vector<int> > matrix;

 public:
  IntMatrix();
  IntMatrix(size_t r, size_t c);
  IntMatrix(const IntMatrix & rhs);
  ~IntMatrix();
  IntMatrix & operator=(const IntMatrix & rhs);
  size_t getRows() const;
  size_t getColumns() const;
  const std::vector<int> & operator[](size_t index) const;
  std::vector<int> & operator[](size_t index);
  bool operator==(const IntMatrix & rhs) const;
  IntMatrix operator+(const IntMatrix & rhs) const;
};

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs);
std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs);
#endif
