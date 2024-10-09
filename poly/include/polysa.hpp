#ifndef _POLYSA_HPP_
#define _POLYSA_HPP_

#include <concepts>
#include <type_traits>

#define __poly_enable()                                                                  \
                                                                                         \
 public:                                                                                 \
  static constexpr const poly_cid_t poly_scid = __LINE__ + 1;                            \
  const poly_cid_t poly_cid = poly_scid

#define __poly_dispatch(_mfunc)                                                          \
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

namespace poly {

template <class T>
concept poly_compatible = requires(T x) {
  x.poly_cid;
  T::poly_scid;
};

using poly_cid_t = int;

namespace detail {

template <class F, class... ArgTs>
constexpr bool invocable_non_void_return
    = std::invocable<F, ArgTs...>
      and not std::is_void_v<std::invoke_result_t<F, ArgTs...>>;

template <class F, class... ArgTs>
constexpr bool invocable_void_return
    = std::invocable<F, ArgTs...> and std::is_void_v<std::invoke_result_t<F, ArgTs...>>;

}  // namespace detail

}  // namespace poly

#endif  // _POLYSA_HPP_
