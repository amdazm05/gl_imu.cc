#ifndef _DISPATCHER
#define _DISPATCHER
namespace function_utils
{
    /// @brief to deal with C styled function pointer
    /// @tparam functype 
    template<class functype>
    class function_ptr
    {
        private:
            functype _funcPtr;
        public:
            void operator =(functype functionPointer)
            {
                _funcPtr = functionPointer;
            }

            functype get()
            {
                return _funcPtr;
            }
    };
}

#endif //_DISPATCHER