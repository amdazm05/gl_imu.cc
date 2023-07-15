#include "gtest/gtest.h"
#include "util/containers/circularbuffer.tpp"

namespace
{
    struct Data
    {
        int a;
        int b;
    };
    CircularBuffer<Data,16> _data;
    TEST(EnqueueDequeueTest, CoordinateConversionTests) 
    {
        Data data {1,2};
        _data.enqueue((data));
        Data data2 {3,4};
        _data.enqueue((data2));
        Data data4 = _data.dequeue();
        Data data5 = _data.dequeue();
        EXPECT_EQ(true,  data.a == data4.a);
        EXPECT_EQ(true,  data.b == data4.b);
        EXPECT_EQ(true,  data2.a == data5.a);
        EXPECT_EQ(true,  data2.b == data5.b);
    }
};