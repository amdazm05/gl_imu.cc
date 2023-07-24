#ifndef _CIRCULAR_BUFFER
#define _CIRCULAR_BUFFER

#include <iostream>
#include <mutex>
#include <array>

constexpr int threadedsafetymode = 1;

template<class TypeOfBuffer, std::size_t sizeOfBuffer, int threadedmode = threadedsafetymode>
class CircularBuffer
{
    private:
        std::size_t _tail;
        std::size_t _head;
        std::mutex _mtx;
        std::size_t _length;
        std::array<TypeOfBuffer,sizeOfBuffer> _buffer;
    public:
        CircularBuffer()
        {
            _tail = 0;
            _head = sizeOfBuffer-1;
            _length = 0;
        }
        void enqueue(TypeOfBuffer&object) noexcept
        {
            if constexpr (threadedmode)
            {
                    std::lock_guard<std::mutex> _lock(_mtx);
                    _head = operator++(int(_head));
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
                    std::lock_guard<std::mutex> _lock(_mtx);
                    TypeOfBuffer valToReturn = _buffer[_tail];
                    _tail = operator++(int(_tail));;
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
            return _length == sizeOfBuffer;
        }
    public:
        std::size_t operator++(int  position)
        {
            return (position +1) % sizeOfBuffer;
        }
};

template<class TypeOfBuffer, std::size_t sizeOfBuffer, int threadedmode = threadedsafetymode>
class CircularBuffer_Dynamic
{
    private:
        std::size_t _tail;
        std::size_t _head;
        std::mutex _mtx;
        std::size_t _length;
        std::vector<TypeOfBuffer> _buffer;
    public:
        CircularBuffer_Dynamic()
        {
            _tail = 0;
            _head = sizeOfBuffer-1;
            _length = 0;
            _buffer.resize(sizeOfBuffer);
        }
        void enqueue(TypeOfBuffer&object) noexcept
        {
            if constexpr (threadedmode)
            {
                    std::lock_guard<std::mutex> _lock(_mtx);
                    _head = operator++(int(_head));
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
        void resize(std::size_t sizeToResize)
        {
            _buffer.resize(sizeToResize);
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
                    std::lock_guard<std::mutex> _lock(_mtx);
                    TypeOfBuffer valToReturn = _buffer[_tail];
                    _tail = operator++(int(_tail));;
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
            return _length == sizeOfBuffer;
        }
    public:
        std::size_t operator++(int  position)
        {
            return (position +1) % sizeOfBuffer;
        }
};



#endif //_CIRCULAR_BUFFER