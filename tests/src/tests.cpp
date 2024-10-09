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
  EXPECT_NE(base->f2(), Dispatcher::dispatch_f2(derived_a));
  EXPECT_NE(base->f2(), Dispatcher::dispatch_f2(derived_b));
  EXPECT_NE(base->f2(), Dispatcher::dispatch_f2(derived_c));

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
  EXPECT_NE(base->get_id(), Dispatcher::dispatch_get_id(derived_a));
  EXPECT_NE(base->get_id(), Dispatcher::dispatch_get_id(derived_b));
  EXPECT_NE(base->get_id(), Dispatcher::dispatch_get_id(derived_c));

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

TEST(ImplicitTests, all_implemented_const) {
  using namespace classes::implicit_style;

  auto pbase = new PolyBase();
  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->get_id(), pbase->f2());
  EXPECT_NE(base->get_id(), pbase->f2());
  EXPECT_NE(base->get_id(), pbase->f2());
  EXPECT_NE(base->get_id(), pbase->f2());

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}
