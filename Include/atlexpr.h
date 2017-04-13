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
template<typename T = uint8_t>
constexpr T CreateBitMask(const int bit) {
	return ((T)1) << bit;
}

/// <summary>
/// Generate a mask with specified length
/// </summary
template<typename T = uint8_t>
constexpr T CreateMask(const int length) {
	return length <= 0 ? (T)0 : CreateBitMask<T>(length -1 ) | CreateMask<T>(length - 1);
}

/// <summary>
/// Generate a mask with specified length
/// </summary
template<typename T = uint8_t>
constexpr T CreateMask(const int length, const int offset) {
	return CreateMask(length) << offset;
}

}
}

#endif /* ATLEXPR_H_ */