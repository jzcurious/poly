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
      void dispatch_##_mfunc(const Base* ptr, ArgTs&&... args) const {                   \
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
      void dispatch_##_mfunc(Base* ptr, ArgTs&&... args) const {                         \
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
      auto dispatch_##_mfunc(const Base* ptr, ArgTs&&... args) const {                   \
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
      auto dispatch_##_mfunc(Base* ptr, ArgTs&&... args) const {                         \
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
  struct _name##_ final : public poly::detail::PolyDispatcher {                          \
   private:                                                                              \
    struct OverridedSuit                                                                 \
        : public poly::detail::OverridedSuit<Base, DerivedHead, DerivedTail...>          \
              _mfuncs;                                                                   \
    OverridedSuit _overrided;                                                            \
                                                                                         \
   public:                                                                               \
    using suit_t = OverridedSuit;                                                        \
                                                                                         \
    OverridedSuit* operator->() {                                                        \
      return &_overrided;                                                                \
    }                                                                                    \
                                                                                         \
    OverridedSuit* forward(Base* ptr) {                                                  \
      _overrided._ptr = ptr;                                                             \
      return &_overrided;                                                                \
    }                                                                                    \
                                                                                         \
    const OverridedSuit* forward(const Base* ptr) {                                      \
      _overrided._ptr = ptr;                                                             \
      return &_overrided;                                                                \
    }                                                                                    \
  };                                                                                     \
  using _name = _name##_<__VA_ARGS__>;

namespace poly::detail {

struct PolyDispatcher {};

template <class T>
concept dispatcher_kind = std::derived_from<T, PolyDispatcher>;

template <class F, class... ArgTs>
concept invocable_non_void_return
    = std::invocable<F, ArgTs...>
      and not std::is_void_v<std::invoke_result_t<F, ArgTs...>>;

template <class F, class... ArgTs>
concept invocable_void_return
    = std::invocable<F, ArgTs...> and std::is_void_v<std::invoke_result_t<F, ArgTs...>>;

template <poly_compatible Base,
    poly_compatible DerivedHead,
    poly_compatible... DerivedTail>
struct OverridedSuit {
  const Base* _ptr;

  OverridedSuit()
      : _ptr(nullptr) {}

  OverridedSuit(const Base* cptr)
      : _ptr(nullptr) {}

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
};
}  // namespace poly::detail

#endif  // _POLY_DISPATCHER_HPP_
