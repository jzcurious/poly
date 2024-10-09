#ifndef _POLY_HPP_
#define _POLY_HPP_

#include <concepts>
#include <type_traits>

namespace poly {

template <class T>
concept poly_compatible = requires(T x) {
  x.poly_cid;
  T::poly_scid;
};

using poly_cid_t = int;

#define __generate_cid() __LINE__ + 1

#define __poly_enable()                                                                  \
                                                                                         \
 public:                                                                                 \
  static constexpr const poly_cid_t poly_scid = __generate_cid();                        \
  const poly_cid_t poly_cid = poly_scid

namespace detail {

template <class F, class... ArgTs>
constexpr bool invocable_non_void_return
    = std::invocable<F, ArgTs...>
      and not std::is_void_v<std::invoke_result_t<F, ArgTs...>>;

template <class F, class... ArgTs>
constexpr bool invocable_void_return
    = std::invocable<F, ArgTs...> and std::is_void_v<std::invoke_result_t<F, ArgTs...>>;

template <poly_compatible Base, poly_compatible... Derived>
struct PolyGroup : public Base {
  int cidof(const Base* ptr) const {
    poly_cid_t poly_cid = Base::poly_scid;
    ((reinterpret_cast<const Derived*>(ptr)->poly_cid == Derived::poly_scid
             ? poly_cid = Derived::poly_scid
             : 0)
        || ...);
    return poly_cid;
  }
};

}  // namespace detail

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
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
  auto _mfunc(ArgTs&&... args) const {                                                   \
    return dispatch_##_mfunc(this, std::forward<ArgTs>(args)...);                        \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
  auto _mfunc(ArgTs&&... args) {                                                         \
    return dispatch_##_mfunc(this, std::forward<ArgTs>(args)...);                        \
  }

#define __autocast_to(_class)                                                            \
  static _class* forward(Base* ptr) {                                                    \
    return reinterpret_cast<_class*>(ptr);                                               \
  }                                                                                      \
  static const _class* forward(const Base* ptr) {                                        \
    return reinterpret_cast<const _class*>(ptr);                                         \
  }

#define __poly_decl_group(_name, _body)                                                  \
  template <poly_compatible Base, poly_compatible... Derived>                            \
  struct _name : public detail::PolyGroup<Base, Derived...> _body
}  // namespace poly

#endif  // _POLY_HPP_
