#ifndef POINCARE_MYFUNC_H
#define POINCARE_MYFUNC_H

#include <poincare.h>
#include <poincare/static_hierarchy.h>
#include <poincare/dynamic_hierarchy.h>
#include <poincare/layout_engine.h>
#include <poincare/complex.h>

namespace Poincare {

// myfunc(x, y) = 2 * x * y
class MyFunc : public StaticHierarchy<2> {
  using StaticHierarchy<2>::StaticHierarchy;
public:
  Type type() const override;
  Expression * clone() const override;
private:
  /* Layout */
  ExpressionLayout * privateCreateLayout(PrintFloat::Mode floatDisplayMode, ComplexFormat complexFormat) const override {
    return LayoutEngine::createPrefixLayout(this, floatDisplayMode, complexFormat, name());
  }
  int writeTextInBuffer(char * buffer, int bufferSize, int numberOfSignificantDigits = PrintFloat::k_numberOfStoredSignificantDigits) const override {
    return LayoutEngine::writePrefixExpressionTextInBuffer(this, buffer, bufferSize, numberOfSignificantDigits, name());
  }
  const char * name() const { return "myfunc"; }
  /* Simplication */
  Expression * shallowReduce(Context& context, AngleUnit angleUnit) override;
  /* Evaluation */
  Expression * privateApproximate(SinglePrecision p, Context& context, AngleUnit angleUnit) const override {
    return templatedApproximate<float>(context, angleUnit);
  }
  Expression * privateApproximate(DoublePrecision p, Context& context, AngleUnit angleUnit) const override {
    return templatedApproximate<double>(context, angleUnit);
  }
  template<typename T> Expression * templatedApproximate(Context& context, AngleUnit angleUnit) const {
    return new Complex<T>(Complex<T>::Float(NAN));
  }
};

}

#endif
