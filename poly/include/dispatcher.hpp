#ifndef _POLY_DISPATCHER_HPP_
#define _POLY_DISPATCHER_HPP_

#include "polysa.hpp"

#define __poly_dispatch(_mfunc)                                                          \
                                                                                         \
 private:                                                                                \
  template <poly::poly_compatible Base_,                                                 \
      poly::poly_compatible DerivedHead_,                                                \
      poly::poly_compatible... DerivedTail_>                                             \
  struct dispatch_##_mfunc##_t {                                                         \
    template <class... ArgTs>                                                            \
      requires std::invocable<decltype(&Base_::_mfunc), Base_, ArgTs&&...>               \
    static auto call(Base_* ptr, ArgTs&&... args) {                                      \
      if (static_cast<DerivedHead_*>(ptr)->cid == Base_::scid)                           \
        return ptr->_mfunc(std::forward<ArgTs>(args)...);                                \
      if (static_cast<DerivedHead_*>(ptr)->cid == DerivedHead_::scid)                    \
        return static_cast<DerivedHead_*>(ptr)->_mfunc(std::forward<ArgTs>(args)...);    \
      using result_t = std::invoke_result_t<decltype(&Base_::_mfunc), Base_, ArgTs...>;  \
      if constexpr (std::is_void_v<result_t>) {                                          \
        if (((static_cast<DerivedTail_*>(ptr)->cid == DerivedTail_::scid                 \
                     ? (static_cast<DerivedTail_*>(ptr)->_mfunc(                         \
                            std::forward<ArgTs>(args)...),                               \
                           true)                                                         \
                     : false)                                                            \
                || ...))                                                                 \
          return;                                                                        \
      } else {                                                                           \
        result_t result;                                                                 \
        if (((static_cast<DerivedTail_*>(ptr)->cid == DerivedTail_::scid                 \
                     ? (result = static_cast<DerivedTail_*>(ptr)->_mfunc(                \
                            std::forward<ArgTs>(args)...),                               \
                           true)                                                         \
                     : false)                                                            \
                || ...))                                                                 \
          return result;                                                                 \
        return ptr->_mfunc(std::forward<ArgTs>(args)...);                                \
      }                                                                                  \
    }                                                                                    \
  };                                                                                     \
                                                                                         \
 public:                                                                                 \
  template <class T, class... ArgTs>                                                     \
    requires(std::derived_from<T, Base>                                                  \
             and std::invocable<decltype(&T::_mfunc), T, ArgTs && ...>)                  \
  static auto dispatch_##_mfunc(T* ptr, ArgTs&&... args) {                               \
    if constexpr (not std::is_same_v<T, Base>) {                                         \
      return ptr->_mfunc(std::forward<ArgTs>(args)...);                                  \
    } else {                                                                             \
      if constexpr (std::is_const_v<T>) {                                                \
        return dispatch_##_mfunc##_t<const Base,                                         \
            const DerivedHead,                                                           \
            const DerivedTail...>::call(ptr, std::forward<ArgTs>(args)...);              \
      } else {                                                                           \
        return dispatch_##_mfunc##_t<Base, DerivedHead, DerivedTail...>::call(           \
            ptr, std::forward<ArgTs>(args)...);                                          \
      }                                                                                  \
    }                                                                                    \
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
    bool is_derived = ((static_cast<const DerivedTail*>(_ptr)->cid == DerivedTail::scid
                               ? ((delete static_cast<const DerivedTail*>(_ptr)), true)
                               : false)
                       || ...);
    if (not is_derived) delete _ptr;
  }

  static void destroy(const Base* ptr) {
    if (static_cast<const DerivedHead*>(ptr)->cid == Base::scid) return delete ptr;
    if (static_cast<const DerivedHead*>(ptr)->cid == DerivedHead::scid)
      return delete static_cast<const DerivedHead*>(ptr);
    bool is_derived = ((static_cast<const DerivedTail*>(ptr)->cid == DerivedTail::scid
                               ? ((delete static_cast<const DerivedTail*>(ptr)), true)
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

}  // namespace poly::detail

#endif  // _POLY_DISPATCHER_HPP_
