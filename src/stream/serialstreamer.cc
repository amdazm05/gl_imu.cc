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
        if(GetCommState(hCom,&dcb)==false)
        {
            std::runtime_error("Unable to get State of the COMM Port " + string);
        }

        dcb.BaudRate = 921600;      // Setting BaudRate = 9600
        dcb.ByteSize = 8;             // Setting ByteSize = 8
        dcb.StopBits = ONESTOPBIT;    // Setting StopBits = 1
        dcb.Parity = NOPARITY;        // Setting Parity = None 

        COMMTIMEOUTS timeouts = { 0 };
        timeouts.ReadIntervalTimeout         = 1000;
        timeouts.ReadTotalTimeoutConstant    = 0;
        timeouts.ReadTotalTimeoutMultiplier  = 0;
        timeouts.WriteTotalTimeoutConstant   = 0;
        timeouts.WriteTotalTimeoutMultiplier = 0;

        if (SetCommTimeouts(hCom, &timeouts) == false)
        {
            std::runtime_error("Unable to set COM timeouts");
        }


    }

    bool WindowsSerialStreamer::isAValidPacketAvailable()
    {
        return {};
    }

    std::size_t WindowsSerialStreamer::ReadAvailableData()
    {
        BOOL Status; 
        DWORD bytesRecievedCount = -1;
            
        if (Status == false)
        {
            //Error reading COM Port
             std::runtime_error("Unable to set COM timeouts");
        }
        else
        {
            do
            {
                Status = ReadFile(hCom, recieveBuffer.data(), sizeof(char)*recieveBuffer.size(), &bytesRecievedCount, nullptr);
                if(Status==true)
                {
                    if(bytesRecievedCount>0)
                    {
                        break;
                    }
                }
                
            }while (bytesRecievedCount);
            
            for (int j = 0; j < bytesRecievedCount; j++)      
                std::cout<<std::hex<<(std::uint16_t)recieveBuffer[j]<<" "<<std::dec;
        }   

        return std::size_t(bytesRecievedCount);
    }

    void WindowsSerialStreamer::writeData(std::shared_ptr<char> dataToWrite, std::size_t bytesToWrite)
    {
        
    }
#endif