#include "benchmark/benchmark.h"
#include "poly.hpp"

#include "polyclasses.hpp"
#include "vtclasses.hpp"

using namespace poly;

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

  float x = 5;
  float y = 8;
  float z = 9;
  const size_t n = 300000;

  for (auto _ : state) {
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

  for (auto obj : objects) {
    delete obj;
  }
}

static void bench_poly_implicit(benchmark::State& state) {
  auto dispatcher = Dispatcher{};

  // clang-format off
  std::vector objects = {
    dispatcher.forward(new PolyBase()),
    dispatcher.forward(new PolyDerived<1>()),
    dispatcher.forward(new PolyDerived<2>()),
    dispatcher.forward(new PolyDerived<3>()),
    dispatcher.forward(new PolyDerived<4>()),
    dispatcher.forward(new PolyDerived<5>()),
    dispatcher.forward(new PolyDerived<6>()),
    dispatcher.forward(new PolyDerived<7>()),
    dispatcher.forward(new PolyDerived<8>()),
    dispatcher.forward(new PolyDerived<9>()),
    dispatcher.forward(new PolyDerived<10>()),
    dispatcher.forward(new PolyDerived<11>()),
    dispatcher.forward(new PolyDerived<12>()),
    dispatcher.forward(new PolyDerived<13>()),
    dispatcher.forward(new PolyDerived<14>()),
    dispatcher.forward(new PolyDerived<15>()),
    dispatcher.forward(new PolyDerived<16>()),
    dispatcher.forward(new PolyDerived<17>()),
    dispatcher.forward(new PolyDerived<18>()),
    dispatcher.forward(new PolyDerived<19>()),
    dispatcher.forward(new PolyDerived<20>())
  };
  // clang-format on

  float x = 5;
  float y = 8;
  float z = 9;
  const size_t n = 300000;

  for (auto _ : state) {
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < objects.size(); ++j) {
        objects[j].func_arity5f(i + 1.0f, i - 1.0f, i - 1.0f, i + 1.0f, i + 1.0f);
        objects[j].func_arity3f(x, y, z);
        objects[j].func_arity2f(i + 1.0f, i + 1.0f);
        objects[j].func_arity1f(i + 1.0f);
        objects[j].func_arity0();
      }
    }
  }

  for (auto obj : objects) {
    obj.destroy();
  }
}

static void bench_poly_explicit(benchmark::State& state) {
  auto dispatcher = Dispatcher{};

  // clang-format off
  std::vector<PolyBase*> objects = {
    new PolyBase(),
    new PolyDerived<1>(),
    new PolyDerived<2>(),
    new PolyDerived<3>(),
    new PolyDerived<4>(),
    new PolyDerived<5>(),
    new PolyDerived<6>(),
    new PolyDerived<7>(),
    new PolyDerived<8>(),
    new PolyDerived<9>(),
    new PolyDerived<10>(),
    new PolyDerived<11>(),
    new PolyDerived<12>(),
    new PolyDerived<13>(),
    new PolyDerived<14>(),
    new PolyDerived<15>(),
    new PolyDerived<16>(),
    new PolyDerived<17>(),
    new PolyDerived<18>(),
    new PolyDerived<19>(),
    new PolyDerived<20>()
  };
  // clang-format on

  float x = 5;
  float y = 8;
  float z = 9;
  const size_t n = 300000;

  for (auto _ : state) {
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < objects.size(); ++j) {
        dispatcher.dispatch_func_arity5f(
            objects[j], i + 1.0f, i - 1.0f, i - 1.0f, i + 1.0f, i + 1.0f);
        dispatcher.dispatch_func_arity3f(objects[j], x, y, z);
        dispatcher.dispatch_func_arity2f(objects[j], i + 1.0f, i + 1.0f);
        dispatcher.dispatch_func_arity1f(objects[j], i + 1.0f);
        dispatcher.dispatch_func_arity0(objects[j]);
      }
    }
  }

  for (auto obj : objects) {
    dispatcher.forward(obj).destroy();
  }
}

BENCHMARK(bench_poly_explicit);
BENCHMARK(bench_poly_implicit);
BENCHMARK(bench_cpp);
BENCHMARK_MAIN();
