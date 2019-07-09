#include "gtest/gtest.h"

TEST(example, add)
{
    double res;
    res= 2.0 + 2.0;
    ASSERT_NEAR(res, 4.0, 1.0e-11);
}
