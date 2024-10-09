#ifndef _POLY_DISPATCHER_HPP_
#define _POLY_DISPATCHER_HPP_

#include "poly.hpp"

namespace poly {

#define __dispatch(_mfunc)                                                               \
  template <class... ArgTs>                                                              \
    requires detail::invocable_void_return<decltype(&Base::_mfunc), Base, ArgTs...>      \
  void dispatch_##_mfunc(const Base* ptr, ArgTs&&... args) const {                       \
    bool found = false;                                                                  \
    ((reinterpret_cast<const Derived*>(ptr)->poly_cid == Derived::poly_scid              \
             ? (reinterpret_cast<const Derived*>(ptr)->_mfunc(                           \
                    std::forward<ArgTs>(args)...),                                       \
                   found = true)                                                         \
             : false)                                                                    \
        || ...);                                                                         \
    if (not found) ptr->_mfunc(args...);                                                 \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
    requires detail::invocable_non_void_return<decltype(&Base::_mfunc), Base, ArgTs...>  \
  auto dispatch_##_mfunc(const Base* ptr, ArgTs&&... args) const {                       \
    std::invoke_result_t<decltype(&Base::_mfunc), Base, ArgTs...> result;                \
    bool found = false;                                                                  \
    ((reinterpret_cast<const Derived*>(ptr)->poly_cid == Derived::poly_scid              \
             ? (result = reinterpret_cast<const Derived*>(ptr)->_mfunc(                  \
                    std::forward<ArgTs>(args)...),                                       \
                   found = true)                                                         \
             : false)                                                                    \
        || ...);                                                                         \
    if (not found)                                                                       \
      return ptr->_mfunc(args...);                                                       \
    else                                                                                 \
      return result;                                                                     \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
    requires detail::invocable_void_return<decltype(&Base::_mfunc), Base, ArgTs...>      \
  void dispatch_##_mfunc(Base* ptr, ArgTs&&... args) {                                   \
    bool found = false;                                                                  \
    ((reinterpret_cast<Derived*>(ptr)->poly_cid == Derived::poly_scid                    \
             ? (reinterpret_cast<Derived*>(ptr)->_mfunc(std::forward<ArgTs>(args)...),   \
                   found = true)                                                         \
             : false)                                                                    \
        || ...);                                                                         \
    if (not found) ptr->_mfunc(args...);                                                 \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
    requires detail::invocable_non_void_return<decltype(&Base::_mfunc), Base, ArgTs...>  \
  auto dispatch_##_mfunc(Base* ptr, ArgTs&&... args) {                                   \
    std::invoke_result_t<decltype(&Base::_mfunc), Base, ArgTs...> result;                \
    bool found = false;                                                                  \
    ((reinterpret_cast<Derived*>(ptr)->poly_cid == Derived::poly_scid                    \
             ? (result = reinterpret_cast<Derived*>(ptr)->_mfunc(                        \
                    std::forward<ArgTs>(args)...),                                       \
                   found = true)                                                         \
             : false)                                                                    \
        || ...);                                                                         \
    if (not found)                                                                       \
      return ptr->_mfunc(args...);                                                       \
    else                                                                                 \
      return result;                                                                     \
  }

}  // namespace poly

#endif  // _POLY_DISPATCHER_HPP_
