#include "benchmark/benchmark.h"
#include "poly.hpp"

#include <cassert>

using namespace poly;

__base__ class PolyBase {
  __polymorphic__;
  __dispatch(func_arity5f);
  __dispatch(func_arity3rf);
  __dispatch(func_arity2f);
  __dispatch(func_arity1f);
  __dispatch(func_arity0);
  __dispatch(get_acc);

 public:
  float acc_base = 0;

  float $func_arity5f(float a0, float a1, float a2, float a3, float a4) {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc_base += y;
    return y;
  }

  float $func_arity3rf(float& a0, float& a1, float& a2) {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc_base -= y;
    return y;
  }

  float $func_arity2f(float a0, float a1) {
    auto y = a0 / (a1 + 1);
    acc_base -= y;
    return y;
  }

  float $func_arity1f(float a0) {
    auto y = a0 * 2;
    acc_base -= y;
    return y;
  }

  float $func_arity0() {
    auto y = acc_base / 5;
    acc_base -= y;
    return y;
  }

  float $get_acc() {
    return acc_base;
  }
};

#define PolyBaseCRTP                                                                     \
  PolyBase<PolyChild<1>,                                                                 \
      PolyChild<2>,                                                                      \
      PolyChild<3>,                                                                      \
      PolyChild<4>,                                                                      \
      PolyChild<5>,                                                                      \
      PolyChild<6>,                                                                      \
      PolyChild<7>,                                                                      \
      PolyChild<8>,                                                                      \
      PolyChild<9>,                                                                      \
      PolyChild<10>,                                                                     \
      PolyChild<11>,                                                                     \
      PolyChild<12>,                                                                     \
      PolyChild<13>,                                                                     \
      PolyChild<14>,                                                                     \
      PolyChild<15>,                                                                     \
      PolyChild<16>,                                                                     \
      PolyChild<17>,                                                                     \
      PolyChild<18>,                                                                     \
      PolyChild<19>,                                                                     \
      PolyChild<20>>

template <int x>
class PolyChild;

template <int x>
class PolyChild : public PolyBaseCRTP {
  __implementation(x);

 public:
  float acc_child_a = 0;

  float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc_child_a += y;
    return y;
  }

  float func_arity3rf(float& a0, float& a1, float& a2) {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc_child_a -= y;
    return y;
  }

  float func_arity2f(float a0, float a1) {
    auto y = a0 / (a1 + 1);
    acc_child_a -= y;
    return y;
  }

  float func_arity1f(float a0) {
    auto y = a0 * 2;
    acc_child_a -= y;
    return y;
  }

  float func_arity0() {
    auto y = acc_child_a / 5;
    acc_child_a -= y;
    return y;
  }

  float get_acc() {
    return acc_child_a;
  }
};

class CppBase {
 public:
  float acc_base = 0;

  virtual float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc_base += y;
    return y;
  }

  virtual float func_arity3rf(float& a0, float& a1, float& a2) {
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
class CppChild;

template <int x>
class CppChild : public CppBase {
 public:
  float acc_child_a = 0;

  float func_arity5f(float a0, float a1, float a2, float a3, float a4) override {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc_child_a += y;
    return y;
  }

  float func_arity3rf(float& a0, float& a1, float& a2) override {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc_child_a -= y;
    return y;
  }

  float func_arity2f(float a0, float a1) override {
    auto y = a0 / (a1 + 1);
    acc_child_a -= y;
    return y;
  }

  float func_arity1f(float a0) override {
    auto y = a0 * 2;
    acc_child_a -= y;
    return y;
  }

  float func_arity0() override {
    auto y = acc_child_a / 5;
    acc_child_a -= y;
    return y;
  }

  float get_acc() override {
    return acc_child_a;
  }
};

template <class T, size_t n = 300000>
void call_all_methods_n_times(std::vector<T*>& objects) {
  float x = 5;
  float y = 8;
  float z = 9;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < objects.size(); ++j) {
      objects[j]->func_arity5f(i + 1.0f, i - 1.0f, i - 1.0f, i + 1.0f, i + 1.0f);
      objects[j]->func_arity3rf(x, y, z);
      objects[j]->func_arity2f(i + 1.0f, i + 1.0f);
      objects[j]->func_arity1f(i + 1.0f);
      objects[j]->func_arity0();
    }
  }
}

static void bench_cpp(benchmark::State& state) {
  // clang-format off
  std::vector<CppBase*> objects = {
      new CppBase(),
      new CppChild<1>(),
      new CppChild<2>(),
      new CppChild<3>(),
      new CppChild<4>(),
      new CppChild<5>(),
      new CppChild<6>(),
      new CppChild<7>(),
      new CppChild<8>(),
      new CppChild<9>(),
      new CppChild<10>(),
      new CppChild<11>(),
      new CppChild<12>(),
      new CppChild<13>(),
      new CppChild<14>(),
      new CppChild<15>(),
      new CppChild<16>(),
      new CppChild<17>(),
      new CppChild<18>(),
      new CppChild<19>(),
      new CppChild<20>()
  };
  // clang-format on

  for (auto _ : state) {
    call_all_methods_n_times(objects);
  }

  for (auto obj : objects) {
    delete obj;
  }
}

static void bench_poly(benchmark::State& state) {
  using PolyBase = PolyBaseCRTP;

  // clang-format off
  std::vector<PolyBase*> objects = {
      new PolyBase(),
      new PolyChild<1>(),
      new PolyChild<2>(),
      new PolyChild<3>(),
      new PolyChild<4>(),
      new PolyChild<5>(),
      new PolyChild<6>(),
      new PolyChild<7>(),
      new PolyChild<8>(),
      new PolyChild<9>(),
      new PolyChild<10>(),
      new PolyChild<11>(),
      new PolyChild<12>(),
      new PolyChild<13>(),
      new PolyChild<14>(),
      new PolyChild<15>(),
      new PolyChild<16>(),
      new PolyChild<17>(),
      new PolyChild<18>(),
      new PolyChild<19>(),
      new PolyChild<20>()
  };
  // clang-format on

  for (auto _ : state) {
    call_all_methods_n_times(objects);
  }

  for (auto obj : objects) {
    delete obj;
  }
}

BENCHMARK(bench_poly);
BENCHMARK(bench_cpp);
BENCHMARK_MAIN();
