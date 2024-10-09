#ifndef _POLY_EXPLICIT_HPP_
#define _POLY_EXPLICIT_HPP_

#include "polysa.hpp"
#include <concepts>
#include <type_traits>

#define __poly_dispatch(_mfunc)                                                          \
  template <class... ArgTs>                                                              \
    requires poly::detail::                                                              \
        invocable_void_return<decltype(&Base::_mfunc), Base, ArgTs&&...>                 \
      static void dispatch_##_mfunc(const Base* ptr, ArgTs&&... args) {                  \
    bool found = false;                                                                  \
    ((reinterpret_cast<const Derived*>(ptr)->cid == Derived::scid                        \
             ? (reinterpret_cast<const Derived*>(ptr)->_mfunc(                           \
                    std::forward<ArgTs>(args)...),                                       \
                   found = true)                                                         \
             : false)                                                                    \
        || ...);                                                                         \
    if (not found) ptr->_mfunc(args...);                                                 \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
    requires poly::detail::                                                              \
        invocable_non_void_return<decltype(&Base::_mfunc), Base, ArgTs&&...>             \
      static auto dispatch_##_mfunc(const Base* ptr, ArgTs&&... args) {                  \
    std::invoke_result_t<decltype(&Base::_mfunc), Base, ArgTs...> result;                \
    bool found = false;                                                                  \
    ((reinterpret_cast<const Derived*>(ptr)->cid == Derived::scid                        \
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
    requires poly::detail::                                                              \
        invocable_void_return<decltype(&Base::_mfunc), Base, ArgTs&&...>                 \
      static void dispatch_##_mfunc(Base* ptr, ArgTs&&... args) {                        \
    bool found = false;                                                                  \
    ((reinterpret_cast<Derived*>(ptr)->cid == Derived::scid                              \
             ? (reinterpret_cast<Derived*>(ptr)->_mfunc(std::forward<ArgTs>(args)...),   \
                   found = true)                                                         \
             : false)                                                                    \
        || ...);                                                                         \
    if (not found) ptr->_mfunc(args...);                                                 \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
    requires poly::detail::                                                              \
        invocable_non_void_return<decltype(&Base::_mfunc), Base, ArgTs&&...>             \
      static auto dispatch_##_mfunc(Base* ptr, ArgTs&&... args) {                        \
    std::invoke_result_t<decltype(&Base::_mfunc), Base, ArgTs...> result;                \
    bool found = false;                                                                  \
    ((reinterpret_cast<Derived*>(ptr)->cid == Derived::scid                              \
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

#define __poly_decl_dispatcher(_name, _mfuncs, ...)                                      \
  template <poly::poly_compatible Base, poly::poly_compatible... Derived>                \
  struct _name##_ : public poly::detail::PolyDispatcherBase<Base, Derived...> _mfuncs;   \
  using _name = _name##_<__VA_ARGS__>

namespace poly {
namespace detail {

template <class F, class... ArgTs>
constexpr bool invocable_non_void_return
    = std::invocable<F, ArgTs...>
      and not std::is_void_v<std::invoke_result_t<F, ArgTs...>>;

template <class F, class... ArgTs>
constexpr bool invocable_void_return
    = std::invocable<F, ArgTs...> and std::is_void_v<std::invoke_result_t<F, ArgTs...>>;

template <poly_compatible Base, poly_compatible... Derived>
struct PolyDispatcherBase : public Base {
  int cidof(const Base* ptr) const {
    cid_t cid = Base::scid;
    ((static_cast<const Derived*>(ptr)->cid == Derived::scid ? cid = Derived::scid : 0),
        ...);
    return cid;
  }
};

}  // namespace detail
}  // namespace poly

#endif  // _POLY_EXPLICIT_HPP_
