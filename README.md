# poly

The implementation of polymorphism without vtables

### Benchmark result

Running ./poly-benchmarks\
Run on (16 X 400 MHz CPU s)\
CPU Caches:\
  L1 Data 32 KiB (x8)\
  L1 Instruction 32 KiB (x8)\
  L2 Unified 512 KiB (x8)\
  L3 Unified 16384 KiB (x1)\
Load Average: 1.19, 1.19, 1.23

|Benchmark            |      Time     |        CPU   |Iterations|
|---------------------|---------------|--------------|----------|
|bench_poly_mean      |   6.25 ms     |    6.24 ms   |         5|
|bench_poly_median    |   6.25 ms     |    6.24 ms   |         5|
|bench_poly_stddev    |  0.007 ms     |   0.006 ms   |         5|
|bench_poly_cv        |   0.12 %      |    0.10 %    |         5|
|bench_cpp_mean       |   58.0 ms     |    57.8 ms   |         5|
|bench_cpp_median     |   58.0 ms     |    57.8 ms   |         5|
|bench_cpp_stddev     |  0.532 ms     |   0.557 ms   |         5|
|bench_cpp_cv         |   0.92 %      |    0.96 %    |         5|

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
