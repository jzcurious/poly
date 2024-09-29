#include "poly_v7.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <format>
#include <functional>
#include <iostream>
#include <random>
#include <unistd.h>

using namespace poly;

__base__ class PolyBase {
    __polymorphic__;
    __dispatch(func_arity5f);
    __dispatch(func_arity3rf);
    __dispatch(func_arity2f);
    __dispatch(func_arity1f);
    __dispatch(func_arity0);
    __dispatch(get_acc);

public:
    float acc_base = 0;

    float $func_arity5f(float a0, float a1, float a2, float a3, float a4) {
        auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
        acc_base += y;
        return y;
    }

    float $func_arity3rf(float& a0, float& a1, float& a2) {
        auto y = (a0 + a1 + a2) / (a2 + 1);
        acc_base -= y;
        return y;
    }

    float $func_arity2f(float a0, float a1) {
        auto y = a0 / (a1 + 1);
        acc_base -= y;
        return y;
    }

    float $func_arity1f(float a0) {
        auto y = a0 * 2;
        acc_base -= y;
        return y;
    }

    float $func_arity0() {
        auto y = acc_base / 5;
        acc_base -= y;
        return y;
    }

    float $get_acc() {
        return acc_base;
    }
};

#define PolyBaseCRTP PolyBase< \
    PolyChild<1>,              \
    PolyChild<2>,              \
    PolyChild<3>,              \
    PolyChild<4>,              \
    PolyChild<5>,              \
    PolyChild<6>,              \
    PolyChild<7>,              \
    PolyChild<8>,              \
    PolyChild<9>,              \
    PolyChild<10>>

template <int x>
class PolyChild;

template <int x>
class PolyChild : public PolyBaseCRTP {
    __implementation(x);

public:
    float acc_child_a = 0;

    float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
        auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
        acc_child_a += y;
        return y;
    }

    float func_arity3rf(float& a0, float& a1, float& a2) {
        auto y = (a0 + a1 + a2) / (a2 + 1);
        acc_child_a -= y;
        return y;
    }

    float func_arity2f(float a0, float a1) {
        auto y = a0 / (a1 + 1);
        acc_child_a -= y;
        return y;
    }

    float func_arity1f(float a0) {
        auto y = a0 * 2;
        acc_child_a -= y;
        return y;
    }

    float func_arity0() {
        auto y = acc_child_a / 5;
        acc_child_a -= y;
        return y;
    }

    float get_acc() {
        return acc_child_a;
    }
};

class CppBase {
public:
    float acc_base = 0;

    virtual float func_arity5f(float a0, float a1, float a2, float a3, float a4) {
        auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
        acc_base += y;
        return y;
    }

    virtual float func_arity3rf(float& a0, float& a1, float& a2) {
        auto y = (a0 + a1 + a2) / (a2 + 1);
        acc_base -= y;
        return y;
    }

    virtual float func_arity2f(float a0, float a1) {
        auto y = a0 / (a1 + 1);
        acc_base -= y;
        return y;
    }

    virtual float func_arity1f(float a0) {
        auto y = a0 * 2;
        acc_base -= y;
        return y;
    }

    virtual float func_arity0() {
        auto y = acc_base / 5;
        acc_base -= y;
        return y;
    }

    virtual float get_acc() {
        return acc_base;
    }

    virtual ~CppBase() { }
};

template <int x>
class CppChild;

template <int x>
class CppChild : public CppBase {
public:
    float acc_child_a = 0;

    float func_arity5f(float a0, float a1, float a2, float a3, float a4) override {
        auto y = (a0 + a1 + a2 - a3) / (a4 + 1);
        acc_child_a += y;
        return y;
    }

    float func_arity3rf(float& a0, float& a1, float& a2) override {
        auto y = (a0 + a1 + a2) / (a2 + 1);
        acc_child_a -= y;
        return y;
    }

    float func_arity2f(float a0, float a1) override {
        auto y = a0 / (a1 + 1);
        acc_child_a -= y;
        return y;
    }

    float func_arity1f(float a0) override {
        auto y = a0 * 2;
        acc_child_a -= y;
        return y;
    }

    float func_arity0() override {
        auto y = acc_child_a / 5;
        acc_child_a -= y;
        return y;
    }

    float get_acc() override {
        return acc_child_a;
    }
};

void run_suit_cpp(std::vector<CppBase*>& pack, int N) {
    float x = 5;
    float y = 8;
    float z = 9;
    for (int i = 0; i < N; ++i) {
        for (unsigned j = 0; j < pack.size(); ++j) {
            pack[j]->func_arity5f(i + 1.0f, i - 1.0f, i - 1.0f, i + 1.0f, i + 1.0f);
            pack[j]->func_arity3rf(x, y, z);
            pack[j]->func_arity2f(i + 1.0f, i + 1.0f);
            pack[j]->func_arity1f(i + 1.0f);
            pack[j]->func_arity0();
        }
    }
}

void run_suit_poly(std::vector<PolyBaseCRTP*>& pack, int N) {
    float x = 5;
    float y = 8;
    float z = 9;
    for (int i = 0; i < N; ++i) {
        for (unsigned j = 0; j < pack.size(); ++j) {
            pack[j]->func_arity5f(i + 1.0f, i - 1.0f, i - 1.0f, i + 1.0f, i + 1.0f);
            pack[j]->func_arity3rf(x, y, z);
            pack[j]->func_arity2f(i + 1.0f, i + 1.0f);
            pack[j]->func_arity1f(i + 1.0f);
            pack[j]->func_arity0();
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

    using PolyBase = PolyBaseCRTP;

    std::vector<PolyBase*> poly_pack = {
        new PolyBase(),
        new PolyChild<1>(),
        new PolyChild<2>(),
        new PolyChild<3>(),
        new PolyChild<4>(),
        new PolyChild<5>(),
        new PolyChild<6>(),
        new PolyChild<7>(),
        new PolyChild<8>(),
        new PolyChild<9>(),
        new PolyChild<10>()
    };

    std::vector<CppBase*> cpp_pack = {
        new CppBase(),
        new CppChild<1>(),
        new CppChild<2>(),
        new CppChild<3>(),
        new CppChild<4>(),
        new CppChild<5>(),
        new CppChild<6>(),
        new CppChild<7>(),
        new CppChild<8>(),
        new CppChild<9>(),
        new CppChild<10>()
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

    for (unsigned i = 0; i < cpp_pack.size(); ++i) {
        assert(std::fabs(cpp_pack[i]->get_acc() - poly_pack[i]->get_acc()) < 10e-3);
    }

    for (auto obj : cpp_pack) {
        delete obj;
    }

    for (auto obj : poly_pack) {
        delete obj;
    }
}