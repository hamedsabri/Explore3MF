#include "gtest/gtest.h"

TEST(example, subtract)
{
    double res;
    res = 1.0 - 3.0;
    ASSERT_NEAR(res, -2.0, 1.0e-11);
}
