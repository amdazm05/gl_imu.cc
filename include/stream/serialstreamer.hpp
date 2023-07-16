#ifndef _SERIALSTREAMER
#define _SERIALSTREAMER

#include <array>
#include <string>
#include <memory>
#include <vector>
#include <concepts>
#include <coroutine>
#include <iostream>
#include <exception>
#include <optional>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <windows.h>
    #include <tchar.h>
    #include <winbase.h>
#endif

    template<class T>
    concept _IsBufferType = std::is_pointer<T>::value;

    template <class T>
    requires _IsBufferType<T>
    class BufferCoroutine
    {
        public:
            class promise_type
            {
                public:
                std::optional<T> m_value;
                BufferCoroutine<T> get_return_object()
                {
                    return BufferCoroutine<T>(this); 
                }
                std::suspend_always initial_suspend() noexcept
                {
                    return {};
                }
                std::suspend_always final_suspend() noexcept
                {
                    return {};
                }
                std::suspend_always yield_value(T value)
                {
                    m_value = value;
                    return {};
                }
                void return_value(T value){ m_value = value;}
                void unhandled_exception(){};
            };
        public:
            //Underlying issue here
            BufferCoroutine(promise_type* promise)
                : m_handle(std::coroutine_handle<promise_type>::from_promise(*promise))
            {
                
            }
            
            ~BufferCoroutine()
            {
                m_handle.destroy();
            }
        public:
            std::coroutine_handle<promise_type> m_handle;
    };


    template<class D>
    class SerialStreamer: std::enable_shared_from_this<SerialStreamer<D>>
    {
        public:
            SerialStreamer()
            {

            }
            ~SerialStreamer()
            {

            }
            void enableDelimeterSearchMode(bool condition)
            {
                static_cast<D*>(this)->enableDelimeterSearchMode(condition);
            }
            void setListOfDelimitersToFind(std::vector<uint32_t> && listofDelimiters)
            {
                static_cast<D*>(this)->setListOfDelimitersToFind(listofDelimiters);
            }
            void init(std::string && string,std::uint32_t baudRate=115200)
            {
                static_cast<D*>(this)->init(std::move(string),baudRate);
            }   
            bool isAValidPacketAvailable()
            {
                return static_cast<D*>(this)->isAValidPacketAvailable();
            }
            std::size_t ReadAvailableData()
            {
                return static_cast<D*>(this)->ReadAvailableData();
            }
            void writeData(std::shared_ptr<char> dataToWrite, std::size_t bytesToWrite)
            {

            }
        protected:
            //Must be a deterministic
            std::vector<uint32_t> listofDelimiters;
            std::array<char,1<<16> recieveBuffer;
            std::unique_ptr<char> currentBufferLocation;
            D * child;

            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            DCB dcb;
            HANDLE hCom;
            BOOL fSuccess;
            TCHAR *pcCommPort;
            #endif
    };

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    class WindowsSerialStreamer : public SerialStreamer<WindowsSerialStreamer>
    {
        public:
            WindowsSerialStreamer();
            ~WindowsSerialStreamer();
            void enableDelimeterSearchMode(bool condition);
            void setListOfDelimitersToFind(std::vector<uint32_t> && listofDelimiters);
            void init(std::string && string,std::uint32_t baudRate);
            bool isAValidPacketAvailable();
            std::size_t ReadAvailableData();
            void writeData(std::shared_ptr<char> dataToWrite, std::size_t bytesToWrite);
    };
    #endif
/// Needing a non blocking mode
/// https://stackoverflow.com/questions/17217032/reading-blocking-mode-from-com-port-rs232
#endif