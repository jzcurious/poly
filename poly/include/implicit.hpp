#ifndef _POLY_IMPLICIT_HPP_
#define _POLY_IMPLICIT_HPP_

#include "polysa.hpp"

#define __poly_override(_mfunc) __poly_dispatch(_mfunc);

#define __poly_decl_base(_name, _dispatch)                                               \
  template <poly_compatible... Classes>                                                  \
  struct _name _dispatch

namespace poly {}  // namespace poly

#endif  // _POLY_IMPLICIT_HPP_
