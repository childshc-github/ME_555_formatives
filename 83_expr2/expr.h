#ifndef __EXPR_H__
#define __EXPR_H__

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

// parent class
class Expression {
 public:
  // abstract method
  virtual std::string toString() const = 0;

  // destructor (does nothing)
  virtual ~Expression() {}
};

// subclass of Expression - if only given a number
class NumExpression : public Expression {
  long inum;

 public:
  // constructor
  NumExpression(long number) : inum(number) {}

  // return lone number (any length) w/ stringstream
  // long -> std::string
  virtual std::string toString() const {
    // insert long num
    std::stringstream input_num;
    input_num << inum;

    // convert to std::string
    std::string output;
    input_num >> output;

    // return
    return output;
  }

  // destructor
  virtual ~NumExpression() {}
};

// subclass of Expression - if given arg w/ '+' in it
class PlusExpression : public Expression {
  Expression * E1;
  Expression * E2;

 public:
  // constructor
  PlusExpression(Expression * lhs, Expression * rhs) : E1(lhs), E2(rhs) {}

  // return re-formatted plus nums (no evaluation)
  // Expression * -> std::string
  virtual std::string toString() const {
    // get E1
    std::string E1_num = E1->toString();

    // get E2
    std::string E2_num = E2->toString();

    // combine strings
    std::string output = '(' + E1_num + " + " + E2_num + ')';

    // return
    return output;
  }

  // destructor
  virtual ~PlusExpression() {
    delete E1;
    delete E2;
  }
};

// subclass of Expression - if given arg w/ '-' in it
class MinusExpression : public Expression {
  Expression * E1;
  Expression * E2;

 public:
  // constructor
  MinusExpression(Expression * lhs, Expression * rhs) : E1(lhs), E2(rhs) {}

  // return re-formatted - nums (no evaluation)
  // Expression * -> std::string
  virtual std::string toString() const {
    // get E1
    std::string E1_num = E1->toString();

    // get E2
    std::string E2_num = E2->toString();

    // combine strings
    std::string output = '(' + E1_num + " - " + E2_num + ')';

    // return
    return output;
  }

  // destructor
  virtual ~MinusExpression() {
    delete E1;
    delete E2;
  }
};

// subclass of Expression - if given arg w/ '*' in it
class TimesExpression : public Expression {
  Expression * E1;
  Expression * E2;

 public:
  // constructor
  TimesExpression(Expression * lhs, Expression * rhs) : E1(lhs), E2(rhs) {}

  // return re-formatted - nums (no evaluation)
  // Expression * -> std::string
  virtual std::string toString() const {
    // get E1
    std::string E1_num = E1->toString();

    // get E2
    std::string E2_num = E2->toString();

    // combine strings
    std::string output = '(' + E1_num + " * " + E2_num + ')';

    // return
    return output;
  }

  // destructor
  virtual ~TimesExpression() {
    delete E1;
    delete E2;
  }
};

// subclass of Expression - if given arg w/ '*' in it
class DivExpression : public Expression {
  Expression * E1;
  Expression * E2;

 public:
  // constructor
  DivExpression(Expression * lhs, Expression * rhs) : E1(lhs), E2(rhs) {}

  // return re-formatted - nums (no evaluation)
  // Expression * -> std::string
  virtual std::string toString() const {
    // get E1
    std::string E1_num = E1->toString();

    // get E2
    std::string E2_num = E2->toString();

    // combine strings
    std::string output = '(' + E1_num + " / " + E2_num + ')';

    // return
    return output;
  }

  // destructor
  virtual ~DivExpression() {
    delete E1;
    delete E2;
  }
};
#endif
