#ifndef _POLICLASSES_HPP_
#define _POLICLASSES_HPP_

#include "poly/poly.hpp"

class PolyBase {
  POLY_SET_CLASS_ID(0);

 public:
  float acc = 0;

  float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc += y;
    return y;
  }

  float func_arity3f(float& a0, float& a1, float& a2) {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc -= y;
    return y;
  }

  float func_arity2f(float a0, float a1) {
    auto y = a0 / (a1 + 1);
    acc -= y;
    return y;
  }

  float func_arity1f(float a0) {
    auto y = a0 * 2;
    acc -= y;
    return y;
  }

  float func_arity0() {
    auto y = acc / 5;
    acc -= y;
    return y;
  }

  float get_acc() {
    return acc;
  }
};

template <int x>
class PolyDerived : public PolyBase {
  POLY_SET_CLASS_ID(x);

 public:
  float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc += y;
    return y;
  }

  float func_arity3f(float& a0, float& a1, float& a2) {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc -= y;
    return y;
  }

  float func_arity2f(float a0, float a1) {
    auto y = a0 / (a1 + 1);
    acc -= y;
    return y;
  }

  float func_arity1f(float a0) {
    auto y = a0 * 2;
    acc -= y;
    return y;
  }

  float func_arity0() {
    auto y = acc / 5;
    acc -= y;
    return y;
  }

  float get_acc() {
    return acc;
  }
};

POLY_DECL_DISPATCHER(
    Dispatcher,
    {
      POLY_DISPATCH(func_arity5f);
      POLY_DISPATCH(func_arity3f);
      POLY_DISPATCH(func_arity2f);
      POLY_DISPATCH(func_arity1f);
      POLY_DISPATCH(func_arity0);
      POLY_DISPATCH(get_acc);
    },
    PolyBase,
    PolyDerived<1>,
    PolyDerived<2>,
    PolyDerived<3>,
    PolyDerived<4>,
    PolyDerived<5>,
    PolyDerived<6>,
    PolyDerived<7>,
    PolyDerived<8>,
    PolyDerived<9>,
    PolyDerived<10>,
    PolyDerived<11>,
    PolyDerived<12>,
    PolyDerived<13>,
    PolyDerived<14>,
    PolyDerived<15>,
    PolyDerived<16>,
    PolyDerived<17>,
    PolyDerived<18>,
    PolyDerived<19>,
    PolyDerived<20>);

#endif  // _POLYCLASSES_HPP_
