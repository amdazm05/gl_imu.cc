#ifndef _SERIALSTREAMER
#define _SERIALSTREAMER

#include <array>
#include <string>
#include <memory>
#include <vector>

    template<class D>
    class SerialStreamer
    {
        public:
            SerialStreamer();
            ~SerialStreamer();
            void enableDelimeterSearchMode(bool condition);
            void setListOfDelimitersToFind(std::vector<uint32_t> && listofDelimiters);
            void init(std::string && string);
            bool isAValidPacketAvailable();
            template<typename T>
            std::size_t ReadAvailableData( T * dataBufferToReadTo);
            void writeData(std::shared_ptr<char> dataToWrite, std::size_t bytesToWrite);
        private:
            std::vector<uint32_t> listofDelimiters;
            std::array<char,1<<16> recieveBuffer;
            std::unique_ptr<char> currentBufferLocation;
            D * child;
    };

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    
    class WindowsSerialStreamer : SerialStreamer<WindowsSerialStreamer>
    {
        public:
            WindowsSerialStreamer();
            ~WindowsSerialStreamer();
            void enableDelimeterSearchMode(bool condition);
            void setListOfDelimitersToFind(std::vector<uint32_t> && listofDelimiters);
            void init(std::string && string);
            bool isAValidPacketAvailable();
            template<typename T>
            std::size_t ReadAvailableData( T * dataBufferToReadTo);
            void writeData(std::shared_ptr<char> dataToWrite, std::size_t bytesToWrite);
    };


    #endif

#endif