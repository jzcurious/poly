#include "dispatcher.hpp"
#include "poly.hpp"

#include <iostream>
#include <string>

namespace classes {

class Base {
  __poly_set_class_id(0);

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
  __poly_set_class_id(1);

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
  __poly_set_class_id(2);

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
  __poly_set_class_id(3);

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

__poly_decl_dispatcher(
    Dispatcher,
    {
      __poly_dispatch(get_id);
      __poly_dispatch(f1);
      __poly_dispatch(f2);
      __poly_dispatch(f3);
    },
    Base,
    DerivedA,
    DerivedB,
    DerivedC);

}  // namespace classes
