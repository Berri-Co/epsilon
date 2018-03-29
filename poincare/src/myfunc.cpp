#include <poincare/myfunc.h>
#include <poincare/multiplication.h>
#include <poincare/rational.h>
extern "C" {
#include <assert.h>
}
#include <cmath>

namespace Poincare {

Expression::Type MyFunc::type() const {
  return Type::MyFunc;
}

Expression * MyFunc::clone() const {
  MyFunc * a = new MyFunc(m_operands, true);
  return a;
}

Expression * MyFunc::shallowReduce(Context& context, AngleUnit angleUnit) {
  Expression * e = Expression::shallowReduce(context, angleUnit);
  if (e != this) {
    return e;
  }

  // Get the two operands
  const Expression * op0 = operand(0);
  const Expression * op1 = operand(1);

  // Detach them
  detachOperand(op0);
  detachOperand(op1);

  // Create a new multiplication
#if 0
  /*
    DynamicHierarchy(const Expression * operand1, const Expression * operand2, bool cloneOperands = true)
  */
  Multiplication * m0 = new Multiplication(op0, op1, false);
  Multiplication * m = new Multiplication(m0, new Rational(2), false);
#else
  /*
    DynamicHierarchy(const Expression * const * operands, int numberOfOperands, bool cloneOperands = true) 
  */
  const Expression * const mops[3] = { op0, op1, new Rational(2) };
  Multiplication * m = new Multiplication(mops, 3, false);
#endif

  // Simplify
  replaceWith(m, true);
  return m->shallowReduce(context, angleUnit);
}

}
