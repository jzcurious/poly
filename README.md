# poly

The implementation of polymorphism without vtables

### Benchmark result

Running ./poly-benchmarks \
Run on (4 X 2500.02 MHz CPU s) \
CPU Caches: \
L1 Data 32 KiB (x2) \
L1 Instruction 32 KiB (x2) \
L2 Unified 256 KiB (x2) \
L3 Unified 3072 KiB (x1) \
Load Average: 1.05, 2.01, 2.81\

| Benchmark         | Time       | CPU        | Iterations |
| ----------------- | ---------- | ---------- | ---------- |
| bench_poly_mean   | 351706 ns  | 350561 ns  | 3          |
| bench_poly_median | 344905 ns  | 344058 ns  | 3          |
| bench_poly_stddev | 18261 ns   | 18090 ns   | 3          |
| bench_poly_cv     | 5.19 %     | 5.16 %     | 3          |
| bench_cpp_mean    | 1802176 ns | 1796015 ns | 3          |
| bench_cpp_median  | 1802405 ns | 1795599 ns | 3          |
| bench_cpp_stddev  | 488 ns     | 824 ns     | 3          |
| bench_cpp_cv      | 0.03 %     | 0.05 %     | 3          |

_(see benchmarks.cpp)_

### Sample

```C++
#include "poly.hpp"
#include <iostream>
#include <vector>

using namespace poly;

class ChildA;
class ChildB;

__base__ class Base {
    __polymorphic__;
    __dispatch(echo_tag);
    __dispatch(repeat);
    __dispatch(mul);

public:
    void $echo_tag() {
        std::cout << __FUNCTION__ << std::endl;
    }

    std::vector<int> $repeat(int a) {
        std::cout << __FUNCTION__ << std::endl;
        auto a_ = static_cast<int>(a);
        return { a_, a_ };
    }

    __abstract(mul, float, int a, int b);
};

class ChildA : public Base<ChildA, ChildB> {
    __implementation__;

public:
    void echo_tag() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    void echo_tag(float i) {
        std::cout << __PRETTY_FUNCTION__ << i << std::endl;
    }

    std::vector<int> repeat(int a) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return { a, a, a };
    }

    float mul(int a, int b) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return a * b;
    }
};

class ChildB : public Base<ChildA, ChildB> {
    __implementation__;

public:
    void echo_tag() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    std::vector<int> repeat(int a) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return { a, a, a, a };
    }

    float mul(int a, int b) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return a * b;
    }
};

int main() {
    using Base = Base<ChildA, ChildB>;

    auto base = new Base();
    auto child_a = new ChildA();
    auto child_b = new ChildB();

    std::vector<Base*> pack = {
        base,
        (static_cast<Base*>(child_a)),
        (static_cast<Base*>(child_b)),
    };

    for (auto obj : pack) {
        obj->echo_tag();
    }
    child_a->echo_tag(111);
    std::cout << std::endl;

    for (unsigned i = 0; i < pack.size(); ++i) {
        auto v = pack[i]->repeat(i);
        for (auto a : v)
            std::cout << a << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << pack[1]->mul(111, 222) << std::endl;
    std::cout << pack[2]->mul(111, 222) << std::endl;

    std::cout << std::endl << pack[0]->mul(111, 222) << std::endl;

    return 0;
}
```
