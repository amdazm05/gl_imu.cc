#include "stream/serialstreamer.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   

    WindowsSerialStreamer::WindowsSerialStreamer()
    :SerialStreamer<WindowsSerialStreamer>()
    {
        hCom = nullptr;
    }
    WindowsSerialStreamer::~WindowsSerialStreamer()
    {

    }

    void WindowsSerialStreamer::enableDelimeterSearchMode(bool condition)
    {

    }

    void WindowsSerialStreamer::init(std::string && string)
    {
        // Opens the file descriptor AKA COM Port
        hCom = CreateFileA(
            string.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0, // Shared mode
            nullptr,
            OPEN_EXISTING,
            0,
            nullptr
         );

        dcb.DCBlength = sizeof(dcb);
        //Gets the state of the COM port in question
        GetCommState(hCom,&dcb);


    }

    bool WindowsSerialStreamer::isAValidPacketAvailable()
    {
        return {};
    }

    template<typename T>
    std::size_t WindowsSerialStreamer::ReadAvailableData( T * dataBufferToReadTo)
    {
        return {};
    }

    void WindowsSerialStreamer::writeData(std::shared_ptr<char> dataToWrite, std::size_t bytesToWrite)
    {
        
    }
#endif