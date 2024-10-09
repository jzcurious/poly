#ifndef _POLY_IMPLICIT_HPP_
#define _POLY_IMPLICIT_HPP_

#define __poly_override_void(_mfunc)                                                     \
  template <class... ArgTs>                                                              \
  void _mfunc(ArgTs&&... args) {                                                         \
    bool found = false;                                                                  \
    ((reinterpret_cast<Derived*>(this)->cid == Derived::scid                             \
             ? (reinterpret_cast<Derived*>(this)->_mfunc(std::forward<ArgTs>(args)...),  \
                   found = true)                                                         \
             : false)                                                                    \
        || ...);                                                                         \
    if (not found) reinterpret_cast<Base*>(this)->_mfunc(std::forward<ArgTs>(args)...);  \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
  void _mfunc(ArgTs&&... args) const {                                                   \
    bool found = false;                                                                  \
    ((reinterpret_cast<const Derived*>(this)->cid == Derived::scid                       \
             ? (reinterpret_cast<const Derived*>(this)->_mfunc(                          \
                    std::forward<ArgTs>(args)...),                                       \
                   found = true)                                                         \
             : false)                                                                    \
        || ...);                                                                         \
    if (not found)                                                                       \
      reinterpret_cast<const Base*>(this)->_mfunc(std::forward<ArgTs>(args)...);         \
  }

#define __poly_override_non_void(_mfunc)                                                 \
  template <class... ArgTs>                                                              \
  auto _mfunc(ArgTs&&... args) {                                                         \
    std::invoke_result_t<decltype(&Base::_mfunc), Base, ArgTs...> result;                \
    bool found = false;                                                                  \
    ((reinterpret_cast<Derived*>(this)->cid == Derived::scid                             \
             ? (result = reinterpret_cast<Derived*>(this)->_mfunc(                       \
                    std::forward<ArgTs>(args)...),                                       \
                   found = true)                                                         \
             : false)                                                                    \
        || ...);                                                                         \
    if (not found)                                                                       \
      return reinterpret_cast<Base*>(this)->_mfunc(std::forward<ArgTs>(args)...);        \
    return result;                                                                       \
  }                                                                                      \
                                                                                         \
  template <class... ArgTs>                                                              \
  auto _mfunc(ArgTs&&... args) const {                                                   \
    std::invoke_result_t<decltype(&Base::_mfunc), Base, ArgTs...> result;                \
    bool found = false;                                                                  \
    ((reinterpret_cast<const Derived*>(this)->cid == Derived::scid                       \
             ? (result = reinterpret_cast<const Derived*>(this)->_mfunc(                 \
                    std::forward<ArgTs>(args)...),                                       \
                   true)                                                                 \
             : false)                                                                    \
        || ...);                                                                         \
    if (not found)                                                                       \
      return reinterpret_cast<const Base*>(this)->_mfunc(std::forward<ArgTs>(args)...);  \
    return result;                                                                       \
  }

#define __poly_decl_base(_name, _overrided, ...)                                         \
  template <class Base, class... Derived>                                                \
  struct _name##_ _overrided;                                                            \
  using _name = _name##_<__VA_ARGS__>

#endif  // _POLY_IMPLICIT_HPP_
