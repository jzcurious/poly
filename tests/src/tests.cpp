#include "classes.cpp"
#include "poly.hpp"
#include "gtest/gtest.h"

TEST(ExplicitTests, all_implemented) {
  using namespace classes::explicit_style;

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->f2(), Dispatcher::dispatch_f2(base));
  EXPECT_EQ(derived_a->f2(), Dispatcher::dispatch_f2(derived_a));
  EXPECT_EQ(derived_b->f2(), Dispatcher::dispatch_f2(derived_b));
  EXPECT_EQ(derived_c->f2(), Dispatcher::dispatch_f2(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ExplicitTests, all_implemented_const) {
  using namespace classes::explicit_style;

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->get_id(), Dispatcher::dispatch_get_id(base));
  EXPECT_EQ(derived_a->get_id(), Dispatcher::dispatch_get_id(derived_a));
  EXPECT_EQ(derived_b->get_id(), Dispatcher::dispatch_get_id(derived_b));
  EXPECT_EQ(derived_c->get_id(), Dispatcher::dispatch_get_id(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ExplicitTests, not_impemented_in_derived) {
  using namespace classes::explicit_style;

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->f3(), Dispatcher::dispatch_f3(base));
  EXPECT_EQ(base->f3(), Dispatcher::dispatch_f3(derived_a));
  EXPECT_EQ(base->f3(), Dispatcher::dispatch_f3(derived_b));
  EXPECT_EQ(base->f3(), Dispatcher::dispatch_f3(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ExplicitTests, not_impemented_in_derived_const) {
  using namespace classes::explicit_style;

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->f1(), Dispatcher::dispatch_f1(base));
  EXPECT_EQ(base->f1(), Dispatcher::dispatch_f1(derived_a));
  EXPECT_EQ(base->f1(), Dispatcher::dispatch_f1(derived_b));
  EXPECT_EQ(base->f1(), Dispatcher::dispatch_f1(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ImplicitTests, all_implemented) {
  using namespace classes::implicit_style;

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->f2(), reinterpret_cast<PolyBase*>(base)->f2());
  EXPECT_EQ(derived_a->f2(), reinterpret_cast<PolyBase*>(derived_a)->f2());
  EXPECT_EQ(derived_b->f2(), reinterpret_cast<PolyBase*>(derived_b)->f2());
  EXPECT_EQ(derived_c->f2(), reinterpret_cast<PolyBase*>(derived_c)->f2());

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ImplicitTests, all_implemented_const) {
  using namespace classes::implicit_style;

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->get_id(), reinterpret_cast<const PolyBase*>(base)->get_id());
  EXPECT_EQ(derived_a->get_id(), reinterpret_cast<const PolyBase*>(derived_a)->get_id());
  EXPECT_EQ(derived_b->get_id(), reinterpret_cast<const PolyBase*>(derived_b)->get_id());
  EXPECT_EQ(derived_c->get_id(), reinterpret_cast<const PolyBase*>(derived_c)->get_id());

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

// TEST(ImplicitTests, not_impemented_in_derived) {
//   using namespace classes::implicit_style;

//   auto base = new Base();
//   auto derived_a = new DerivedA();
//   auto derived_b = new DerivedB();
//   auto derived_c = new DerivedC();

//   EXPECT_EQ(base->f3(), reinterpret_cast<PolyBase*>(base)->f3());
//   EXPECT_EQ(derived_a->f3(), reinterpret_cast<PolyBase*>(derived_a)->f3());
//   EXPECT_EQ(derived_b->f3(), reinterpret_cast<PolyBase*>(derived_b)->f3());
//   EXPECT_EQ(derived_c->f3(), reinterpret_cast<PolyBase*>(derived_c)->f3());

//   delete base;
//   delete derived_a;
//   delete derived_b;
//   delete derived_c;
// }

// TEST(ImplicitTests, not_impemented_in_derived_const) {
//   using namespace classes::implicit_style;

//   auto base = new Base();
//   auto derived_a = new DerivedA();
//   auto derived_b = new DerivedB();
//   auto derived_c = new DerivedC();

//   EXPECT_EQ(base->f1(), reinterpret_cast<const PolyBase*>(base)->f1());
//   EXPECT_EQ(base->f1(), reinterpret_cast<const PolyBase*>(derived_a)->f1());
//   EXPECT_EQ(base->f1(), reinterpret_cast<const PolyBase*>(derived_b)->f1());
//   EXPECT_EQ(base->f1(), reinterpret_cast<const PolyBase*>(derived_c)->f1());

//   delete base;
//   delete derived_a;
//   delete derived_b;
//   delete derived_c;
// }
