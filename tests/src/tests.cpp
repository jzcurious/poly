#include "classes.cpp"
#include "poly.hpp"
#include "gtest/gtest.h"

TEST(ExplicitTests, all_implemented) {
  using namespace classes;

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->f2(), Dispatcher::f2(base));
  EXPECT_EQ(derived_a->f2(), Dispatcher::f2(derived_a));
  EXPECT_EQ(derived_b->f2(), Dispatcher::f2(derived_b));
  EXPECT_EQ(derived_c->f2(), Dispatcher::f2(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ExplicitTests, all_implemented_const) {
  using namespace classes;

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->get_id(), Dispatcher::get_id(base));
  EXPECT_EQ(derived_a->get_id(), Dispatcher::get_id(derived_a));
  EXPECT_EQ(derived_b->get_id(), Dispatcher::get_id(derived_b));
  EXPECT_EQ(derived_c->get_id(), Dispatcher::get_id(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ExplicitTests, not_impemented_in_derived) {
  using namespace classes;

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->f3(), Dispatcher::f3(base));
  EXPECT_EQ(base->f3(), Dispatcher::f3(derived_a));
  EXPECT_EQ(base->f3(), Dispatcher::f3(derived_b));
  EXPECT_EQ(base->f3(), Dispatcher::f3(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ExplicitTests, not_impemented_in_derived_const) {
  using namespace classes;

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->f1(), Dispatcher::f1(base));
  EXPECT_EQ(base->f1(), Dispatcher::f1(derived_a));
  EXPECT_EQ(base->f1(), Dispatcher::f1(derived_b));
  EXPECT_EQ(base->f1(), Dispatcher::f1(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}
