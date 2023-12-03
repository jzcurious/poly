#include <iostream>
#include <vector>
#include "poly.hpp"

using namespace poly;

class ChildA;
class ChildB;
class ChildC;


template<class... Derived>
class Base {
    __polymorphic__
    __dispatch(echo_tag)
    __dispatch(div)
    __dispatch(repeat)
    __dispatch(mul)

private:
    void $echo_tag() {
        std::cout << __FUNCTION__ <<  std::endl;
    }

    float $div(int a, int b) {
        std::cout << __FUNCTION__ << std::endl;
        return a / b;
    }

    std::vector<int> $repeat(int a) {
        std::cout << __FUNCTION__ << std::endl;
        auto a_ = static_cast<int>(a);
        return { a_, a_ };
    }

    __interface(mul, float, int a, int b)
};


class ChildA : public Base<ChildA, ChildB, ChildC> {
public:
    __implementation__

    void echo_tag(int i) {
        std::cout << __PRETTY_FUNCTION__ << i << std::endl;
    }

    void echo_tag() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    void echo_tag(float i) {
        std::cout << __PRETTY_FUNCTION__ << i << std::endl;
    }

    float div(int a, int b) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return a / b;
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


class ChildB : public Base<ChildA, ChildB, ChildC> {
public:
    __implementation__

    void echo_tag() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    float div(int a, int b) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return static_cast<float>(a) / b;
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


class ChildC : public Base<ChildA, ChildB, ChildC> {
public:
    __implementation__

    void echo_tag() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    float div(int a, int b) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return static_cast<double>(a) / b;
    }

    std::vector<int> repeat(int a) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return { a, a, a, a, a };
    }

    float mul(int a, int b) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return a * b;
    }
};


int main() {
    using Base = Base<ChildA, ChildB, ChildC>;

    auto base = new Base();
    auto child_a = new ChildA();
    auto child_b = new ChildB();
    auto child_c = new ChildC();

    std::vector<Base*> pack = {
        base,
        (static_cast<Base*>(child_a)),
        (static_cast<Base*>(child_c)),
        (static_cast<Base*>(child_b))
    };

    for (auto obj : pack) {
        obj->echo_tag();
    }
    child_a->echo_tag(111);
    std::cout << std::endl;

    for (auto obj : pack) {
        std::cout << obj->div(111, 222) << std::endl;
    }
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
    std::cout << pack[3]->mul(111, 222) << std::endl;

    std::cout << pack[0]->mul(111, 222) << std::endl;

    return 0;
}