#ifndef _VTCLASSES_HPP_
#define _VTCLASSES_HPP_

class CppBase {
 public:
  float acc_base = 0;

  virtual float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc_base += y;
    return y;
  }

  virtual float func_arity3f(float& a0, float& a1, float& a2) {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc_base -= y;
    return y;
  }

  virtual float func_arity2f(float a0, float a1) {
    auto y = a0 / (a1 + 1);
    acc_base -= y;
    return y;
  }

  virtual float func_arity1f(float a0) {
    auto y = a0 * 2;
    acc_base -= y;
    return y;
  }

  virtual float func_arity0() {
    auto y = acc_base / 5;
    acc_base -= y;
    return y;
  }

  virtual float get_acc() {
    return acc_base;
  }

  virtual ~CppBase() {}
};

template <int x>
class CppDerived : public CppBase {
 public:
  float acc_Derived_a = 0;

  float func_arity5f(float a0, float a1, float a2, float a3, float a4) override {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc_Derived_a += y;
    return y;
  }

  float func_arity3f(float& a0, float& a1, float& a2) override {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc_Derived_a -= y;
    return y;
  }

  float func_arity2f(float a0, float a1) override {
    auto y = a0 / (a1 + 1);
    acc_Derived_a -= y;
    return y;
  }

  float func_arity1f(float a0) override {
    auto y = a0 * 2;
    acc_Derived_a -= y;
    return y;
  }

  float func_arity0() override {
    auto y = acc_Derived_a / 5;
    acc_Derived_a -= y;
    return y;
  }

  float get_acc() override {
    return acc_Derived_a;
  }
};

#endif  // _VTCLASSES_HPP_
