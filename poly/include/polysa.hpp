#ifndef _POLYSA_HPP_
#define _POLYSA_HPP_

#define __poly_set_class_id(_cid)                                                        \
                                                                                         \
 public:                                                                                 \
  static constexpr const poly::cid_t scid = _cid;                                        \
  const poly::cid_t cid = _cid

namespace poly {

template <class T>
concept poly_compatible = requires(T x) {
  x.cid;
  T::scid;
};

using cid_t = int;

}  // namespace poly

#endif  // _POLYSA_HPP_
