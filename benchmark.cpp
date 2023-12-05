#include <chrono>
#include <functional>
#include <iostream>
#include "poly.hpp"

using namespace poly;

class PolyChildA;
class PolyChildB;
class PolyChildC;

__base class PolyBase {
    __polymorphic__
        __dispatch(mul_arity5)
public:
    float $mul_arity5(float a0, float a1, float a2, float a3, float a4) {
        return a0 * a1 * a2 * a3 * a4;
    }
};

class PolyChildA : public PolyBase<PolyChildA, PolyChildB, PolyChildC> {
    __implementation__
public:
    float mul_arity5(float a0, float a1, float a2, float a3, float a4) {
        return a0 * a1 * a2 * a3 * a4;
    }
};

class PolyChildB : public PolyBase<PolyChildA, PolyChildB, PolyChildC> {
    __implementation__
public:
    float mul_arity5(float a0, float a1, float a2, float a3, float a4) {
        return a0 * a1 * a2 * a3 * a4;
    }
};

class PolyChildC : public PolyBase<PolyChildA, PolyChildB, PolyChildC> {
    __implementation__
public:
    float mul_arity5(float a0, float a1, float a2, float a3, float a4) {
        return a0 * a1 * a2 * a3 * a4;
    }
};


class CppBase {
public:
    virtual float mul_arity5(float a0, float a1, float a2, float a3, float a4) {
        return a0 * a1 * a2 * a3 * a4;
    }
};

class CppChildA : public CppBase {
public:
    float mul_arity5(float a0, float a1, float a2, float a3, float a4) override {
        return a0 * a1 * a2 * a3 * a4;
    }
};

class CppChildB : public CppBase {
public:
    float mul_arity5(float a0, float a1, float a2, float a3, float a4) override {
        return a0 * a1 * a2 * a3 * a4;
    }
};

class CppChildC : public CppBase {
public:
    float mul_arity5(float a0, float a1, float a2, float a3, float a4) override {
        return a0 * a1 * a2 * a3 * a4;
    }
};


void run_poly(int N) {
    using PolyBase = PolyBase<PolyChildA, PolyChildB, PolyChildC>;

    auto poly_base = new PolyBase();
    auto poly_child_a = new PolyChildA();
    auto poly_child_b = new PolyChildB();
    auto poly_child_c = new PolyChildC();

    std::vector<PolyBase*> pack = {
        poly_base,
        (static_cast<PolyBase*>(poly_child_a)),
        (static_cast<PolyBase*>(poly_child_c)),
        (static_cast<PolyBase*>(poly_child_b))
    };

    for (int i = 0; i < N; ++i) {
        for (auto obj : pack) {
            obj->mul_arity5(i + 0, i + 1, i + 2, i + 3, i + 4);
        }
    }
}


void run_cpp(int N) {
    auto cpp_base = new CppBase();
    auto cpp_child_a = new CppChildA();
    auto cpp_child_b = new CppChildB();
    auto cpp_child_c = new CppChildC();

    std::vector<CppBase*> pack = {
        cpp_base,
        (static_cast<CppBase*>(cpp_child_a)),
        (static_cast<CppBase*>(cpp_child_c)),
        (static_cast<CppBase*>(cpp_child_b))
    };

    for (int i = 0; i < N; ++i) {
        for (auto obj : pack) {
            obj->mul_arity5(i + 0, i + 1, i + 2, i + 3, i + 4);
        }
    }
}

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;


template<class F>
double timeit(F f) {
    auto t1 = high_resolution_clock::now();
    f();
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    return ms_double.count();
}


int main() {
    int N = 100000000;
    
    auto t1 = timeit(std::bind_front(run_cpp, N));
    std::cout << "CPP: " << t1 << "ms" << std::endl;

    auto t2 = timeit(std::bind_front(run_poly, N));
    std::cout << "Poly: " << t2 << "ms" << std::endl;

    std::cout << "CPP / Poly = " << (float)t1 / (float)t2 << std::endl;
}