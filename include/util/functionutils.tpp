#ifndef _DISPATCHER
#define _DISPATCHER
#include <concepts>
#include <type_traits>
namespace function_utils
{
    /// @brief to deal with C styled function pointer
    /// @tparam functype 

    template <class functype> 
    concept _isFunctionPointer = requires(functype)
    {
        requires std::is_pointer<functype>::value &&
                std::is_function<typename std::remove_pointer<functype>::type>::value;
    };

    template<class functype>
    requires _isFunctionPointer<functype>
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

// https://godbolt.org/z/KW76T5TKz