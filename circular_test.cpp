#include <gtest/gtest.h>
#include "circular_list.hpp"
#include <vector>
#include <string>

TEST(CircularListTest, EmptyList)
{
    CircularList<int> list;
    
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}

TEST(CircularListTest, Constructors)
{
    CircularList<int> list1;
    EXPECT_TRUE(list1.empty());
    
    CircularList<int> list2 = {1, 2, 3, 4, 5};
    EXPECT_EQ(list2.size(), 5);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 5);
    
    CircularList<int> list3(list2);
    EXPECT_EQ(list3.size(), 5);
    EXPECT_EQ(list3.front(), 1);
    
    CircularList<int> list4(std::move(list3));
    EXPECT_EQ(list4.size(), 5);
    EXPECT_TRUE(list3.empty());
}

TEST(CircularListTest, AssignmentOperators)
{
    CircularList<int> list1 = {1, 2, 3};
    CircularList<int> list2;
    
    list2 = list1;
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front(), 1);
    
    CircularList<int> list3;
    list3 = std::move(list2);
    EXPECT_EQ(list3.size(), 3);
    EXPECT_TRUE(list2.empty());
    
    list3 = {4, 5, 6};
    EXPECT_EQ(list3.front(), 4);
    EXPECT_EQ(list3.back(), 6);
}

TEST(CircularListTest, PushOperations)
{
    CircularList<int> list;
    
    list.push_back(1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);
    
    list.push_back(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
    
    list.push_front(0);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), 2);
}

TEST(CircularListTest, PopOperations)
{
    CircularList<int> list = {1, 2, 3};
    
    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 3);
    
    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 2);
    
    list.pop_back();
    EXPECT_TRUE(list.empty());
}


TEST(CircularListTest, ElementAccess)
{
    CircularList<int> list = {10, 20, 30};
    
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 30);
    
    list.front() = 100;
    list.back() = 300;
    EXPECT_EQ(list.front(), 100);
    EXPECT_EQ(list.back(), 300);
}

TEST(CircularListTest, Iterators)
{
    CircularList<int> list = {1, 2, 3, 4, 5};
    
    std::vector<int> result;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        result.push_back(*it);
    }
    EXPECT_EQ(result, std::vector<int>({1, 2, 3, 4, 5}));
    
    result.clear();
    for (int value : list)
    {
        result.push_back(value);
    }
    EXPECT_EQ(result, std::vector<int>({1, 2, 3, 4, 5}));
    
    result.clear();
    for (auto it = list.rbegin(); it != list.rend(); ++it)
    {
        result.push_back(*it);
    }
    EXPECT_EQ(result, std::vector<int>({5, 4, 3, 2, 1}));
}

TEST(CircularListTest, InsertAndErase)
{
    CircularList<int> list = {1, 3, 5};
    
    auto it = list.insert(list.begin(), 0);
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.size(), 4);
    
    it = list.begin();
    ++it; ++it;
    it = list.insert(it, 2);
    EXPECT_EQ(*it, 2);
    
    std::vector<int> expected = {0, 1, 2, 3, 5};
    std::vector<int> actual;
    for (int x : list) actual.push_back(x);
    EXPECT_EQ(actual, expected);
    
    it = list.begin();
    ++it;
    it = list.erase(it);
    EXPECT_EQ(*it, 2);
    
    expected = {0, 2, 3, 5};
    actual.clear();
    for (int x : list) actual.push_back(x);
    EXPECT_EQ(actual, expected);
}

TEST(CircularListTest, Clear)
{
    CircularList<int> list = {1, 2, 3, 4, 5};
    
    EXPECT_FALSE(list.empty());
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}

TEST(CircularListTest, Swap)
{
    CircularList<int> list1 = {1, 2, 3};
    CircularList<int> list2 = {4, 5, 6, 7};
    
    list1.swap(list2);
    
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list1.front(), 4);
    EXPECT_EQ(list2.front(), 1);
}

TEST(CircularListTest, Assign)
{
    CircularList<int> list;
    
    list.assign(3, 42);
    EXPECT_EQ(list.size(), 3);
    for (int x : list) 
    {
        EXPECT_EQ(x, 42);
    }
    
    list.assign({100, 200, 300});
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 100);
    EXPECT_EQ(list.back(), 300);
}

TEST(CircularListTest, ComparisonOperators)
{
    CircularList<int> list1 = {1, 2, 3};
    CircularList<int> list2 = {1, 2, 3};
    CircularList<int> list3 = {1, 2, 4};
    CircularList<int> list4 = {1, 2};
    
    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 == list3);
    EXPECT_TRUE(list1 != list3);
    
    EXPECT_TRUE(list1 < list3);
    EXPECT_TRUE(list3 > list1);
    EXPECT_TRUE(list4 < list1);
    
    EXPECT_TRUE(list1 <= list2);
    EXPECT_TRUE(list1 >= list2);
    EXPECT_TRUE(list1 <= list3);
    EXPECT_TRUE(list3 >= list1);
}

TEST(CircularListTest, Exceptions)
{
    CircularList<int> list;
    
    EXPECT_THROW(list.front(), std::runtime_error);
    EXPECT_THROW(list.back(), std::runtime_error);
    
    EXPECT_THROW(list.pop_front(), std::runtime_error);
    EXPECT_THROW(list.pop_back(), std::runtime_error);
    
    list.push_back(1);
    EXPECT_NO_THROW(list.front());
    EXPECT_NO_THROW(list.back());
    
    auto it = list.begin();
    EXPECT_NO_THROW(*it);
    EXPECT_NO_THROW(++it);
    
    auto end_it = list.end();
    EXPECT_THROW(*end_it, std::runtime_error);
    EXPECT_THROW(++end_it, std::runtime_error);
}

TEST(CircularListTest, CopyWithElements)
{
    CircularList<int> original = {1, 2, 3, 4, 5};
    CircularList<int> copy = original;
    
    EXPECT_EQ(original.size(), copy.size());
    
    auto it1 = original.begin();
    auto it2 = copy.begin();
    while (it1 != original.end() && it2 != copy.end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
    
    copy.front() = 100;
    EXPECT_EQ(original.front(), 1);
    EXPECT_EQ(copy.front(), 100);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
