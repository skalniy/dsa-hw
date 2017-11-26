#include "stl_wrapper.hxx"

#include <gtest/gtest.h>


class STLWrapperTest : public ::testing::Test {
  protected:
    dsa::stl_wrapper ht;
};

TEST_F(STLWrapperTest, SearchUnexistingKey) {
  EXPECT_FALSE(ht.search(0));
}

TEST_F(STLWrapperTest, InsertUnexistingKey) {
  EXPECT_TRUE(ht.insert(0, 1));
}

TEST_F(STLWrapperTest, EraseUnexistingKey) {
  ASSERT_FALSE(ht.erase(0));
}

TEST_F(STLWrapperTest, SearchExistingKey) {
  ASSERT_TRUE(ht.insert(0, 1));
  EXPECT_EQ(1, ht.search(0));
}

TEST_F(STLWrapperTest, InsertExistingKey) {
  ASSERT_TRUE(ht.insert(0, 1));
  EXPECT_FALSE(ht.insert(0, 2));
}

TEST_F(STLWrapperTest, EraseExistingKey) {
  ASSERT_TRUE(ht.insert(0, 1));
  EXPECT_TRUE(ht.erase(0));
  EXPECT_FALSE(ht.search(0));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
