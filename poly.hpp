#ifndef _POLY_HPP_
#define _POLY_HPP_

#include <functional>
#include <string_view>

namespace poly {

using cid_t = const std::string_view;

template<class D>
concept has_scid = requires(D d) { d.scid; };

#define __tostr(_x) __tostr_(_x)
#define __tostr_(_x) #_x
#define __generate_cid() __tostr(__LINE__) __FILE_NAME__
#define __implementation__ public: static constexpr cid_t scid = "D" __generate_cid(); cid_t cid = scid;
#define __cid(_cid) public: static constexpr cid_t scid = _cid; cid_t cid = _cid;
#define __collect_derived_cids(_derived) static constexpr cid_t derived_cids[] = { _derived::scid ... };
#define __polymorphic__ public: __cid("B" __generate_cid()) __collect_derived_cids(Derived)
#define __base template<class... Derived>

#define __make_dispatch_table(_method)                                                        \
template<class D, typename ResT, typename... ArgsT>                                           \
inline void _call_derived$##_method(int &cid_idx, ResT *res, ArgsT&... args)                  \
requires has_scid<D> {                                                                        \
    if (cid_idx < 0) return;                                                                  \
    auto casted_ptr = static_cast<D*>(this);                                                  \
    if (casted_ptr->cid == derived_cids[cid_idx++]) {                                         \
        using B = std::remove_reference<decltype(*this)>::type;                               \
        using M = decltype(&B::$##_method);                                                   \
        M base_method = &B::_method;                                                          \
        M derived_method = static_cast<M>(&D::_method);                                       \
        M matched_method = (base_method == derived_method) ? &B::$##_method : derived_method; \
        if constexpr (std::is_same_v<ResT*, void*>) {                                         \
            std::bind_front(matched_method, casted_ptr)(args...);                             \
        } else {                                                                              \
            *res = std::bind_front(matched_method, casted_ptr)(args...);                      \
        }                                                                                     \
        cid_idx = -1;                                                                         \
    }                                                                                         \
}

#define __dispatch(_method)                                                                   \
private:                                                                                      \
__make_dispatch_table(_method)                                                                \
public:                                                                                       \
template<typename... Ts>                                                                      \
auto _method(Ts... args) {                                                                    \
    int cid_idx = 0;                                                                          \
    using ResT = decltype(this->$##_method(args...));                                         \
    if constexpr (std::is_void_v<ResT>) {                                                     \
        ((_call_derived$##_method<Derived>(cid_idx, (void*)0, args...), cid_idx > 0) && ...); \
        if (cid_idx > 0) this->$##_method(args...);                                           \
    } else {                                                                                  \
        ResT res;                                                                             \
        ((_call_derived$##_method<Derived>(cid_idx, &res, args...), cid_idx > 0) && ...);     \
        if (cid_idx > 0) res = this->$##_method(args...);                                     \
        return res;                                                                           \
    }                                                                                         \
}

#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(_macro, ...) \
    __VA_OPT__(EXPAND(FOR_EACH_HELPER(_macro, __VA_ARGS__)))

#define FOR_EACH_HELPER(_macro, _a1, ...) \
    _macro(_a1) \
    __VA_OPT__(, FOR_EACH_AGAIN PARENS (_macro, __VA_ARGS__))

#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define __unused(_a) [[maybe_unused]] _a

#define __interface_call_msg__ \
    std::string("Calling the interface \"") + __PRETTY_FUNCTION__ + "\" is prohibited"

#define __interface(_name, _ret, ...) \
[[maybe_unused]] _ret $##_name (FOR_EACH(__unused, __VA_ARGS__)) {  \
    throw std::logic_error(__interface_call_msg__);                 \
    return _ret{};                                                  \
}

} // namespace poly

#endif // _POLY_HPP_