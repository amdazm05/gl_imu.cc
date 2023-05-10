#ifndef _SPACE_VECTPR_UNITS
#define _SPACE_VECTPR_UNITS

#include <type_traits>
#include <concepts>
#include <memory>
#include <compare>
#include <new>
#include <algorithm>

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


    template<typename T>
    requires _isFloatingType4Byte<T> || _isFloatingType8Byte<T>
    class RadialDegree
    {
        public: 
            T _degree;
            RadialDegree():RadialDegree(0.0f){}
            RadialDegree(T deg) _degree(deg){}
            RadialDegree operator+(const RadialDegree &operand )
            {              
                return this->_degree +operand._degree;
            }
            RadialDegree operator-(const RadialDegree &operand )
            { 
                return this->_degree - operand._degree;
            }
            RadialDegree operator*(const RadialDegree &operand )
            {              
                return this->_degree *operand._degree;
            }
            RadialDegree operator/(const RadialDegree &operand )
            { 
                return this->_degree /operand._degree;
            }

            bool operator==(const RadialDegree &operand) const = default;
            std::partial_ordering operator<=>(const RadialDegree &operand) const
            {
                return std::partial_ordering((this->_degree)<=>operand._degree);
            }

    };

    template<typename T>
    requires _isFloatingType4Byte<T> || _isFloatingType8Byte<T>
    class RadialRadian
    {
        public:
            T _radian;
            RadialRadian():RadialRadian(0.0f){}
            RadialRadian(T deg) RadialRadian(deg){}
            RadialRadian operator+(const RadialRadian &operand )
            {              
                return this->_radian +operand._radian;
            }
            RadialRadian operator-(const RadialRadian &operand )
            { 
                return this->_radian - operand._radian;
            }
            RadialRadian operator*(const RadialRadian &operand )
            {              
                return this->_radian *operand._radian;
            }
            RadialRadian operator/(const RadialRadian &operand )
            { 
                return this->_radian /operand._radian;
            }

            bool operator==(const RadialRadian &operand) const = default;
            std::partial_ordering operator<=>(const RadialRadian &operand) const
            {
                return std::partial_ordering((this->_radian)<=>operand._radian);
            }
    };
    template<class T>
    requires _isFloatingType4Byte<T> || _isFloatingType8Byte<T> 
    class Coordinates
    {
        private:
        enum AxisEnum
        {
            x = 0,
            y = 1,
            z = 2
        };
        public:
        alignas (std::hardware_constructive_interference_size) std::array<T,3> _data;
        public:
        Coordinates():Coordinates(0.0f,0.0f,0.0f){}
        Coordinates(T x,T y, T z)
        {
            _data[AxisEnum::x] = x;
            _data[AxisEnum::y] = y;
            _data[AxisEnum::z] = z;
        }

        Coordinates operator+(Coordinates &operand)
        {         
            int idx = 0;
            Coordinates result;
            std::for_each
            (
                _data.begin(),
                _data.end(),
                [&idx,&operand,&result](T & currentElement)
                { 
                    result._data[idx]= operand._data[idx] + currentElement; 
                    ++idx; 
                }
            );    
            return result;
        }

        Coordinates operator-(Coordinates &operand)
        {         
            int idx = 0;
            Coordinates result;
            std::for_each
            (
                _data.begin(),
                _data.end(),
                [&idx,&operand,&result](T & currentElement)
                { 
                    result._data[idx]= currentElement - operand._data[idx]; 
                    ++idx; 
                }
            );    
            return result;
        }

        std::partial_ordering operator<=>(Coordinates &operand) 
        {
            T resultToCompareRHS = 0.0f;
            T resultToCompareLHS = 0.0f;
            int idx = 0;
            std::for_each
            (
                _data.begin(),
                _data.end(),
                [&resultToCompareLHS,&resultToCompareRHS,&operand,&idx]
                    (T &currentElement)
                    { 
                        resultToCompareLHS = resultToCompareLHS + std::pow(operand._data[idx],2);
                        ++idx;
                        resultToCompareRHS = resultToCompareRHS + std::pow(currentElement,2);
                    }
            );

            return resultToCompareRHS <=> resultToCompareLHS;
        }
    };

    template <class T>
    requires _isFloatingType4Byte<T>
    class SpaceUnits : std::enable_shared_from_this<SpaceUnits<T>>
    {
        public:
        std::shared_ptr<SpaceUnits<T>> getInstance()
        {
            return shared_from_this();
        }
        

        private:
        SpaceUnits(){ _inst = shared_from_this();}
        static std::shared_ptr<SpaceUnits<T>> _inst;
    };
}

#endif //_SPACE_VECTPR_UNITS