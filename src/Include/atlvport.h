/*
 * atlvport.h
 *
 * Created: 3/24/2017 1:15:28 PM
 *  Author: vad
 */ 


#ifndef ATL_VPORT_H_
#define ATL_VPORT_H_

#include <atlpin.h>

namespace atl{

template<int T1, int T0>
static inline uint8_t ToPortValue(uint8_t value)
{
	return
		((value & 0x02) << (T1 - 1)) |
		((value & 0x01) << (T0 - 0));
}

template<int T2, int T1, int T0>
static inline uint8_t ToPortValue(const uint8_t value)
{
	return
		((value & 0x04) << (T2 - 2)) |
		((value & 0x02) << (T1 - 1)) |
		((value & 0x01) << (T0 - 0));
}

template<int T3, int T2, int T1, int T0>
static inline uint8_t ToPortValue(const uint8_t value)
{
	return
		((value & 0x08) << (T3 - 3)) |
		((value & 0x04) << (T2 - 2)) |
		((value & 0x02) << (T1 - 1)) |
		((value & 0x01) << (T0 - 0));
}

template<int T4, int T3, int T2, int T1, int T0>
static inline uint8_t ToPortValue(const uint8_t value)
{
	return
		((value & 0x10) << (T4 - 4)) |
		((value & 0x08) << (T3 - 3)) |
		((value & 0x04) << (T2 - 2)) |
		((value & 0x02) << (T1 - 1)) |
		((value & 0x01) << (T0 - 0));
}

template<int T5, int T4, int T3, int T2, int T1, int T0>
static inline uint8_t ToPortValue(const uint8_t value)
{
	return
		((value & 0x20) << (T5 - 5)) |
		((value & 0x10) << (T4 - 4)) |
		((value & 0x08) << (T3 - 3)) |
		((value & 0x03) << (T2 - 2)) |
		((value & 0x02) << (T1 - 1)) |
		((value & 0x01) << (T0 - 0));
}

template<int T6, int T5, int T4, int T3, int T2, int T1, int T0>
static inline uint8_t ToPortValue(const uint8_t value)
{
	return
		((value & 0x40) << (T6 - 6)) |
		((value & 0x20) << (T5 - 5)) |
		((value & 0x10) << (T4 - 4)) |
		((value & 0x08) << (T3 - 3)) |
		((value & 0x04) << (T2 - 2)) |
		((value & 0x02) << (T1 - 1)) |
		((value & 0x01) << (T0 - 0));
}

template<int T7, int T6, int T5, int T4, int T3, int T2, int T1, int T0>
static inline uint8_t ToPortValue(const uint8_t value)
{
	return
		((value & 0x80) << (T7 - 7)) |
		((value & 0x40) << (T6 - 6)) |
		((value & 0x20) << (T5 - 5)) |
		((value & 0x10) << (T4 - 4)) |
		((value & 0x08) << (T3 - 3)) |
		((value & 0x04) << (T2 - 2)) |
		((value & 0x02) << (T1 - 1)) |
		((value & 0x01) << (T0 - 0));
}

template<int T1, int T0>
static inline uint8_t FromPortValue(const uint8_t value)
{
	return
		((value & (1 << T1)) >> (T1 - 1)) |
		((value & (1 << T0)) >> (T0 - 0));
}

template<int T2, int T1, int T0>
static inline uint8_t FromPortValue(const uint8_t value)
{
	return
		((value & (1 << T2)) >> (T2 - 2)) |
		((value & (1 << T1)) >> (T1 - 1)) |
		((value & (1 << T0)) >> (T0 - 0));
}

template<typename TPORT, int T1, int T0>
class VPort{
public:
	static const uint8_t Pin1Mask = (1 << T1);
	static const uint8_t Pin0Mask = (1 << T0);
	static const uint8_t Mask = Pin1Mask | Pin0Mask;
	static const uint8_t MaxValue = 0x3;

	static uint8_t Get()
	{
		return FromPortValue<T1, T0>(TPORT::Get());
	}

	static void Set(const uint8_t value)
	{
		TPORT::Set(ToPortValue<T1, T0>(value));
	}
};


}

#endif /* ATL_VPORT_H_ */