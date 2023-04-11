#include "sensors/wt931.h"

Wt931ImuHandler::Wt931ImuHandler(std::string && deviceNamelink)
{
    fd = open (deviceNamelink.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        std::cout<<"Could not open WT931 port "<<std::endl;
    }
    else
    {
        //Default baudrate supported by the sensor
        cfsetospeed(&(this->tty),B921600);
        cfsetispeed (&(this->tty), B921600);
        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout
        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= 0;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr(fd, TCSANOW, &tty) != 0)
        {
            std::cout<<"tcsetattr err "<<errno<<std::endl;
        }
        else
        {
            std::memset(&tty, 0, sizeof tty);
            if (tcgetattr (fd, &tty) != 0)
            {
                    std::cout<<"Non blocking tggetattr" <<errno<<std::endl;
            }
            else
            {
                //Sets blocking
                tty.c_cc[VMIN]  = 0;
                tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

                if (tcsetattr (fd, TCSANOW, &tty) != 0)
                        std::cout<<"error %d setting term attributes "<< errno<<std::endl;
            }
        }
        //Courtesy 
        ///https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
    }   
    
}

Wt931ImuHandler::~Wt931ImuHandler()
{
    close(fd);
}

uint32_t Wt931ImuHandler::readAvailableByteFrame(char * buffer,std::size_t sizeofBuffer)
{
    uint32_t bytesToReturn;
    bytesToReturn= read (this->fd, buffer,sizeofBuffer);
    return std::move(bytesToReturn);
}