#ifndef _POLICLASSES_HPP_
#define _POLICLASSES_HPP_

#include "poly.hpp"

using namespace poly;

class PolyBase {
  __poly_set_class_id(0);

 public:
  float acc_base = 0;

  float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc_base += y;
    return y;
  }

  float func_arity3f(float& a0, float& a1, float& a2) {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc_base -= y;
    return y;
  }

  float func_arity2f(float a0, float a1) {
    auto y = a0 / (a1 + 1);
    acc_base -= y;
    return y;
  }

  float func_arity1f(float a0) {
    auto y = a0 * 2;
    acc_base -= y;
    return y;
  }

  float func_arity0() {
    auto y = acc_base / 5;
    acc_base -= y;
    return y;
  }

  float get_acc() {
    return acc_base;
  }
};

template <int x>
class PolyDerived : public PolyBase {
  __poly_set_class_id(x);

 public:
  float acc_derived = 0;

  float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc_derived += y;
    return y;
  }

  float func_arity3f(float& a0, float& a1, float& a2) {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc_derived -= y;
    return y;
  }

  float func_arity2f(float a0, float a1) {
    auto y = a0 / (a1 + 1);
    acc_derived -= y;
    return y;
  }

  float func_arity1f(float a0) {
    auto y = a0 * 2;
    acc_derived -= y;
    return y;
  }

  float func_arity0() {
    auto y = acc_derived / 5;
    acc_derived -= y;
    return y;
  }

  float get_acc() {
    return acc_derived;
  }
};

__poly_decl_dispatcher(
    Dispatcher,
    {
      __poly_dispatch(func_arity5f);
      __poly_dispatch(func_arity3f);
      __poly_dispatch(func_arity2f);
      __poly_dispatch(func_arity1f);
      __poly_dispatch(func_arity0);
      __poly_dispatch(get_acc);
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
