#include "double_hash.hxx"

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#define TESTVAL_DHUT 0xDEFEC8ED


class DoubleHashTest : public ::testing::Test {
  protected:
    DoubleHashTest() : ht(8) {}

    dsa::double_hash ht;
};

TEST_F(DoubleHashTest, SearchUnexistingKey) {
  EXPECT_FALSE(ht.search(0));
}

TEST_F(DoubleHashTest, InsertUnexistingKey) {
  EXPECT_TRUE(ht.insert(0, TESTVAL_DHUT));
}

TEST_F(DoubleHashTest, EraseUnexistingKey) {
  ASSERT_FALSE(ht.erase(0));
}

TEST_F(DoubleHashTest, SearchExistingKey) {
  ASSERT_TRUE(ht.insert(0, TESTVAL_DHUT));
  EXPECT_EQ(TESTVAL_DHUT, *ht.search(0));
}

TEST_F(DoubleHashTest, InsertExistingKey) {
  ASSERT_TRUE(ht.insert(0, TESTVAL_DHUT));
  EXPECT_FALSE(ht.insert(0, TESTVAL_DHUT+1));
}

TEST_F(DoubleHashTest, EraseExistingKey) {
  ASSERT_TRUE(ht.insert(0, TESTVAL_DHUT));
  EXPECT_TRUE(ht.erase(0));
  EXPECT_FALSE(ht.search(0));
}

TEST_F(DoubleHashTest, Rehash) {
  std::vector<int> data = { 10, 22, 31, 4, 15, 28, 17, 88, 59 };
  EXPECT_EQ(0, ht.size());
  for (const auto& key : data)
    {
      ASSERT_FALSE(ht.search(key));
      ASSERT_TRUE(ht.insert(key, TESTVAL_DHUT));
      EXPECT_EQ(TESTVAL_DHUT, *ht.search(key));
      EXPECT_FALSE(ht.insert(key, TESTVAL_DHUT));
    }
  EXPECT_EQ(data.size(), ht.size());
  for (const auto& key : data)
    {
      EXPECT_EQ(TESTVAL_DHUT, *ht.search(key));
      ASSERT_TRUE(ht.erase(key));
      EXPECT_FALSE(ht.search(key));
      ASSERT_FALSE(ht.erase(key));
    }
  EXPECT_EQ(0, ht.size());
}

TEST_F(DoubleHashTest, Print) {
  std::string ans = R"([0]DELETED
[1]8 3
[2]
[3]
[4]
[5]
[6]
[7]
)";
  ht.insert(0, 1);
  ht.insert(8, 3);
  ht.erase(0);
  std::stringstream res;
  res << ht;
  std::string s;
  std::getline(res, s, '\0');
  EXPECT_EQ(ans, s);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
