#include "sensors/wt931.h"

int main()
{
    Wt931ImuHandler ImuHandle("/dev/ttyUSB0");
    char buffer[100];
    int bytesRead = ImuHandle.readAvailableByteFrame(buffer,sizeof(buffer));
    if(bytesRead<0)
    {
        std::cout<<"Nothing could be read"<<std::endl;
    }

    else
    {
        std::cout<<"Copied" <<bytesRead <<" bytes"<<std::endl;
        for(int i=0 ; i <bytesRead;i++)
        {
            std::cout<<std::hex <<(uint16_t)*(buffer+i)<<" ";
        }
        std::cout<<std::endl;
    }
    return 0;
}