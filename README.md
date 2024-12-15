# poly

The implementation of polymorphism without vtables

### Benchmark result

Running ./poly-benchmarks\
Run on (16 X 3546.03 MHz CPU s)\
CPU Caches:\
 L1 Data 32 KiB (x8)\
 L1 Instruction 32 KiB (x8)\
 L2 Unified 512 KiB (x8)\
 L3 Unified 16384 KiB (x1)\
 Load Average: 2.38, 1.66, 1.62

| Benchmark               | Time     | CPU      | Iterations |
| ----------------------- | -------- | -------- | ---------- |
| poly_explicit_mean      | 6.89 ms  | 6.88 ms  | 3          |
| poly_explicit_median    | 6.87 ms  | 6.86 ms  | 3          |
| poly_explicit_stddev    | 0.044 ms | 0.046 ms | 3          |
| poly_explicit_cv        | 0.63 %   | 0.66 %   | 3          |
| poly_implicit_mean      | 7.05 ms  | 7.04 ms  | 3          |
| poly_implicit_median    | 7.05 ms  | 7.04 ms  | 3          |
| poly_implicit_stddev    | 0.004 ms | 0.003 ms | 3          |
| poly_implicit_cv        | 0.06 %   | 0.05 %   | 3          |
| poly_known_types_mean   | 1.78 ms  | 1.77 ms  | 3          |
| poly_known_types_median | 1.78 ms  | 1.77 ms  | 3          |
| poly_known_types_stddev | 0.002 ms | 0.001 ms | 3          |
| poly_known_types_cv     | 0.14 %   | 0.07 %   | 3          |
| cpp_mean                | 58.4 ms  | 58.2 ms  | 3          |
| cpp_median              | 58.4 ms  | 58.2 ms  | 3          |
| cpp_stddev              | 0.047 ms | 0.059 ms | 3          |
| cpp_cv                  | 0.08 %   | 0.10 %   | 3          |
| cpp_known_types_mean    | 28.9 ms  | 28.8 ms  | 3          |
| cpp_known_types_median  | 28.9 ms  | 28.8 ms  | 3          |
| cpp_known_types_stddev  | 0.073 ms | 0.058 ms | 3          |
| cpp_known_types_cv      | 0.25 %   | 0.20 %   | 3          |

_(see benchmarks.cpp)_

### Sample

```C++
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
```
