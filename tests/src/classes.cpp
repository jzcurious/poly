#include "dispatcher.hpp"
#include "poly.hpp"

#include <iostream>
#include <string>

namespace classes {

class Base {
  POLY_SET_CLASS_ID(0);

 public:
  int x;

  void echo() const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  std::string get_id() const {
    return __PRETTY_FUNCTION__;
  }

  std::string f1() const {
    return get_id();
  }

  std::string f2() {
    x = 1;
    return get_id();
  }

  std::string f3() {
    return get_id();
  }
};

class DerivedA : public Base {
  POLY_SET_CLASS_ID(1);

 public:
  int y = 3;

  void echo() const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  std::string get_id() const {
    return __PRETTY_FUNCTION__;
  }

  std::string f2() {
    x = 6;
    y = 3;
    return get_id();
  }
};

class DerivedB : public Base {
  POLY_SET_CLASS_ID(2);

 public:
  void echo() const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  std::string get_id() const {
    return __PRETTY_FUNCTION__;
  }

  std::string f2() {
    x = 2;
    return get_id();
  }
};

class DerivedC : public Base {
  POLY_SET_CLASS_ID(3);

 public:
  void echo() const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  std::string get_id() const {
    return __PRETTY_FUNCTION__;
  }

  std::string f2() {
    x = 3;
    return get_id();
  }
};

POLY_DECL_DISPATCHER(
    Dispatcher,
    {
      POLY_DISPATCH(get_id);
      POLY_DISPATCH(f1);
      POLY_DISPATCH(f2);
      POLY_DISPATCH(f3);
    },
    Base,
    DerivedA,
    DerivedB,
    DerivedC);

}  // namespace classes
