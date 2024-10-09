#ifndef _POLY_EXPLICIT_HPP_
#define _POLY_EXPLICIT_HPP_

#include "polysa.hpp"

#define __poly_decl_dispatcher(_name, _cases)                                            \
  template <poly_compatible Base, poly_compatible... Derived>                            \
  struct _name : public detail::PolyDispatcherBase<Base, Derived...> _cases

namespace poly {

namespace detail {

template <poly_compatible Base, poly_compatible... Derived>
struct PolyDispatcherBase : public Base {
  int cidof(const Base* ptr) const {
    poly_cid_t poly_cid = Base::poly_scid;
    ((static_cast<const Derived*>(ptr)->poly_cid == Derived::poly_scid
             ? poly_cid = Derived::poly_scid
             : 0),
        ...);
    return poly_cid;
  }
};

}  // namespace detail

}  // namespace poly

#endif  // _POLY_EXPLICIT_HPP_
