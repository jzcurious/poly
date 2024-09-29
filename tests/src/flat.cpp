#include "poly.hpp"

#include <string>

using namespace poly;

namespace flat {
/* Base <- ChildA */
/* Base <- ChildB */
/* Base <- ChildC */

class ChildA;
class ChildB;
class ChildC;

__base__ class Base {
  __polymorphic__;
  __dispatch(get_id);
  __dispatch(f1);
  __dispatch(f2);

 public:
  std::string $get_id() {
    return __PRETTY_FUNCTION__;
  }

  std::string $f1() {
    return $get_id();
  }

  __abstract(f2, float, int a, int b);
};

class ChildA : public Base<ChildA, ChildB, ChildC> {
  __implementation__;

 public:
  std::string get_id() {
    return __PRETTY_FUNCTION__;
  }

  float f2(int a, int b) {
    return a * b;
  }
};

class ChildB : public Base<ChildA, ChildB, ChildC> {
  __implementation__;

 public:
  std::string get_id() {
    return __PRETTY_FUNCTION__;
  }
};

class ChildC : public Base<ChildA, ChildB, ChildC> {
  __implementation__;

 public:
  std::string get_id() {
    return __PRETTY_FUNCTION__;
  }
};

}  // namespace flat
