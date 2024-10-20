#include "benchmark/benchmark.h"
#include "poly.hpp"

#include "polyclasses.hpp"
#include "vtclasses.hpp"

using namespace poly;

const size_t n = 300000;
float f = 0;

static void cpp(benchmark::State& state) {
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

  float c = 0;

  for (auto obj : objects) {
    c += obj->get_acc();
    delete obj;
  }

  f = c;
}

static void cpp_known_types(benchmark::State& state) {
  auto obj0 = new CppBase();
  auto obj1 = new CppDerived<1>();
  auto obj2 = new CppDerived<2>();
  auto obj3 = new CppDerived<3>();
  auto obj4 = new CppDerived<4>();
  auto obj5 = new CppDerived<5>();
  auto obj6 = new CppDerived<6>();
  auto obj7 = new CppDerived<7>();
  auto obj8 = new CppDerived<8>();
  auto obj9 = new CppDerived<9>();
  auto obj10 = new CppDerived<10>();
  auto obj11 = new CppDerived<11>();
  auto obj12 = new CppDerived<12>();
  auto obj13 = new CppDerived<13>();
  auto obj14 = new CppDerived<14>();
  auto obj15 = new CppDerived<15>();
  auto obj16 = new CppDerived<16>();
  auto obj17 = new CppDerived<17>();
  auto obj18 = new CppDerived<18>();
  auto obj19 = new CppDerived<19>();
  auto obj20 = new CppDerived<20>();

  float x = 5;
  float y = 8;
  float z = 9;

#define __call_snippet(_j)                                                               \
  obj##_j->func_arity5f(i + 1.0f, i - 1.0f, i - 1.0f, i + 1.0f, i + 1.0f);               \
  obj##_j->func_arity3f(x, y, z);                                                        \
  obj##_j->func_arity2f(i + 1.0f, i + 1.0f);                                             \
  obj##_j->func_arity1f(i + 1.0f);                                                       \
  obj##_j->func_arity0();

  for (auto _ : state) {
    for (size_t i = 0; i < n; ++i) {
      __call_snippet(0);
      __call_snippet(1);
      __call_snippet(2);
      __call_snippet(3);
      __call_snippet(4);
      __call_snippet(5);
      __call_snippet(6);
      __call_snippet(7);
      __call_snippet(8);
      __call_snippet(9);
      __call_snippet(10);
      __call_snippet(11);
      __call_snippet(12);
      __call_snippet(13);
      __call_snippet(14);
      __call_snippet(15);
      __call_snippet(16);
      __call_snippet(17);
      __call_snippet(18);
      __call_snippet(19);
      __call_snippet(20);
    }
  }

#undef __call_snippet

  float c = 0;

  c += obj0->get_acc();
  c += obj1->get_acc();
  c += obj2->get_acc();
  c += obj3->get_acc();
  c += obj4->get_acc();
  c += obj5->get_acc();
  c += obj6->get_acc();
  c += obj7->get_acc();
  c += obj8->get_acc();
  c += obj9->get_acc();
  c += obj10->get_acc();
  c += obj11->get_acc();
  c += obj12->get_acc();
  c += obj13->get_acc();
  c += obj14->get_acc();
  c += obj15->get_acc();
  c += obj16->get_acc();
  c += obj17->get_acc();
  c += obj18->get_acc();
  c += obj19->get_acc();
  c += obj20->get_acc();

  f = c;

  delete obj0;
  delete obj1;
  delete obj2;
  delete obj3;
  delete obj4;
  delete obj5;
  delete obj6;
  delete obj7;
  delete obj8;
  delete obj9;
  delete obj10;
  delete obj11;
  delete obj12;
  delete obj13;
  delete obj14;
  delete obj15;
  delete obj16;
  delete obj17;
  delete obj18;
  delete obj19;
  delete obj20;
}

static void poly_implicit(benchmark::State& state) {
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

  float c = 0;

  for (auto obj : objects) {
    c += obj.get_acc();
    obj.destroy();
  }

  f = c;
}

static void poly_explicit(benchmark::State& state) {
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

  float c = 0;

  for (auto obj : objects) {
    c += dispatcher.forward(obj).get_acc();
    dispatcher.forward(obj).destroy();
  }

  f = c;
}

static void poly_known_types(benchmark::State& state) {
  auto obj0 = new PolyBase();
  auto obj1 = new PolyDerived<1>();
  auto obj2 = new PolyDerived<2>();
  auto obj3 = new PolyDerived<3>();
  auto obj4 = new PolyDerived<4>();
  auto obj5 = new PolyDerived<5>();
  auto obj6 = new PolyDerived<6>();
  auto obj7 = new PolyDerived<7>();
  auto obj8 = new PolyDerived<8>();
  auto obj9 = new PolyDerived<9>();
  auto obj10 = new PolyDerived<10>();
  auto obj11 = new PolyDerived<11>();
  auto obj12 = new PolyDerived<12>();
  auto obj13 = new PolyDerived<13>();
  auto obj14 = new PolyDerived<14>();
  auto obj15 = new PolyDerived<15>();
  auto obj16 = new PolyDerived<16>();
  auto obj17 = new PolyDerived<17>();
  auto obj18 = new PolyDerived<18>();
  auto obj19 = new PolyDerived<19>();
  auto obj20 = new PolyDerived<20>();

  float x = 5;
  float y = 8;
  float z = 9;

#define __call_snippet(_j)                                                               \
  Dispatcher::dispatch_func_arity5f(                                                     \
      obj##_j, i + 1.0f, i - 1.0f, i - 1.0f, i + 1.0f, i + 1.0f);                        \
  Dispatcher::dispatch_func_arity3f(obj##_j, x, y, z);                                   \
  Dispatcher::dispatch_func_arity2f(obj##_j, i + 1.0f, i + 1.0f);                        \
  Dispatcher::dispatch_func_arity1f(obj##_j, i + 1.0f);                                  \
  Dispatcher::dispatch_func_arity0(obj##_j);

  for (auto _ : state) {
    for (size_t i = 0; i < n; ++i) {
      __call_snippet(0);
      __call_snippet(1);
      __call_snippet(2);
      __call_snippet(3);
      __call_snippet(4);
      __call_snippet(5);
      __call_snippet(6);
      __call_snippet(7);
      __call_snippet(8);
      __call_snippet(9);
      __call_snippet(10);
      __call_snippet(11);
      __call_snippet(12);
      __call_snippet(13);
      __call_snippet(14);
      __call_snippet(15);
      __call_snippet(16);
      __call_snippet(17);
      __call_snippet(18);
      __call_snippet(19);
      __call_snippet(20);
    }
  }

#undef __call_snippet

  float c = 0;

  c += obj0->get_acc();
  c += obj1->get_acc();
  c += obj2->get_acc();
  c += obj3->get_acc();
  c += obj4->get_acc();
  c += obj5->get_acc();
  c += obj6->get_acc();
  c += obj7->get_acc();
  c += obj8->get_acc();
  c += obj9->get_acc();
  c += obj10->get_acc();
  c += obj11->get_acc();
  c += obj12->get_acc();
  c += obj13->get_acc();
  c += obj14->get_acc();
  c += obj15->get_acc();
  c += obj16->get_acc();
  c += obj17->get_acc();
  c += obj18->get_acc();
  c += obj19->get_acc();
  c += obj20->get_acc();

  f = c;

  delete obj0;
  delete obj1;
  delete obj2;
  delete obj3;
  delete obj4;
  delete obj5;
  delete obj6;
  delete obj7;
  delete obj8;
  delete obj9;
  delete obj10;
  delete obj11;
  delete obj12;
  delete obj13;
  delete obj14;
  delete obj15;
  delete obj16;
  delete obj17;
  delete obj18;
  delete obj19;
  delete obj20;
}

BENCHMARK(poly_explicit);
BENCHMARK(poly_implicit);
BENCHMARK(poly_known_types);
BENCHMARK(cpp);
BENCHMARK(cpp_known_types);
BENCHMARK_MAIN();
