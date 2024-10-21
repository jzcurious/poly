#ifndef _VTCLASSES_HPP_
#define _VTCLASSES_HPP_

class CppBase {
 public:
  float acc = 0;

  virtual float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc += y;
    return y;
  }

  virtual float func_arity3f(float& a0, float& a1, float& a2) {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc -= y;
    return y;
  }

  virtual float func_arity2f(float a0, float a1) {
    auto y = a0 / (a1 + 1);
    acc -= y;
    return y;
  }

  virtual float func_arity1f(float a0) {
    auto y = a0 * 2;
    acc -= y;
    return y;
  }

  virtual float func_arity0() {
    auto y = acc / 5;
    acc -= y;
    return y;
  }

  virtual float get_acc() {
    return acc;
  }

  virtual ~CppBase() {}
};

template <int x>
class CppDerived : public CppBase {
 public:
  float func_arity5f(float a0, float a1, float a2, float a3, float a4) override {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc += y;
    return y;
  }

  float func_arity3f(float& a0, float& a1, float& a2) override {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc -= y;
    return y;
  }

  float func_arity2f(float a0, float a1) override {
    auto y = a0 / (a1 + 1);
    acc -= y;
    return y;
  }

  float func_arity1f(float a0) override {
    auto y = a0 * 2;
    acc -= y;
    return y;
  }

  float func_arity0() override {
    auto y = acc / 5;
    acc -= y;
    return y;
  }
};

#endif  // _VTCLASSES_HPP_
