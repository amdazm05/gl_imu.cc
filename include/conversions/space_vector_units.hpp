#ifndef _SPACE_VECTPR_UNITS
#define _SPACE_VECTPR_UNITS

#include <type_traits>
#include <concepts>

namespace SpaceUnits
{
    template<class _Type>
    concept _isFloatingType4Byte = requires(_Type)
    {
        requires std::floating_point<_Type> && sizeof(_Type) == 4;
    };
    template<class _Type>
    concept _isFloatingType8Byte = requires(_Type)
    {
        requires std::floating_point<_Type> && sizeof(_Type) == 8;
    };

    template <class T>
    requires _isFloatingType4Byte<T>
    class SpaceUnits
    {
        
    };
}

#endif //_SPACE_VECTPR_UNITS