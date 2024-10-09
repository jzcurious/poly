#ifndef _POLYSA_HPP_
#define _POLYSA_HPP_

#define __poly_enable()                                                                  \
                                                                                         \
 public:                                                                                 \
  static constexpr const poly::cid_t scid = __LINE__ + 1;                                \
  const poly::cid_t cid = scid

namespace poly {

template <class T>
concept poly_compatible = requires(T x) {
  x.cid;
  T::scid;
};

using cid_t = int;

}  // namespace poly

#endif  // _POLYSA_HPP_
