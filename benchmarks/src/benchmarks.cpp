#include "benchmark/benchmark.h"
#include "poly.hpp"

#include "polyclasses.hpp"
#include "vtclasses.hpp"

using namespace poly;

template <class T, size_t n = 300000>
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
      new CppDerived<10>(),
      new CppDerived<11>(),
      new CppDerived<12>(),
      new CppDerived<13>(),
      new CppDerived<14>(),
      new CppDerived<15>(),
      new CppDerived<16>(),
      new CppDerived<17>(),
      new CppDerived<18>(),
      new CppDerived<19>(),
      new CppDerived<20>()
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
    reinterpret_cast<Dispatcher*>(new PolyDerived<10>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<11>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<12>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<13>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<14>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<15>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<16>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<17>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<18>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<19>()),
    reinterpret_cast<Dispatcher*>(new PolyDerived<20>())
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
