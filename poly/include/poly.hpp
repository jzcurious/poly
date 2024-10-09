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

#define __poly_enable()                                                                  \
                                                                                         \
 public:                                                                                 \
  static constexpr const poly_cid_t poly_scid = __LINE__ + 1;                            \
  const poly_cid_t poly_cid = poly_scid

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

#endif  // _POLY_HPP_
