#ifndef _WT931
#define _WT931

#include <string>
#include <vector>
#include <iostream>

#include <cstring>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h> 

class Wt931ImuHandler
{
    public:
        Wt931ImuHandler() = delete;
        /// @brief Opens the device from the device tree //default baudrate is 921600
        /// @param deviceNamelink assumes a linux device for now 
        Wt931ImuHandler(std::string && deviceNamelink);
        uint32_t readAvailableByteFrame(char * buffer, std::size_t sizeofBuffer);

        //Clear any memory
        ~Wt931ImuHandler();
        void set9AxisMode();
        void set6AxisMode();
    private:
        std::string deviceName;
        int fd;
        termios tty;
};

#endif