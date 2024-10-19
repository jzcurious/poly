# poly

The implementation of polymorphism without vtables

### Benchmark result

2024-10-19T13:05:25+07:00\
Running ./poly-benchmarks\
Run on (16 X 3546.03 MHz CPU s)\
CPU Caches:\
 L1 Data 32 KiB (x8)\
 L1 Instruction 32 KiB (x8)\
 L2 Unified 512 KiB (x8)\
 L3 Unified 16384 KiB (x1)\
 Load Average: 2.38, 1.66, 1.62

| Benchmark                  | Time     | CPU      | Iterations |
| -------------------------- | -------- | -------- | ---------- |
| bench_poly_explicit_mean   | 6.98 ms  | 6.94 ms  | 3          |
| bench_poly_explicit_median | 6.98 ms  | 6.93 ms  | 3          |
| bench_poly_explicit_stddev | 0.047 ms | 0.048 ms | 3          |
| bench_poly_explicit_cv     | 0.68 %   | 0.70 %   | 3          |
| bench_poly_implicit_mean   | 8.35 ms  | 8.30 ms  | 3          |
| bench_poly_implicit_median | 8.30 ms  | 8.25 ms  | 3          |
| bench_poly_implicit_stddev | 0.487 ms | 0.478 ms | 3          |
| bench_poly_implicit_cv     | 5.83 %   | 5.76 %   | 3          |
| bench_cpp_mean             | 56.2 ms  | 55.9 ms  | 3          |
| bench_cpp_median           | 56.2 ms  | 55.9 ms  | 3          |
| bench_cpp_stddev           | 0.321 ms | 0.403 ms | 3          |
| bench_cpp_cv               | 0.57 %   | 0.72 %   | 3          |

_(see benchmarks.cpp)_

### Sample

```C++
#include "poly.hpp"
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

  void overrided_function() const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  int partial_overrided_function(int x, int y) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return x * y - val;
  }
};

class DerivedB : public Base {
  __poly_set_class_id(2);

 public:
  void overrided_function() const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

class DerivedC : public Base {
  __poly_set_class_id(3);

 public:
  void overrided_function() const {
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

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}
```
