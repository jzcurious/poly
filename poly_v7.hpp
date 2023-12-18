#ifndef _POLY_V7_HPP_
#define _POLY_V7_HPP_

namespace poly {

template <class D>
concept has_cid = requires(D d) { d.cid; };

using cid_t = long int;
#define __generate_cid() __LINE__ + 1

#define __base__ template <class... Derived>

#define __implementation__                                \
public:                                                   \
    static constexpr const cid_t scid = __generate_cid(); \
    const cid_t cid = scid

#define __implementation(_cid)                \
public:                                       \
    static constexpr const cid_t scid = _cid; \
    const cid_t cid = _cid

#define __polymorphic__                             \
public:                                             \
    static constexpr cid_t scid = __generate_cid(); \
    const cid_t cid = scid;                         \
                                                    \
private:                                            \
    bool _is_base_inst = false;                     \
    bool _is_derived_inst = true

#define __end_of_method__ static_assert(true, "")

#define __dispatch_case(_method)                                                                      \
    template <typename DerivedT, typename ResT, typename... ArgsT>                                    \
    inline void _call_impl_##_method(ResT* res, ArgsT&... args)                                       \
        requires has_cid<DerivedT>                                                                    \
    {                                                                                                 \
        using B = std::remove_reference<decltype(*this)>::type;                                       \
        using M = decltype(&B::$##_method);                                                           \
        constexpr bool overrided = static_cast<M>(&B::_method) != static_cast<M>(&DerivedT::_method); \
        constexpr bool procedural = std::is_same_v<ResT*, void*>;                                     \
        if constexpr (overrided and procedural) {                                                     \
            static_cast<DerivedT*>(this)->_method(args...);                                           \
        }                                                                                             \
        if constexpr (overrided and not procedural) {                                                 \
            *res = static_cast<DerivedT*>(this)->_method(args...);                                    \
        }                                                                                             \
        if constexpr (not overrided and procedural) {                                                 \
            this->$##_method(args...);                                                                \
        }                                                                                             \
        if constexpr (not overrided and not procedural) {                                             \
            *res = this->$##_method(args...);                                                         \
        }                                                                                             \
    }                                                                                                 \
    __end_of_method__

#define __dispatch(_method)                                                                                           \
public:                                                                                                               \
    __dispatch_case(_method);                                                                                         \
    template <typename... Ts>                                                                                         \
    inline auto _method(Ts... args) {                                                                                 \
        if (_is_base_inst) {                                                                                          \
            return this->$##_method(args...);                                                                         \
        }                                                                                                             \
        using ResT = decltype(this->$##_method(args...));                                                             \
        if constexpr (not std::is_void_v<ResT>) {                                                                     \
            ResT res {};                                                                                              \
            _is_base_inst = not((static_cast<Derived*>(this)->cid == Derived::scid                                    \
                                        ? (_call_impl_##_method<Derived>(&res, args...), _is_derived_inst = true)     \
                                        : false)                                                                      \
                || ...);                                                                                              \
            if (_is_base_inst) {                                                                                      \
                return this->$##_method(args...);                                                                     \
            }                                                                                                         \
            return res;                                                                                               \
        } else {                                                                                                      \
            _is_base_inst = not((static_cast<Derived*>(this)->cid == Derived::scid                                    \
                                        ? (_call_impl_##_method<Derived>((void*)0, args...), _is_derived_inst = true) \
                                        : false)                                                                      \
                || ...);                                                                                              \
            if (_is_base_inst) {                                                                                      \
                this->$##_method(args...);                                                                            \
            }                                                                                                         \
        }                                                                                                             \
    }                                                                                                                 \
    __end_of_method__

#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(_macro, ...) \
    __VA_OPT__(EXPAND(FOR_EACH_HELPER(_macro, __VA_ARGS__)))

#define FOR_EACH_HELPER(_macro, _a1, ...) \
    _macro(_a1)                           \
        __VA_OPT__(, FOR_EACH_AGAIN PARENS(_macro, __VA_ARGS__))

#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define __unused_arg(_a) [[maybe_unused]] _a

#define __interface_call_msg__ \
    std::string("Calling the interface \"") + __PRETTY_FUNCTION__ + "\" is prohibited"

#define __interface(_name, _ret, ...)                                     \
    [[maybe_unused]] _ret $##_name(FOR_EACH(__unused_arg, __VA_ARGS__)) { \
        throw std::logic_error(__interface_call_msg__);                   \
        return _ret {};                                                   \
    }                                                                     \
    __end_of_method__

} // namespace poly

#endif // _POLY_V7_HPP_