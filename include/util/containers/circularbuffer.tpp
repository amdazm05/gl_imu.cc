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
        uint32_t _length;
        std::array<TypeOfBuffer,sizeofBuffer> _buffer;
    private:
        CircularBuffer()
        {
            _tail = 0;
            _head = sizeOfBuffer-1;
            _length = 0;
        }
        void enqueue(TypeOfBuffer&&object) noexcept
        {
            if constexpr (threadedmode)
            {
                std::lock_guard<_readwriteLock> lock;
                    _head++;
                    _buffer[_head]= object;
                    if(full())
                    {
                        _tail = _tail++;
                    }
                    else
                    {
                        _length+=1;
                    }
            }
            else
            {
                static_assert("Thread Safety is off please consider turning it ON");
            }
        }
        TypeOfBuffer dequeue()
        {
            if constexpr (threadedmode)
            {
                if(empty())
                {
                    throw std::runtime_error("Queue empty !");
                    
                }
                else
                {
                    std::lock_guard<_readwriteLock> lock;
                    TypeOfBuffer valToReturn = _buffer[_tail];
                    _tail = _tail++;
                    _length--;
                    return valToReturn;
                }
            }
            else
            {
                 return {};
            }
        }
        inline bool empty()
        {
            return (_length == 0);
        }
        inline bool full()
        {
            return _length == sizeofBuffer;
        }
    public:
        uint32_t operator++(uint32_t & position)
        {
            return (position +1) % sizeOfBuffer;
        }
};

#endif //_CIRCULAR_BUFFER