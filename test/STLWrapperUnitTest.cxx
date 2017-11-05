#include "stl_wrapper.hxx"

#include <gtest/gtest.h>


TEST(SearchTest, HandlesUnexistingKey) {
  dsa::stl_wrapper stlw;
  EXPECT_FALSE(stlw.search(0));
}

TEST(InsertTest, HandlesUnexistingKey) {
  dsa::stl_wrapper stlw;
  EXPECT_TRUE(stlw.insert(0, 1));
}

TEST(EraseTest, HandlesUnexistingKey) {
  dsa::stl_wrapper stlw;
  ASSERT_FALSE(stlw.erase(0));
}

TEST(SearchTest, HandlesExistingKey) {
  dsa::stl_wrapper stlw;
  ASSERT_TRUE(stlw.insert(0, 1));
  EXPECT_EQ(1, stlw.search(0));
}

TEST(InsertTest, HandlesExistingKey) {
  dsa::stl_wrapper stlw;
  ASSERT_TRUE(stlw.insert(0, 1));
  EXPECT_FALSE(stlw.insert(0, 2));
}

TEST(EraseTest, HandlesExistingKey) {
  dsa::stl_wrapper stlw;
  ASSERT_TRUE(stlw.insert(0, 1));
  EXPECT_TRUE(stlw.erase(0));
  EXPECT_FALSE(stlw.search(0));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
