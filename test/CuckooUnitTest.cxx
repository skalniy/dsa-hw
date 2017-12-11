#include "cuckoo.hxx"

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#define TESTVAL_CUT 0xABADBABE


class CuckooTest : public ::testing::Test {
  protected:
    CuckooTest() : ht(2) {}

    dsa::cuckoo ht;
};

TEST_F(CuckooTest, SearchUnexistingKey) {
  EXPECT_FALSE(ht.search(0));
}

TEST_F(CuckooTest, InsertUnexistingKey) {
  EXPECT_TRUE(ht.insert(0, TESTVAL_CUT));
}

TEST_F(CuckooTest, EraseUnexistingKey) {
  ASSERT_FALSE(ht.erase(0));
}

TEST_F(CuckooTest, SearchExistingKey) {
  ASSERT_TRUE(ht.insert(0, TESTVAL_CUT));
  EXPECT_EQ(TESTVAL_CUT, *ht.search(0));
}

TEST_F(CuckooTest, InsertExistingKey) {
  ASSERT_TRUE(ht.insert(0, TESTVAL_CUT));
  EXPECT_FALSE(ht.insert(0, TESTVAL_CUT+1));
}

TEST_F(CuckooTest, EraseExistingKey) {
  EXPECT_TRUE(ht.insert(0, TESTVAL_CUT));
  EXPECT_TRUE(ht.erase(0));
  EXPECT_FALSE(ht.search(0));
}

TEST_F(CuckooTest, Rehash) {
  std::vector<int> data = { 10, 22, 31, 4, 15, 28, 17, 88, 59 };
  EXPECT_EQ(0, ht.size());
  for (const auto& key : data)
    {
      ASSERT_FALSE(ht.search(key));
      ASSERT_TRUE(ht.insert(key, key));
      EXPECT_EQ(key, *ht.search(key));
      EXPECT_FALSE(ht.insert(key, key));
    }
  EXPECT_EQ(data.size(), ht.size());
  for (const auto& key : data)
    {
      EXPECT_EQ(key, *ht.search(key));
      ASSERT_TRUE(ht.erase(key));
      EXPECT_FALSE(ht.search(key));
      ASSERT_FALSE(ht.erase(key));
    }
  EXPECT_EQ(0, ht.size());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
