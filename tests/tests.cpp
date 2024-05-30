#include <gtest/gtest.h>
#include "../funcs.h"

TEST(FirstTest, FuncTests) {
    EXPECT_EQ(my_sum(2, 5), 7);
    ASSERT_EQ(my_sub(4,5), -1);
}

TEST(SecondTest, ZeroTests){
    ASSERT_EQ(my_zero(), 0);
}

TEST(TherdTest, CheckActions){
    EXPECT_EQ(my_sum(2, 2), 5);
}