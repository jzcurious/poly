#include "classes.cpp"
#include "poly.hpp"
#include "gtest/gtest.h"

using namespace classes;
const auto dispatcher = Dispatcher{};

TEST(ExplicitTests, all_implemented) {
  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->f2(), dispatcher->f2(base));
  EXPECT_EQ(derived_a->f2(), dispatcher->f2(derived_a));
  EXPECT_EQ(derived_b->f2(), dispatcher->f2(derived_b));
  EXPECT_EQ(derived_c->f2(), dispatcher->f2(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ExplicitTests, all_implemented_const) {

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->get_id(), dispatcher->get_id(base));
  EXPECT_EQ(derived_a->get_id(), dispatcher->get_id(derived_a));
  EXPECT_EQ(derived_b->get_id(), dispatcher->get_id(derived_b));
  EXPECT_EQ(derived_c->get_id(), dispatcher->get_id(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ExplicitTests, not_impemented_in_derived) {

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->f3(), dispatcher->f3(base));
  EXPECT_EQ(base->f3(), dispatcher->f3(derived_a));
  EXPECT_EQ(base->f3(), dispatcher->f3(derived_b));
  EXPECT_EQ(base->f3(), dispatcher->f3(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ExplicitTests, not_impemented_in_derived_const) {

  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->f1(), dispatcher->f1(base));
  EXPECT_EQ(base->f1(), dispatcher->f1(derived_a));
  EXPECT_EQ(base->f1(), dispatcher->f1(derived_b));
  EXPECT_EQ(base->f1(), dispatcher->f1(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}
