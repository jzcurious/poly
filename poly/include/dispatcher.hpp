#ifndef _POLY_DISPATCHER_HPP_
#define _POLY_DISPATCHER_HPP_

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
                                                                                         \
  template <class... ArgTs>                                                              \
    requires poly::detail::                                                              \
        invocable_non_void_return<decltype(&Base::_mfunc), Base, ArgTs&&...>             \
      static auto dispatch_##_mfunc(const Base* ptr, ArgTs&&... args) {                  \
    if (static_cast<const DerivedHead*>(ptr)->cid == Base::scid)                         \
      return ptr->_mfunc(std::forward<ArgTs>(args)...);                                  \
    if (static_cast<const DerivedHead*>(ptr)->cid == DerivedHead::scid)                  \
      return static_cast<const DerivedHead*>(ptr)->_mfunc(std::forward<ArgTs>(args)...); \
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
    if (static_cast<DerivedHead*>(ptr)->cid == Base::scid)                               \
      return ptr->_mfunc(std::forward<ArgTs>(args)...);                                  \
    if (static_cast<DerivedHead*>(ptr)->cid == DerivedHead::scid)                        \
      return static_cast<DerivedHead*>(ptr)->_mfunc(std::forward<ArgTs>(args)...);       \
    std::invoke_result_t<decltype(&Base::_mfunc), Base, ArgTs...> result;                \
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
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
  auto _mfunc(ArgTs&&... args) const {                                                   \
    return dispatch_##_mfunc(this->_ptr, std::forward<ArgTs>(args)...);                  \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
  auto _mfunc(ArgTs&&... args) {                                                         \
    return dispatch_##_mfunc(                                                            \
        const_cast<Base*>(this->_ptr), std::forward<ArgTs>(args)...);                    \
  }

#define __poly_decl_dispatcher(_name, _mfuncs, ...)                                      \
  template <poly::poly_compatible Base,                                                  \
      poly::poly_compatible DerivedHead,                                                 \
      poly::poly_compatible... DerivedTail>                                              \
  struct _name##OverridedSuit                                                            \
      : public poly::detail::OverridedSuit<Base, DerivedHead, DerivedTail...>            \
            _mfuncs;                                                                     \
                                                                                         \
  template <poly::poly_compatible Base, poly::poly_compatible... Derived>                \
  struct _name##_ final : public _name##OverridedSuit<Base, Derived...> {                \
    _name##_() = default;                                                                \
                                                                                         \
    _name##_(const Base* ptr)                                                            \
        : _name##OverridedSuit<Base, Derived...>(ptr) {}                                 \
                                                                                         \
    _name##_(Base* ptr)                                                                  \
        : _name##OverridedSuit<Base, Derived...>(ptr) {}                                 \
                                                                                         \
    static _name##_ forward(Base* ptr) {                                                 \
      return _name##_(ptr);                                                              \
    }                                                                                    \
                                                                                         \
    static const _name##_ forward(const Base* ptr) {                                     \
      return _name##_(ptr);                                                              \
    }                                                                                    \
  };                                                                                     \
                                                                                         \
  using _name = _name##_<__VA_ARGS__>;

namespace poly::detail {

template <poly_compatible Base,
    poly_compatible DerivedHead,
    poly_compatible... DerivedTail>
struct OverridedSuit {
 protected:
  const Base* _ptr;

 public:
  OverridedSuit()
      : _ptr(nullptr) {}

  OverridedSuit(const Base* cptr)
      : _ptr(cptr) {}

  void destroy() const {
    if (static_cast<const DerivedHead*>(_ptr)->cid == Base::scid) return delete _ptr;
    if (static_cast<const DerivedHead*>(_ptr)->cid == DerivedHead::scid)
      return delete static_cast<const DerivedHead*>(_ptr);
    bool is_derived = false;
    ((static_cast<const DerivedTail*>(_ptr)->cid == DerivedTail::scid
             ? ((delete static_cast<const DerivedTail*>(_ptr)), is_derived = true)
             : false)
        || ...);
    if (not is_derived) delete _ptr;
  }

  static void destroy(const Base* ptr) {
    if (static_cast<const DerivedHead*>(ptr)->cid == Base::scid) return delete ptr;
    if (static_cast<const DerivedHead*>(ptr)->cid == DerivedHead::scid)
      return delete static_cast<const DerivedHead*>(ptr);
    bool is_derived = false;
    ((static_cast<const DerivedTail*>(ptr)->cid == DerivedTail::scid
             ? ((delete static_cast<const DerivedTail*>(ptr)), is_derived = true)
             : false)
        || ...);
    if (not is_derived) delete ptr;
  }

  operator const Base*() const {
    return this->_ptr;
  }

  operator Base*() {
    return const_cast<Base*>(this->_ptr);
  }
};

template <class F, class... ArgTs>
concept invocable_non_void_return
    = std::invocable<F, ArgTs...>
      and not std::is_void_v<std::invoke_result_t<F, ArgTs...>>;

template <class F, class... ArgTs>
concept invocable_void_return
    = std::invocable<F, ArgTs...> and std::is_void_v<std::invoke_result_t<F, ArgTs...>>;

}  // namespace poly::detail

#endif  // _POLY_DISPATCHER_HPP_
