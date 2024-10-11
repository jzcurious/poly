#ifndef _POLY_EXPLICIT_HPP_
#define _POLY_EXPLICIT_HPP_

#include "polysa.hpp"
#include <concepts>
#include <type_traits>
#include <utility>  // IWYU pragma: keep

#define __poly_dispatch(_mfunc)                                                          \
  template <class... ArgTs>                                                              \
    requires poly::detail::                                                              \
        invocable_void_return<decltype(&Base::_mfunc), Base, ArgTs&&...>                 \
      static void dispatch_##_mfunc(const Base* ptr, ArgTs&&... args) {                  \
    if (static_cast<const DerivedHead*>(ptr)->cid == Base::scid)                         \
      return ptr->_mfunc(std::forward<ArgTs>(args)...);                                  \
    if (static_cast<const DerivedHead*>(ptr)->cid == DerivedHead::scid)                  \
      return static_cast<const DerivedHead*>(ptr)->_mfunc(std::forward<ArgTs>(args)...); \
    bool is_derived = false;                                                             \
    ((static_cast<const DerivedTail*>(ptr)->cid == DerivedTail::scid                     \
             ? (static_cast<const DerivedTail*>(ptr)->_mfunc(                            \
                    std::forward<ArgTs>(args)...),                                       \
                   is_derived = true)                                                    \
             : false)                                                                    \
        || ...);                                                                         \
    if (not is_derived) ptr->_mfunc(std::forward<ArgTs>(args)...);                       \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
    requires poly::detail::                                                              \
        invocable_void_return<decltype(&Base::_mfunc), Base, ArgTs&&...>                 \
      static void dispatch_##_mfunc(Base* ptr, ArgTs&&... args) {                        \
    if (static_cast<DerivedHead*>(ptr)->cid == Base::scid)                               \
      return ptr->_mfunc(std::forward<ArgTs>(args)...);                                  \
    if (static_cast<DerivedHead*>(ptr)->cid == DerivedHead::scid)                        \
      return static_cast<DerivedHead*>(ptr)->_mfunc(std::forward<ArgTs>(args)...);       \
    bool is_derived = false;                                                             \
    ((static_cast<DerivedTail*>(ptr)->cid == DerivedTail::scid                           \
             ? (static_cast<DerivedTail*>(ptr)->_mfunc(std::forward<ArgTs>(args)...),    \
                   is_derived = true)                                                    \
             : false)                                                                    \
        || ...);                                                                         \
    if (not is_derived) ptr->_mfunc(std::forward<ArgTs>(args)...);                       \
  }                                                                                      \
  template <class... ArgTs>                                                              \
    requires poly::detail::                                                              \
        invocable_non_void_return<decltype(&Base::_mfunc), Base, ArgTs&&...>             \
      static auto dispatch_##_mfunc(const Base* ptr, ArgTs&&... args) {                  \
    if (static_cast<const DerivedHead*>(ptr)->cid == Base::scid)                         \
      return ptr->_mfunc(std::forward<ArgTs>(args)...);                                  \
    if (static_cast<const DerivedHead*>(ptr)->cid == DerivedHead::scid)                  \
      return static_cast<DerivedHead*>(ptr)->_mfunc(std::forward<ArgTs>(args)...);       \
    std::invoke_result_t<decltype(&Base::_mfunc), Base, ArgTs...> result;                \
    bool is_derived = false;                                                             \
    ((static_cast<const DerivedTail*>(ptr)->cid == DerivedTail::scid                     \
             ? (result = static_cast<const DerivedTail*>(ptr)->_mfunc(                   \
                    std::forward<ArgTs>(args)...),                                       \
                   is_derived = true)                                                    \
             : false)                                                                    \
        || ...);                                                                         \
    if (not is_derived)                                                                  \
      return ptr->_mfunc(std::forward<ArgTs>(args)...);                                  \
    else                                                                                 \
      return result;                                                                     \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
    requires poly::detail::                                                              \
        invocable_non_void_return<decltype(&Base::_mfunc), Base, ArgTs&&...>             \
      static auto dispatch_##_mfunc(Base* ptr, ArgTs&&... args) {                        \
    std::invoke_result_t<decltype(&Base::_mfunc), Base, ArgTs...> result;                \
    if (static_cast<DerivedHead*>(ptr)->cid == Base::scid)                               \
      return ptr->_mfunc(std::forward<ArgTs>(args)...);                                  \
    if (static_cast<DerivedHead*>(ptr)->cid == DerivedHead::scid)                        \
      return static_cast<DerivedHead*>(ptr)->_mfunc(std::forward<ArgTs>(args)...);       \
    bool is_derived = false;                                                             \
    ((static_cast<DerivedTail*>(ptr)->cid == DerivedTail::scid                           \
             ? (result = static_cast<DerivedTail*>(ptr)->_mfunc(                         \
                    std::forward<ArgTs>(args)...),                                       \
                   is_derived = true)                                                    \
             : false)                                                                    \
        || ...);                                                                         \
    if (not is_derived)                                                                  \
      return ptr->_mfunc(std::forward<ArgTs>(args)...);                                  \
    else                                                                                 \
      return result;                                                                     \
  }

#define __poly_decl_dispatcher(_name, _mfuncs, ...)                                      \
  template <poly::poly_compatible Base,                                                  \
      poly::poly_compatible DerivedHead,                                                 \
      poly::poly_compatible... DerivedTail>                                              \
  struct _name##_                                                                        \
      : public poly::detail::PolyDispatcherBase<Base, DerivedHead, DerivedTail...>       \
            _mfuncs;                                                                     \
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

template <poly_compatible Base,
    poly_compatible DerivedHead,
    poly_compatible... DerivedTail>
struct PolyDispatcherBase : public Base {
  static int cidof(const Base* ptr) {
    if (static_cast<const DerivedHead*>(ptr)->cid == DerivedHead::scid)
      return DerivedHead::scid;
    cid_t cid = Base::scid;
    ((static_cast<const DerivedTail*>(ptr)->cid == DerivedTail::scid
             ? (cid = DerivedTail::scid, true)
             : false)
        || ...);
    return cid;
  }
};

}  // namespace detail
}  // namespace poly

#endif  // _POLY_EXPLICIT_HPP_
