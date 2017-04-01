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
/// Generate a mask with specified length
/// </summary
constexpr uint8_t CreateMask(const int length) {
	return length <= 0 ? 0 : (1 << (length - 1)) | CreateMask(length - 1);
}

constexpr uint8_t CreateBitMask(const int bit) {
	return 1 << bit;
}

}
}

#endif /* ATLEXPR_H_ */