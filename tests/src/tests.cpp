#include "flat.cpp"
#include "poly.hpp"
#include "gtest/gtest.h"

__poly_decl_group(Group, {
  __dispatch(get_id);
  __dispatch(f1);
});

using namespace flat;
using group_t = Group<Base, ChildA, ChildB, ChildC>;

TEST(FlatInhTests, all_implemented_const) {
  auto base = new Base();
  auto child_a = new ChildA();
  auto child_b = new ChildB();
  auto child_c = new ChildC();

  auto child_a_ = static_cast<Base*>(child_a);
  auto child_b_ = static_cast<Base*>(child_b);
  auto child_c_ = static_cast<Base*>(child_c);

  EXPECT_NE(base->get_id(), static_cast<group_t*>(child_a_)->get_id());
  EXPECT_NE(base->get_id(), static_cast<group_t*>(child_b_)->get_id());
  EXPECT_NE(base->get_id(), static_cast<group_t*>(child_c_)->get_id());

  delete base;
  delete child_a;
  delete child_b;
  delete child_c;
}

// TEST(FlatInhTests, not_impemented_in_derived_const) {

//   auto base = new Base();
//   auto child_a = new ChildA();
//   auto child_b = new ChildB();
//   auto child_c = new ChildC();

//   auto child_a_ = static_cast<Base*>(child_a);
//   auto child_b_ = static_cast<Base*>(child_b);
//   auto child_c_ = static_cast<Base*>(child_c);

//   EXPECT_EQ(base->f1(), child_a_->f1());
//   EXPECT_EQ(base->f1(), child_b_->f1());
//   EXPECT_EQ(base->f1(), child_c_->f1());

//   delete base;
//   delete child_a;
//   delete child_b;
//   delete child_c;
// }

// TEST(FlatInhTests, abstract) {

//   auto base = new Base();
//   auto child_a = new ChildA();
//   auto child_b = new ChildB();
//   auto child_c = new ChildC();

//   auto child_a_ = static_cast<Base*>(child_a);
//   auto child_b_ = static_cast<Base*>(child_b);
//   auto child_c_ = static_cast<Base*>(child_c);

//   EXPECT_EQ(child_a_->f2(2, 2), 4);
//   EXPECT_THROW(base->f2(2, 2), std::logic_error);
//   EXPECT_THROW(child_b_->f2(2, 2), std::logic_error);
//   EXPECT_THROW(child_c_->f2(2, 2), std::logic_error);

//   delete base;
//   delete child_a;
//   delete child_b;
//   delete child_c;
// }
