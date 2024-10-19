#include "classes.cpp"
#include "poly.hpp"

#include <vector>

using namespace classes;

auto dispatcher = Dispatcher{};

void case1() {
  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  dispatcher.forward(base).destroy();
  dispatcher.forward(derived_a).destroy();
  dispatcher.forward(derived_b).destroy();
  dispatcher.forward(derived_c).destroy();
}

void case2() {
  const auto base = new Base();
  const auto derived_a = new DerivedA();
  const auto derived_b = new DerivedB();
  const auto derived_c = new DerivedC();

  dispatcher.forward(derived_c).destroy();
  dispatcher.forward(derived_b).destroy();
  dispatcher.forward(derived_a).destroy();
  dispatcher.forward(base).destroy();
}

void case3() {
  std::vector v = {
      dispatcher.forward(new Base()),
      dispatcher.forward(new DerivedA()),
      dispatcher.forward(new DerivedB()),
      dispatcher.forward(new DerivedC()),
  };

  v[0].destroy();
  v[1].destroy();
  v[2].destroy();
  v[3].destroy();
}

void case4() {
  std::vector v = {
      dispatcher.forward(new Base()),
      dispatcher.forward(new DerivedA()),
      dispatcher.forward(new DerivedB()),
      dispatcher.forward(new DerivedC()),
  };

  v[0].destroy();
  v[1].destroy();
  v[2].destroy();
  v[3].destroy();
}

void case5() {
  std::vector v = {
      dispatcher.forward(new Base()),
      dispatcher.forward(new DerivedA()),
      dispatcher.forward(new DerivedB()),
      dispatcher.forward(new DerivedC()),
  };

  for (auto ptr : v) ptr.destroy();
}

void case6() {
  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  Dispatcher::destroy(base);
  Dispatcher::destroy(derived_a);
  Dispatcher::destroy(derived_b);
  Dispatcher::destroy(derived_c);
}

void case7() {
  const auto base = new Base();
  const auto derived_a = new DerivedA();
  const auto derived_b = new DerivedB();
  const auto derived_c = new DerivedC();

  Dispatcher::destroy(derived_c);
  Dispatcher::destroy(derived_b);
  Dispatcher::destroy(derived_a);
  Dispatcher::destroy(base);
}

void case8() {
  std::vector v = {
      dispatcher.forward(new Base()),
      dispatcher.forward(new DerivedA()),
      dispatcher.forward(new DerivedB()),
      dispatcher.forward(new DerivedC()),
  };

  Dispatcher::destroy(v[0]);
  Dispatcher::destroy(v[1]);
  Dispatcher::destroy(v[2]);
  Dispatcher::destroy(v[3]);
}

void case9() {
  std::vector v = {
      dispatcher.forward(new Base()),
      dispatcher.forward(new DerivedA()),
      dispatcher.forward(new DerivedB()),
      dispatcher.forward(new DerivedC()),
  };

  v[0].destroy();
  v[1].destroy();
  v[2].destroy();
  v[3].destroy();
}

void case10() {
  std::vector v = {
      dispatcher.forward(new Base()),
      dispatcher.forward(new DerivedA()),
      dispatcher.forward(new DerivedB()),
      dispatcher.forward(new DerivedC()),
  };

  for (auto ptr : v) ptr.destroy();
}

void case11() {
  std::vector v = {
      Dispatcher::forward(new Base()),
      Dispatcher::forward(new DerivedA()),
      Dispatcher::forward(new DerivedB()),
      Dispatcher::forward(new DerivedC()),
  };

  for (auto ptr : v) ptr.destroy();
}

int main() {
  case1();
  case2();
  case3();
  case4();
  case5();
  case6();
  case7();
  case8();
  case9();
  case10();
}
