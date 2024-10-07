#include "benchmark/benchmark.h"
#include "poly.hpp"

#include <cassert>

using namespace poly;

class PolyBase {
  __poly_enable();

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
class PolyChild : public PolyBase {
  __poly_enable();

 public:
  float acc_child_a = 0;

  float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc_child_a += y;
    return y;
  }

  float func_arity3f(float& a0, float& a1, float& a2) {
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
class CppChild : public CppBase {
 public:
  float acc_child_a = 0;

  float func_arity5f(float a0, float a1, float a2, float a3, float a4) override {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc_child_a += y;
    return y;
  }

  float func_arity3f(float& a0, float& a1, float& a2) override {
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

template <class T, size_t n = 10000>
void call_all_methods_n_times(std::vector<T*>& objects) {
  float x = 5;
  float y = 8;
  float z = 9;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < objects.size(); ++j) {
      objects[j]->func_arity5f(i + 1.0f, i - 1.0f, i - 1.0f, i + 1.0f, i + 1.0f);
      objects[j]->func_arity3f(x, y, z);
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
      new CppChild<10>()
  };
  // clang-format on

  for (auto _ : state) {
    call_all_methods_n_times(objects);
  }

  for (auto obj : objects) {
    delete obj;
  }
}

__poly_decl_group(Group, {
  __dispatch(func_arity5f);
  __dispatch(func_arity3f);
  __dispatch(func_arity2f);
  __dispatch(func_arity1f);
  __dispatch(func_arity0);
  __dispatch(get_acc);
});

static void bench_poly(benchmark::State& state) {
  // clang-format off
  using group_t = Group<
      PolyBase,
      PolyChild<1>,
      PolyChild<2>,
      PolyChild<3>,
      PolyChild<4>,
      PolyChild<5>,
      PolyChild<6>,
      PolyChild<7>,
      PolyChild<8>,
      PolyChild<9>,
      PolyChild<10>>;

  std::vector<group_t*> objects = {
      static_cast<group_t*>(new PolyBase()),
      static_cast<group_t*>(static_cast<PolyBase*>(new PolyChild<1>())),
      static_cast<group_t*>(static_cast<PolyBase*>(new PolyChild<2>())),
      static_cast<group_t*>(static_cast<PolyBase*>(new PolyChild<3>())),
      static_cast<group_t*>(static_cast<PolyBase*>(new PolyChild<4>())),
      static_cast<group_t*>(static_cast<PolyBase*>(new PolyChild<5>())),
      static_cast<group_t*>(static_cast<PolyBase*>(new PolyChild<6>())),
      static_cast<group_t*>(static_cast<PolyBase*>(new PolyChild<7>())),
      static_cast<group_t*>(static_cast<PolyBase*>(new PolyChild<8>())),
      static_cast<group_t*>(static_cast<PolyBase*>(new PolyChild<9>())),
      static_cast<group_t*>(static_cast<PolyBase*>(new PolyChild<10>()))
  };
  // clang-format on

  for (auto _ : state) {
    call_all_methods_n_times(objects);
  }

  for (auto obj : objects) {
    delete obj;
  }
}

BENCHMARK(bench_cpp);
BENCHMARK(bench_poly);
BENCHMARK_MAIN();
