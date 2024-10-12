#ifndef _POLY_GROUP_HPP_
#define _POLY_GROUP_HPP_

#include "polysa.hpp"

namespace poly {

template <poly_compatible Base, poly_compatible... Derived>
struct PolyGroup final {
  static int cidof(const Base* ptr) {
    cid_t cid = Base::scid;
    ((static_cast<const Derived*>(ptr)->cid == Derived::scid ? (cid = Derived::scid, true)
                                                             : false)
        || ...);
    return cid;
  }
};

}  // namespace poly
#endif  // _POLY_GROUP_HPP_
