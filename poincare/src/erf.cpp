#include <poincare/erf.h>
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
