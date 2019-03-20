#include <stdio.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression
{
 public:
  virtual std::string toString() const = 0;

  virtual ~Expression() {}
};

class NumExpression : public Expression
{
 protected:
  long number;

 public:
  NumExpression(long value) : number(value) {}

  virtual std::string toString() const {
    std::stringstream stream;
    stream << number;
    return stream.str();
  }

  virtual ~NumExpression() {}
};

class PlusExpression : public Expression
{
 protected:
  Expression * left;
  Expression * right;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}

  virtual std::string toString() const {
    std::stringstream stream;
    stream << "(" << left->toString() << " + " << right->toString() << ")";
    return stream.str();
  }

  virtual ~PlusExpression() {
    delete left;
    delete right;
  }
};
