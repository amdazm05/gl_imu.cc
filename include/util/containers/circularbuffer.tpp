#ifndef _CIRCULAR_BUFFER
#define _CIRCULAR_BUFFER

#include <iostream>
#include <mutex>

constexpr int threadedsafetymode = 1;

template<class TypeOfBuffer, std::size_t sizeOfBuffer, int threadedmode = threadedsafetymode>
class CircularBuffer
{
    //Array// Buffer of Objects
    private:
        uint32_t _tail;
        uint32_t _head;
        std::mutex _mtx;
        using  _readwriteLock std::unique_lock<std::mutex>;
        std::array<TypeOfBuffer,sizeofBuffer> _buffer;
    private:
        CircularBuffer()
        {
            _tail = sizeOfBuffer;
            _head = sizeOfBuffer;
        }
        void enqueue(T&&object) noexcept
        {
            if constexpr (threadedmode)
            {
                std::lock_guard<_readwriteLock> lock;
                

            }
            else
            {


            }
        }
        T && dequeue()
        {

        }
    public:
        uint32_t operator++(uint32_t & position)
        {
            return (position % sizeOfBuffer)+1;
        }
};

#endif //_CIRCULAR_BUFFER