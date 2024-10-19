#include "classes.cpp"
#include "poly.hpp"
#include "gtest/gtest.h"

using namespace classes;
auto dispatcher = Dispatcher{};

TEST(ExplicitTests, all_implemented) {
  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  EXPECT_EQ(base->f2(), dispatcher.dispatch_f2(base));
  EXPECT_EQ(derived_a->f2(), dispatcher.dispatch_f2(derived_a));
  EXPECT_EQ(derived_b->f2(), dispatcher.dispatch_f2(derived_b));
  EXPECT_EQ(derived_c->f2(), dispatcher.dispatch_f2(derived_c));

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

  EXPECT_EQ(base->get_id(), dispatcher.dispatch_get_id(base));
  EXPECT_EQ(derived_a->get_id(), dispatcher.dispatch_get_id(derived_a));
  EXPECT_EQ(derived_b->get_id(), dispatcher.dispatch_get_id(derived_b));
  EXPECT_EQ(derived_c->get_id(), dispatcher.dispatch_get_id(derived_c));

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

  EXPECT_EQ(base->f3(), dispatcher.dispatch_f3(base));
  EXPECT_EQ(base->f3(), dispatcher.dispatch_f3(derived_a));
  EXPECT_EQ(base->f3(), dispatcher.dispatch_f3(derived_b));
  EXPECT_EQ(base->f3(), dispatcher.dispatch_f3(derived_c));

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

  EXPECT_EQ(base->f1(), dispatcher.dispatch_f1(base));
  EXPECT_EQ(base->f1(), dispatcher.dispatch_f1(derived_a));
  EXPECT_EQ(base->f1(), dispatcher.dispatch_f1(derived_b));
  EXPECT_EQ(base->f1(), dispatcher.dispatch_f1(derived_c));

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ForwardingTests, all_implemented) {
  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  auto derived_a_ = reinterpret_cast<Base*>(derived_a);
  auto derived_b_ = reinterpret_cast<Base*>(derived_b);
  auto derived_c_ = reinterpret_cast<Base*>(derived_c);

  EXPECT_EQ(base->f2(), dispatcher.forward(base)->f2());
  EXPECT_EQ(derived_a->f2(), dispatcher.forward(derived_a_)->f2());
  EXPECT_EQ(derived_b->f2(), dispatcher.forward(derived_b_)->f2());
  EXPECT_EQ(derived_c->f2(), dispatcher.forward(derived_c_)->f2());

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ForwardingTests, all_implemented_const) {
  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  auto derived_a_ = reinterpret_cast<Base*>(derived_a);
  auto derived_b_ = reinterpret_cast<Base*>(derived_b);
  auto derived_c_ = reinterpret_cast<Base*>(derived_c);

  EXPECT_EQ(base->get_id(), dispatcher.forward(base)->get_id());
  EXPECT_EQ(derived_a->get_id(), dispatcher.forward(derived_a_)->get_id());
  EXPECT_EQ(derived_b->get_id(), dispatcher.forward(derived_b_)->get_id());
  EXPECT_EQ(derived_c->get_id(), dispatcher.forward(derived_c_)->get_id());

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ForwardingTests, not_impemented_in_derived) {
  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  auto derived_a_ = reinterpret_cast<Base*>(derived_a);
  auto derived_b_ = reinterpret_cast<Base*>(derived_b);
  auto derived_c_ = reinterpret_cast<Base*>(derived_c);

  EXPECT_EQ(base->f3(), dispatcher.forward(base)->f3());
  EXPECT_EQ(derived_a->f3(), dispatcher.forward(derived_a_)->f3());
  EXPECT_EQ(derived_b->f3(), dispatcher.forward(derived_b_)->f3());
  EXPECT_EQ(derived_c->f3(), dispatcher.forward(derived_c_)->f3());

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}

TEST(ForwardingTests, not_impemented_in_derived_const) {
  auto base = new Base();
  auto derived_a = new DerivedA();
  auto derived_b = new DerivedB();
  auto derived_c = new DerivedC();

  auto derived_a_ = reinterpret_cast<Base*>(derived_a);
  auto derived_b_ = reinterpret_cast<Base*>(derived_b);
  auto derived_c_ = reinterpret_cast<Base*>(derived_c);

  EXPECT_EQ(base->f1(), dispatcher.forward(base)->f1());
  EXPECT_EQ(derived_a->f1(), dispatcher.forward(derived_a_)->f1());
  EXPECT_EQ(derived_b->f1(), dispatcher.forward(derived_b_)->f1());
  EXPECT_EQ(derived_c->f1(), dispatcher.forward(derived_c_)->f1());

  delete base;
  delete derived_a;
  delete derived_b;
  delete derived_c;
}
