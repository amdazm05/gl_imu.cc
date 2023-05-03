#include "gtest/gtest.h"
#include "stream/serialstreamer.hpp"
namespace 
{
    BufferCoroutine<char *> coro()
    {
        std::string buffer = "BufferTest";
        std::string::iterator bufferIt(buffer.begin());
        while(bufferIt!=buffer.end())
        {
            co_yield &(*bufferIt);
            bufferIt++;
        }
    }

    std::string RunCoroutineBufferTest()
    {
        std::string result;
        BufferCoroutine<char *> co = coro();
        while(1)
        {
            if(!co.m_handle.done())
            {
                co.m_handle();
                char character = *(co.m_handle.promise().m_value.value());
                result += character;
                // result.append();
            }
            else
            {
                break;
            }
        }
        return result;
    }

    TEST(FactorialTest, CoroutineBufferTest) 
    {
        EXPECT_EQ("BufferTest", RunCoroutineBufferTest());
    }
}
