#ifndef GRAPHIC_UTILS
#define GRAPHIC_UTILS

#include <memory>
#include <istream>

namespace GraphicUtils
{
    class FPSBenchmark : std::enable_shared_from_this<FPSBenchmark>
    {   
        public:
            FPSBenchmark();
            ~FPSBenchmark();
            float getFPS();
            //Assume seconds
            void logFPS(std::uint64_t timeInterval);
        private: 
            float _fps;
    };  
    
    // Place more utils to assist heres 
}

#endif // GRAPHIC_UTILS