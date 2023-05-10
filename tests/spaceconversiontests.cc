#include "gtest/gtest.h"
#include "conversions/space_vector_units.hpp"

namespace
{
    TEST(SpaceConversions, CoordinateConversionTests) 
    {
        SpaceUnits::Coordinates<float> c1(1,2,3);
        SpaceUnits::Coordinates<float> c2(1,2,3);
        SpaceUnits::Coordinates<float> c3(1,2,4);
        SpaceUnits::Coordinates<float> c4(1,2,1);
        auto result1 = (c1 <=> c2);
        auto result2 = (c1 <=> c3);
        auto result3 = (c1 <=> c4);
        EXPECT_EQ(true,  result1 == 0);
        EXPECT_EQ(true,  result2 < 0);
        EXPECT_EQ(true,  result3 > 0);
    }
};