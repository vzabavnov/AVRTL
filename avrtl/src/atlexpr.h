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
template<typename T = uint8_t, int bit>
constexpr T CreateBitMask() {
	return  bit < 0 ? 0 : ((T)1) << bit;
}

/// <summary>
/// create mask for specified bits
/// </summary>
template<typename T = uint8_t, int bit1, int bit2, int... pins>
constexpr T CreateBitMask() {
	return CreateBitMask<T, bit1>() | CreateBitMask<T, bit2, pins...>();
}

template<typename T = uint8_t>
constexpr T CreateMask(int length, int offset = 0) {
	return length <= 0 	? T(0) : CreateMask<T>(length - 1, offset);
}

template<typename T>
constexpr inline T ValueFromPins(T const value) {
	return  T(0);
}

/// <summary>
/// convert value from specified pins to a number
/// </summary>
template<typename T, int pin, int... pins>
constexpr inline T ValueFromPins(T const value) {
	const T masked = value & CreateBitMask<T, pin>();
	return ((pin > sizeof...(pins))
	? masked >> (pin - sizeof...(pins))
	: masked << (sizeof...(pins) - pin))
	| ValueFromPins<T, pins...>(value);
}

template<typename T>
constexpr inline T ValueToPins(T const value) {
	return  T(0);
}

/// <summary>
/// convert specified value to specified pins
/// </summary>
template<typename T, int pin, int... pins>
constexpr inline T ValueToPins(T const value) {
	const T masked = value & CreateBitMask<T, sizeof...(pins)>();
	return ((pin > sizeof...(pins))
	? masked << (pin - sizeof...(pins))
	: masked >> (sizeof...(pins) - pin)
	) | ValueToPins<T, pins...>(value);
}

}
}

#endif /* ATLEXPR_H_ */