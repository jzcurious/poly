#include "benchmark/benchmark.h"
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
  float acc_Derived_a = 0;

  float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
    auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
    acc_Derived_a += y;
    return y;
  }

  float func_arity3f(float& a0, float& a1, float& a2) {
    auto y = (a0 + a1 + a2) / (a2 + 1);
    acc_Derived_a -= y;
    return y;
  }

  float func_arity2f(float a0, float a1) {
    auto y = a0 / (a1 + 1);
    acc_Derived_a -= y;
    return y;
  }

  float func_arity1f(float a0) {
    auto y = a0 * 2;
    acc_Derived_a -= y;
    return y;
  }

  float func_arity0() {
    auto y = acc_Derived_a / 5;
    acc_Derived_a -= y;
    return y;
  }

  float get_acc() {
    return acc_Derived_a;
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
    PolyDerived<10>);

template <class T, size_t n = 200000>
void call_all_methods_n_times(std::vector<T*>& objects) {
  float x = 5;
  float y = 8;
  float z = 9;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < objects.size(); ++j) {
      if constexpr (std::is_same_v<T, CppBase>) {
        objects[j]->func_arity5f(i + 1.0f, i - 1.0f, i - 1.0f, i + 1.0f, i + 1.0f);
        objects[j]->func_arity3f(x, y, z);
        objects[j]->func_arity2f(i + 1.0f, i + 1.0f);
        objects[j]->func_arity1f(i + 1.0f);
        objects[j]->func_arity0();
      } else {
        Dispatcher::dispatch_func_arity5f(
            objects[j], i + 1.0f, i - 1.0f, i - 1.0f, i + 1.0f, i + 1.0f);
        Dispatcher::dispatch_func_arity3f(objects[j], x, y, z);
        Dispatcher::dispatch_func_arity2f(objects[j], i + 1.0f, i + 1.0f);
        Dispatcher::dispatch_func_arity1f(objects[j], i + 1.0f);
        Dispatcher::dispatch_func_arity0(objects[j]);
      }
    }
  }
}

static void bench_cpp(benchmark::State& state) {
  // clang-format off
  std::vector<CppBase*> objects = {
      new CppBase(),
      new CppDerived<1>(),
      new CppDerived<2>(),
      new CppDerived<3>(),
      new CppDerived<4>(),
      new CppDerived<5>(),
      new CppDerived<6>(),
      new CppDerived<7>(),
      new CppDerived<8>(),
      new CppDerived<9>(),
      new CppDerived<10>()
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
  // clang-format off

  std::vector<Dispatcher*> objects = {
    reinterpret_cast<Dispatcher*>(new PolyBase()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<1>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<2>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<3>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<4>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<5>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<6>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<7>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<8>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<9>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<10>())
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
