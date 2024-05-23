#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include <gtest/gtest.h>
#include <iostream>
#include "circular_buffer.h"
using namespace std;

struct CircularBufferTest : public testing::Test
{
    CircularBuffer a = CircularBuffer(5);
};

bool run_try_catch(std::function<void()> f)
{
    bool result = false;
    try
    {
        f();
    }
    catch (const std::exception& e)
    {
        result = true;
    }

    return result;
}

TEST_F(CircularBufferTest, init_class_test)
{
    // Act
    size_t actual_length_of_cont = a.capacity();
    size_t num_of_available_slots = a.reserve();
    //// Asserts
    EXPECT_EQ(actual_length_of_cont, 6);
    EXPECT_EQ(num_of_available_slots, 5);
}
TEST_F(CircularBufferTest, check_pushes) {
    a.push_back(321);
    a.push_front(123);
    EXPECT_EQ(a.at(0), 321);
    EXPECT_EQ(a.at(5), 123);
}

TEST_F(CircularBufferTest, check_pop)
{
    a.push_back(321);
    a.push_back(123);
    EXPECT_EQ(a.start_val, 0);
    a.pop_front();
    EXPECT_EQ(a.start_val, 1);
    a.pop_back();
    EXPECT_EQ(a.end_val, 1);
}

TEST_F(CircularBufferTest, check_linearize)
{
    a.push_back(123);
    a.push_back(321);
    a.push_front(228);
    EXPECT_EQ(a.is_linearized(), false);
    a.linearize();
    EXPECT_EQ(a[0], 228);
    EXPECT_EQ(a.is_linearized(), true);
}

TEST_F(CircularBufferTest, test_clear)
{
    a.push_back(123);
    a.push_back(321);
    a.push_front(228);
    EXPECT_EQ(a.size(), 3);
    a.clear();
    EXPECT_EQ(a.size(), 0);
}

TEST(resize_test, resize_test)
{
    CircularBuffer b = CircularBuffer(5);
    EXPECT_EQ(b.capacity(), 6);
    b.resize(10);
    EXPECT_EQ(b.capacity(), 11);
    b.resize(2);
    EXPECT_EQ(b.capacity(), 3);
}

TEST(set_capacity, set_capacity)
{
    CircularBuffer b = CircularBuffer(2);
    EXPECT_EQ(b.capacity(), 3);
    b.set_capacity(10);
    EXPECT_EQ(b.capacity(), 11);
}

TEST(check_empty, check_empty) {
    CircularBuffer b = CircularBuffer(5);
    EXPECT_EQ(b.empty(), true);
    b.push_back(321);
    b.pop_front();
    EXPECT_EQ(b.empty(), true);
}
TEST(check_full, check_full) {
    CircularBuffer b = CircularBuffer(5);
    b.push_back(321);
    b.push_back(321);
    b.push_back(321);
    b.push_back(321);
    b.push_back(321);
    EXPECT_EQ(b.full(), true);
    b.pop_back();
    EXPECT_EQ(b.full(), false);
}
TEST(check_rotate, check_rotate) {
    CircularBuffer b = CircularBuffer(5);
    b.push_back(321);
    b.push_back(123);
    b.push_back(22);
    b.push_back(33);
    b.push_back(44);
    b.rotate(2);
    EXPECT_EQ(b[0], 22);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);


	return RUN_ALL_TESTS();
}
