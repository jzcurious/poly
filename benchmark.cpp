#include "poly.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <format>
#include <functional>
#include <iostream>
#include <random>
#include <unistd.h>

using namespace poly;

class PolyChildA;
class PolyChildB;
class PolyChildC;
class PolyChildD;

__base__ class PolyBase {
    __polymorphic__;
    __dispatch(sum_arity5);
    __dispatch(mul_arity3);
    __dispatch(echo_acc);
    __dispatch(get_acc);

public:
    long acc_base = 0;

    float $sum_arity5(float a0, float a1, float a2, float a3, float a4) {
        auto sum = a0 + a1 + a2 + a3 + a4;
        acc_base += sum;
        return sum;
    }

    float $mul_arity3(float a0, float a1, float a2) {
        auto mul = a0 * a1 * a2;
        acc_base /= mul;
        return mul;
    }

    void $echo_acc() {
        std::cout << __PRETTY_FUNCTION__ << ": " << acc_base << std::endl;
    }

    long $get_acc() {
        return acc_base;
    }
};

class PolyChildA : public PolyBase<PolyChildA, PolyChildB, PolyChildC, PolyChildD> {
    __implementation__;

public:
    long acc_child_a = 0;

    float sum_arity5(float a0, float a1, float a2, float a3, float a4) {
        auto sum = a0 + a1 + a2 + a3 + a4;
        acc_child_a += sum;
        return sum;
    }

    float mul_arity3(float a0, float a1, float a2) {
        auto mul = a0 * a1 * a2;
        acc_child_a /= mul;
        return mul;
    }

    void echo_acc() {
        std::cout << __PRETTY_FUNCTION__ << ": " << acc_child_a << std::endl;
    }

    long get_acc() {
        return acc_child_a;
    }
};

class PolyChildB : public PolyBase<PolyChildA, PolyChildB, PolyChildC, PolyChildD> {
    __implementation__;

public:
    long acc_child_b = 0;

    float sum_arity5(float a0, float a1, float a2, float a3, float a4) {
        auto sum = a0 + a1 + a2 + a3 + a4;
        acc_child_b += sum;
        return sum;
    }

    float mul_arity3(float a0, float a1, float a2) {
        auto mul = a0 * a1 * a2;
        acc_child_b /= mul;
        return mul;
    }

    void echo_acc() {
        std::cout << __PRETTY_FUNCTION__ << ": " << acc_child_b << std::endl;
    }

    long get_acc() {
        return acc_child_b;
    }
};

class PolyChildC : public PolyBase<PolyChildA, PolyChildB, PolyChildC, PolyChildD> {
    __implementation__;

public:
    long acc_child_c = 0;

    float sum_arity5(float a0, float a1, float a2, float a3, float a4) {
        auto sum = a0 + a1 + a2 + a3 + a4;
        acc_child_c += sum;
        return sum;
    }

    float mul_arity3(float a0, float a1, float a2) {
        auto mul = a0 * a1 * a2;
        acc_child_c /= mul;
        return mul;
    }

    void echo_acc() {
        std::cout << __PRETTY_FUNCTION__ << ": " << acc_child_c << std::endl;
    }

    long get_acc() {
        return acc_child_c;
    }
};

class PolyChildD : public PolyBase<PolyChildA, PolyChildB, PolyChildC, PolyChildD> {
    __implementation__;

public:
    long acc_child_d = 0;

    float sum_arity5(float a0, float a1, float a2, float a3, float a4) {
        auto sum = a0 + a1 + a2 + a3 + a4;
        acc_child_d += sum;
        return sum;
    }

    float mul_arity3(float a0, float a1, float a2) {
        auto mul = a0 * a1 * a2;
        acc_child_d /= mul;
        return mul;
    }

    void echo_acc() {
        std::cout << __PRETTY_FUNCTION__ << ": " << acc_child_d << std::endl;
    }

    long get_acc() {
        return acc_child_d;
    }
};

class CppBase {
public:
    long acc_base = 0;

    virtual float sum_arity5(float a0, float a1, float a2, float a3, float a4) {
        auto sum = a0 + a1 + a2 + a3 + a4;
        acc_base += sum;
        return sum;
    }

    virtual float mul_arity3(float a0, float a1, float a2) {
        auto mul = a0 * a1 * a2;
        acc_base /= mul;
        return mul;
    }

    virtual void echo_acc() {
        std::cout << __PRETTY_FUNCTION__ << ": " << acc_base << std::endl;
    }

    virtual long get_acc() {
        return acc_base;
    }

    virtual ~CppBase() { }
};

class CppChildA : public CppBase {
public:
    long acc_child_a = 0;

    float sum_arity5(float a0, float a1, float a2, float a3, float a4) override {
        auto sum = a0 + a1 + a2 + a3 + a4;
        acc_child_a += sum;
        return sum;
    }

    float mul_arity3(float a0, float a1, float a2) override {
        auto mul = a0 * a1 * a2;
        acc_child_a /= mul;
        return mul;
    }

    void echo_acc() override {
        std::cout << __PRETTY_FUNCTION__ << ": " << acc_child_a << std::endl;
    }

    long get_acc() override {
        return acc_child_a;
    }
};

class CppChildB : public CppBase {
public:
    long acc_child_b = 0;

    float sum_arity5(float a0, float a1, float a2, float a3, float a4) override {
        auto sum = a0 + a1 + a2 + a3 + a4;
        acc_child_b += sum;
        return sum;
    }

    float mul_arity3(float a0, float a1, float a2) override {
        auto mul = a0 * a1 * a2;
        acc_child_b /= mul;
        return mul;
    }

    void echo_acc() override {
        std::cout << __PRETTY_FUNCTION__ << ": " << acc_child_b << std::endl;
    }

    long get_acc() override {
        return acc_child_b;
    }
};

class CppChildC : public CppBase {
public:
    long acc_child_c = 0;

    float sum_arity5(float a0, float a1, float a2, float a3, float a4) override {
        auto sum = a0 + a1 + a2 + a3 + a4;
        acc_child_c += sum;
        return sum;
    }

    float mul_arity3(float a0, float a1, float a2) override {
        auto mul = a0 * a1 * a2;
        acc_child_c /= mul;
        return mul;
    }

    void echo_acc() override {
        std::cout << __PRETTY_FUNCTION__ << ": " << acc_child_c << std::endl;
    }

    long get_acc() override {
        return acc_child_c;
    }
};

class CppChildD : public CppBase {
public:
    long acc_child_d = 0;

    float sum_arity5(float a0, float a1, float a2, float a3, float a4) override {
        auto sum = a0 + a1 + a2 + a3 + a4;
        acc_child_d += sum;
        return sum;
    }

    float mul_arity3(float a0, float a1, float a2) override {
        auto mul = a0 * a1 * a2;
        acc_child_d /= mul;
        return mul;
    }

    void echo_acc() override {
        std::cout << __PRETTY_FUNCTION__ << ": " << acc_child_d << std::endl;
    }

    long get_acc() override {
        return acc_child_d;
    }
};

void run_suit_cpp(std::vector<CppBase*>& pack, int N) {
    for (int i = 0; i < N; ++i) {
        for (unsigned j = 0; j < pack.size(); ++j) {
            pack[j]->sum_arity5(i + 0.0f, i + 1.0f, i + i * 2.0f, i + i * 3.0f, i + 4.0f);
            pack[j]->mul_arity3(1.0f, 1.0f, 2.0f);
        }
    }
}

void run_suit_poly(std::vector<PolyBase<PolyChildA, PolyChildB, PolyChildC, PolyChildD>*>& pack, int N) {
    for (int i = 0; i < N; ++i) {
        for (unsigned j = 0; j < pack.size(); ++j) {
            pack[j]->sum_arity5(i + 0.0f, i + 1.0f, i + i * 2.0f, i + i * 3.0f, i + 4.0f);
            pack[j]->mul_arity3(1.0f, 1.0f, 2.0f);
        }
    }
}

using std::chrono::duration;
using std::chrono::high_resolution_clock;

template <class F>
double timeit(F f) {
    auto t1 = high_resolution_clock::now();
    f();
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    return ms_double.count();
}

int main() {
    int N = 10e+3;
    int M = 10e+3;
    auto rng = std::default_random_engine {};

    using PolyBase = PolyBase<PolyChildA, PolyChildB, PolyChildC, PolyChildD>;

    auto poly_base = new PolyBase();
    auto poly_child_a = new PolyChildA();
    auto poly_child_b = new PolyChildB();
    auto poly_child_c = new PolyChildC();
    auto poly_child_d = new PolyChildC();

    std::vector<PolyBase*> poly_pack = {
        poly_base,
        (static_cast<PolyBase*>(poly_child_a)),
        (static_cast<PolyBase*>(poly_child_c)),
        (static_cast<PolyBase*>(poly_child_b)),
        (static_cast<PolyBase*>(poly_child_d))
    };

    auto cpp_base = new CppBase();
    auto cpp_child_a = new CppChildA();
    auto cpp_child_b = new CppChildB();
    auto cpp_child_c = new CppChildC();
    auto cpp_child_d = new CppChildD();

    std::vector<CppBase*> cpp_pack = {
        cpp_base,
        (static_cast<CppBase*>(cpp_child_a)),
        (static_cast<CppBase*>(cpp_child_c)),
        (static_cast<CppBase*>(cpp_child_b)),
        (static_cast<CppBase*>(cpp_child_d))
    };

    double poly_time = 0;
    double cpp_time = 0;

    for (auto k = 0; k < M; ++k) {
        poly_time += timeit(std::bind_front(run_suit_poly, poly_pack, N));
        std::shuffle(std::begin(poly_pack), std::end(poly_pack), rng);
    }

    sleep(3);

    for (auto k = 0; k < M; ++k) {
        cpp_time += timeit(std::bind_front(run_suit_cpp, cpp_pack, N));
        std::shuffle(std::begin(cpp_pack), std::end(cpp_pack), rng);
    }

    std::cout << std::format("Poly: {:.5f}ms (total), {:.5f}ms (avg)\n", poly_time, poly_time / (N * M));
    std::cout << std::format("CPP:  {:.5f}ms (total), {:.5f}ms (avg)\n", cpp_time, cpp_time / (N * M));
    std::cout << std::format("CPP / Poly = {:.3f}\n", cpp_time / poly_time);

    for (auto obj : cpp_pack) {
        delete obj;
    }

    for (auto obj : poly_pack) {
        delete obj;
    }
}