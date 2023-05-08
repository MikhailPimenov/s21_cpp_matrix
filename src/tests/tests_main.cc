#include <gtest/gtest.h>
#include <iostream>

int factorial(int n) {
	return (n == 0) || (n == 1) ? 1 : n* factorial(n - 1);
}

TEST(FactorialTest, ZeroInput) {
	EXPECT_EQ(factorial(0), 1);
}

TEST(FactorialTest, PositiveInput) {
	EXPECT_EQ(factorial(1), 1);
	EXPECT_EQ(factorial(2), 2);
	EXPECT_EQ(factorial(3), 6);
	EXPECT_EQ(factorial(8), 40320);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
