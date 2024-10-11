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

template <poly_compatible Base, poly_compatible... Derived>
struct PolyGroup final {
  static int cidof(const Base* ptr) {
    cid_t cid = Base::scid;
    ((static_cast<const Derived*>(ptr)->cid == Derived::scid ? (cid = Derived::scid, true)
                                                             : false)
        || ...);
    return cid;
  }
};

}  // namespace poly

#endif  // _POLYSA_HPP_
