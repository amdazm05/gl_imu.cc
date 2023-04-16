#ifndef _WT931
#define _WT931

#include <string>
#include <vector>
#include <iostream>

#include <cstring>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h> 

struct Wt931AccelerationStructure
{
    uint8_t header;
    uint8_t mode;
    uint8_t AxL;
    uint8_t AxH;
    uint8_t AyL;
    uint8_t AyH;
    uint8_t AzL;
    uint8_t AzH;
    uint8_t TL;
    uint8_t TH;
    uint8_t checksum;
};

struct Wt931AngularVelocityStructure
{
    uint8_t header;
    uint8_t mode;
    uint8_t wxL;
    uint8_t wxH;
    uint8_t wyL;
    uint8_t wyH;
    uint8_t wzL;
    uint8_t wzH;
    uint8_t TL;
    uint8_t TH;
    uint8_t checksum;
};

struct Wt931AngleOutputStructure
{
    uint8_t header;
    uint8_t mode;
    uint8_t rollL;
    uint8_t rollH;
    uint8_t pitchL;
    uint8_t pitchH;
    uint8_t yawL;
    uint8_t yawH;
    uint8_t VL;
    uint8_t VH;
    uint8_t checksum;
};

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
        void setBaudRate(uint32_t baudrate);
        void setRefreshRate(uint32_t setRefreshRate);
        void setDefaultSettings();
    private:
        void saveConfiguration();
        std::string deviceName;
        int fd;
        termios tty;
};

#endif