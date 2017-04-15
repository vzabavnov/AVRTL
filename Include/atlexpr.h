/*
 * atlexpr.h
 *
 * Created: 3/31/2017 12:34:00 AM
 *  Author: Vadim Zabavnov
 */ 

#ifndef ATLEXPR_H_
#define ATLEXPR_H_

#ifndef  __cpp_constexpr
#error At least C++11 is requered
#endif

namespace atl {
namespace expr {

/// <summary>
/// create mask for a single bit specified
/// </summary>
template<typename T, int bit>
constexpr inline T CreateBitMask() {
	return  bit < 0 ? 0 : ((T)1) << bit;
}

/// <summary>
/// create mask for specified bits
/// </summary>
template<typename T, int bit1, int bit2, int... pins>
constexpr inline T CreateBitMask() {
	return CreateBitMask<T, bit1>() | CreateBitMask<T, bit2, pins...>();
}

template<typename T>
constexpr inline T CreateMask(int length, int offset = 0) {
	return length <= 0 	? T(0) : CreateMask<T>(length - 1, offset);
}

template <typename DataType, int length, int offset = 0>
constexpr inline DataType ConvertToValueWithLengthAndOffset(const DataType value) {
	return (value << offset) & CreateMask<DataType>(length, offset);
}

template <typename DataType, int length, int offset = 0>
constexpr inline DataType ConvertFromValieWithLengthAndOffset(const DataType value) {
	return (value & CreateMask<DataType>(length, offset)) >> offset;
}

template<typename T>
constexpr inline T ConvertValueFromPins(T const value) {
	return  T(0);
}

/// <summary>
/// convert value from specified pins to a number
/// </summary>
template<typename T, int pin, int... pins>
constexpr inline T ConvertValueFromPins(T const value) {
	return ((pin > sizeof...(pins))
			? (value & CreateBitMask<T, pin>()) >> (pin - sizeof...(pins))
			: (value & CreateBitMask<T, pin>()) << (sizeof...(pins) - pin))
		| ConvertValueFromPins<T, pins...>(value);
}

template<typename T>
constexpr inline T ConvertValueToPins(T const value) {
	return  T(0);
}

/// <summary>
/// convert specified value to specified pins
/// </summary>
template<typename T, int pin, int... pins>
constexpr inline T ConvertValueToPins(T const value) {
	return ((pin > sizeof...(pins))
			? (value & CreateBitMask<T, sizeof...(pins)>()) << (pin - sizeof...(pins))
			: (value & CreateBitMask<T, sizeof...(pins)>()) >> (sizeof...(pins) - pin)) 
		| ConvertValueToPins<T, pins...>(value);
}

}
}

#endif /* ATLEXPR_H_ */