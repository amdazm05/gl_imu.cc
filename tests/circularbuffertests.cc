#include <iostream>
#include "util/containers/circularbuffer.tpp"

struct Data
{
    int a;
    int b;
};

int main()
{
    CircularBuffer<Data,16> _data;
    Data data {1,2};
    _data.enqueue((data));
    Data data2 {1,2};
    _data.enqueue((data2));
    return 0;
}