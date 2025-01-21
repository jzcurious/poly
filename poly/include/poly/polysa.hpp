#ifndef _POLYSA_HPP_
#define _POLYSA_HPP_

#define POLY_SET_CLASS_ID(_cid)                                                          \
                                                                                         \
 public:                                                                                 \
  static constexpr const poly::cid_t scid = _cid;                                        \
  const poly::cid_t cid = _cid

#define POLY_OVERRIDE

namespace poly {

template <class T>
concept poly_compatible = requires(T x) {
  x.cid;
  T::scid;
};

using cid_t = int;

}  // namespace poly

#endif  // _POLYSA_HPP_
