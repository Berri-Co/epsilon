#include <poincare/erf.h>
#include <poincare/multiplication.h>
#include <poincare/division.h>
#include <poincare/opposite.h>
#include <poincare/integral.h>
#include <poincare/power.h>
#include <poincare/rational.h>
#include <poincare/complex.h>
extern "C" {
#include <assert.h>
}
#include <cmath>

namespace Poincare {

Expression::Type Erf::type() const {
  return Type::Erf;
}

Expression * Erf::clone() const {
  Erf * a = new Erf(m_operands, true);
  return a;
}

Expression * Erf::shallowReduce(Context& context, AngleUnit angleUnit) {
#if ERF_INTEGRAL
  Expression * e = Expression::shallowReduce(context, angleUnit);
  if (e != this) {
    return e;
  }

  const Expression * x = operand(0);
  detachOperand(x);

  Power * fx = new Power(
    new Complex<double>(Complex<double>::Float(M_E)),
    new Opposite(
      new Power(new Symbol('x'), new Rational(2), false),
      false
    ),
    false
  );

  const Expression * const iops[3] = { fx, new Rational(0), x };
  Integral * i = new Integral(iops, false);

  Division * co = new Division(
    new Rational(2),
    new SquareRoot(
      new Complex<double>(Complex<double>::Float(M_PI)),
      false
    ),
    false
  );

  Multiplication * m = new Multiplication(co, i, false);

  replaceWith(m, true);
  return m->shallowReduce(context, angleUnit);
#else
  return this;
#endif
}

template<typename T>
Complex<T> Erf::computeOnComplex(const Complex<T> c, AngleUnit angleUnit) {
  T n = c.a();
  if (c.b() != 0 || std::isnan(n)) {
    // No imaginary part
    return Complex<T>::Float(NAN);
  }

  T result = erf(n);
  return Complex<T>::Float(result);
}

}
