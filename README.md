# poly
The implementation of polymorphism without vtables

### Benchmark result

##### g++ 13.2.1

|             | Time                                  |
| ----------- | --------------------------------------|
| Poly        | 2910.50998ms (total), 0.00003ms (avg) |
| CPP vtable  | 17413.49896ms (total), 0.00017ms (avg)|
| Speedup     | 5.983                                 |


##### clang++ 16.0.6

|             | Time                                  |
| ----------- | --------------------------------------|
| Poly        | 4117.48131ms (total), 0.00004ms (avg) |
| CPP vtable  | 16876.41915ms (total), 0.00017ms (avg)|
| Speedup     | 4.099                                 |


*(see benchmark.cpp)*

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

    __interface(mul, float, int a, int b);
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