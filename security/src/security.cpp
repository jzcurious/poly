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

  dispatcher.forward(base)->destroy();
  dispatcher.forward(derived_a)->destroy();
  dispatcher.forward(derived_b)->destroy();
  dispatcher.forward(derived_c)->destroy();
}

void case2() {
  const auto base = new Base();
  const auto derived_a = new DerivedA();
  const auto derived_b = new DerivedB();
  const auto derived_c = new DerivedC();

  dispatcher.forward(base)->destroy();
  dispatcher.forward(derived_a)->destroy();
  dispatcher.forward(derived_b)->destroy();
  dispatcher.forward(derived_c)->destroy();
}

void case3() {
  std::vector v = {
      dispatcher.forward(new Base()),
      dispatcher.forward(new DerivedA()),
      dispatcher.forward(new DerivedB()),
      dispatcher.forward(new DerivedC()),
  };

  auto ptr = v[0];
  ptr->destroy();

  ptr = v[1];
  ptr->destroy();

  ptr = v[2];
  ptr->destroy();

  ptr = v[3];
  ptr->destroy();
}

void case4() {
  std::vector v = {
      dispatcher.forward(new Base()),
      dispatcher.forward(new DerivedA()),
      dispatcher.forward(new DerivedB()),
      dispatcher.forward(new DerivedC()),
  };

  v[0]->destroy();
  v[1]->destroy();
  v[2]->destroy();
  v[3]->destroy();
}

void case5() {
  std::vector v = {
      dispatcher.forward(new Base()),
      dispatcher.forward(new DerivedA()),
      dispatcher.forward(new DerivedB()),
      dispatcher.forward(new DerivedC()),
  };

  for (auto ptr : v) ptr->destroy();
}

int main() {
  case1();
  case2();
  // case3();
  // case4();
  // case5();
}
