#include "poly/poly.hpp"
#include <iostream>

class Base {
  __poly_set_class_id(0);

 public:
  int val = 8;

  void overrided_function() const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  float not_overrided_function(float x) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return val + x + 1;
  }

  int partial_overrided_function(int x, int y) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return val + x + y;
  }
};

class DerivedA : public Base {
  __poly_set_class_id(1);

 public:
  int y = 3;

  void overrided_function() const poly_override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  int partial_overrided_function(int x, int y) poly_override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return x * y - val;
  }
};

class DerivedB : public Base {
  __poly_set_class_id(2);

 public:
  void overrided_function() const poly_override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

class DerivedC : public Base {
  __poly_set_class_id(3);

 public:
  void overrided_function() const poly_override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

__poly_decl_dispatcher(
    Dispatcher,
    {
      __poly_dispatch(overrided_function);
      __poly_dispatch(not_overrided_function);
      __poly_dispatch(partial_overrided_function);
    },
    Base,
    DerivedA,
    DerivedB,
    DerivedC);

int main() {
  auto dispatcher = Dispatcher{};

  auto base = new Base();
  auto derived_a = reinterpret_cast<Base*>(new DerivedA());
  auto derived_b = reinterpret_cast<Base*>(new DerivedB());
  auto derived_c = reinterpret_cast<Base*>(new DerivedC());

  dispatcher.dispatch_overrided_function(base);
  dispatcher.forward(derived_a).overrided_function();
  dispatcher.dispatch_overrided_function(derived_b);
  dispatcher.dispatch_overrided_function(derived_c);

  dispatcher.dispatch_not_overrided_function(base, 1);
  dispatcher.dispatch_not_overrided_function(derived_a, 10);
  dispatcher.forward(derived_b).not_overrided_function(10);
  dispatcher.dispatch_not_overrided_function(derived_c, 101);

  dispatcher.dispatch_partial_overrided_function(base, 1, 2);
  dispatcher.dispatch_partial_overrided_function(derived_a, 10, 15);
  dispatcher.dispatch_partial_overrided_function(derived_b, 101, 4);
  dispatcher.forward(derived_c).partial_overrided_function(10, 8);

  dispatcher.destroy(base);
  dispatcher.destroy(derived_a);
  dispatcher.destroy(derived_b);
  dispatcher.destroy(derived_c);
}
