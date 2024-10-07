#include "poly.hpp"

#include <string>

using namespace poly;

namespace flat {
/* Base <- ChildA */
/* Base <- ChildB */
/* Base <- ChildC */

class Base {
  __poly_enable();

 public:
  std::string get_id() const {
    return __PRETTY_FUNCTION__;
  }

  std::string f1() const {
    return get_id();
  }
};

class ChildA : public Base {
  __poly_enable();

 public:
  std::string get_id() const {
    return __PRETTY_FUNCTION__;
  }

  float f2(int a, int b) const {
    return a * b;
  }
};

class ChildB : public Base {
  __poly_enable();

 public:
  std::string get_id() const {
    return __PRETTY_FUNCTION__;
  }
};

class ChildC : public Base {
  __poly_enable();

 public:
  std::string get_id() const {
    return __PRETTY_FUNCTION__;
  }
};

}  // namespace flat
