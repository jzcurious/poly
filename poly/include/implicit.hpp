#ifndef _POLY_IMPLICIT_HPP_
#define _POLY_IMPLICIT_HPP_

#define __poly_override_void(_mfunc)                                                     \
  template <class... ArgTs>                                                              \
  void _mfunc(ArgTs&&... args) {                                                         \
    if (static_cast<Base*>(this)->cid == Base::scid)                                     \
      return static_cast<Base*>(this)->_mfunc(std::forward<ArgTs>(args)...);             \
    ((static_cast<Derived*>(this)->cid == Derived::scid                                  \
             ? (static_cast<Derived*>(this)->_mfunc(std::forward<ArgTs>(args)...), true) \
             : false)                                                                    \
        || ...);                                                                         \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
  void _mfunc(ArgTs&&... args) const {                                                   \
    if (static_cast<const Base*>(this)->cid == Base::scid)                               \
      return static_cast<const Base*>(this)->_mfunc(std::forward<ArgTs>(args)...);       \
    ((static_cast<const Derived*>(this)->cid == Derived::scid                            \
             ? (static_cast<const Derived*>(this)->_mfunc(std::forward<ArgTs>(args)...), \
                   true)                                                                 \
             : false)                                                                    \
        || ...);                                                                         \
  }

#define __poly_override_non_void(_mfunc)                                                 \
  template <class... ArgTs>                                                              \
  auto _mfunc(ArgTs&&... args) {                                                         \
    if (static_cast<Base*>(this)->cid == Base::scid)                                     \
      return static_cast<Base*>(this)->_mfunc(std::forward<ArgTs>(args)...);             \
    std::invoke_result_t<decltype(&Base::_mfunc), Base, ArgTs&&...> result;              \
    ((static_cast<Derived*>(this)->cid == Derived::scid                                  \
             ? (result                                                                   \
                   = static_cast<Derived*>(this)->_mfunc(std::forward<ArgTs>(args)...),  \
                   true)                                                                 \
             : false)                                                                    \
        || ...);                                                                         \
    return result;                                                                       \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
  auto _mfunc(ArgTs&&... args) const {                                                   \
    if (static_cast<const Base*>(this)->cid == Base::scid)                               \
      return static_cast<const Base*>(this)->_mfunc(std::forward<ArgTs>(args)...);       \
    std::invoke_result_t<decltype(&Base::_mfunc), Base, ArgTs&&...> result;              \
    ((static_cast<const Derived*>(this)->cid == Derived::scid                            \
             ? (result = static_cast<const Derived*>(this)->_mfunc(                      \
                    std::forward<ArgTs>(args)...),                                       \
                   true)                                                                 \
             : false)                                                                    \
        || ...);                                                                         \
    return result;                                                                       \
  }

#define __poly_decl_base(_name, _overrided, ...)                                         \
  template <class Base, class... Derived>                                                \
  struct _name##_ _overrided;                                                            \
  using _name = _name##_<__VA_ARGS__>

#endif  // _POLY_IMPLICIT_HPP_
