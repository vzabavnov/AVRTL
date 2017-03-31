/*
 * atlport.h
 *
 * Created: 3/20/2017 9:13:08 PM
 *  Author: Vadim Zabavnov
 */ 


#ifndef ATLPORT_H_
#define ATLPORT_H_

#include <avr/io.h>

#include <atlexpr.h>
	
namespace atl {

/// <summary>
/// The direction mode
/// </summary>
enum DirectionMode {
	/// <summary>
	/// input or tri stated
	/// </summary>
	Input,
	/// <summary>
	/// Output
	/// </summary>
	Output,
	/// <summary>
	/// input with pull-up register enabled
	/// </summary>
	PullUp
};

class PortDirection {
	const int _portAddr;
	const int _ddrAddr;
public:
	constexpr PortDirection(const int portAddr, const int ddrAddr) : _portAddr(portAddr), _ddrAddr(ddrAddr) { }
	constexpr PortDirection(const PortDirection & dd) : _portAddr(dd._portAddr), _ddrAddr(dd._ddrAddr) { }

	operator uint8_t() const {
		return _SFR_IO8(_ddrAddr);
	}

	void inline operator = (const uint8_t value) const {
		_SFR_IO8(_ddrAddr) = value;
	}

	void inline operator = (const DirectionMode mode) const {
		switch(mode) {
			case Input:
			AsInput();
			break;
			case PullUp:
			AsPullUp();
			break;
			default:
			AsOutput();
		}
	}
	
	void inline AsInput() const {
		_SFR_IO8(_ddrAddr) = 0;
		_SFR_IO8(_portAddr) = 0;
	}

	void inline AsPullUp() const {
		_SFR_IO8(_ddrAddr) = 0;
		_SFR_IO8(_portAddr) = 0xff;
	}
	
	void inline AsOutput() const {
		_SFR_IO8(_ddrAddr) = 0xff;
	}
};

class Port {
	const int _portAddr;
	const int _pinAddr;
public:
	const PortDirection Direction;
	const int Length;
	const uint8_t Mask;
	
	constexpr Port(const int portAddr, const int ddrAddr, const int pinAddr, const int length = sizeof(uint8_t)) : _portAddr(portAddr), _pinAddr(pinAddr),
		Direction(portAddr, ddrAddr), 
		Length(length), 
		Mask(expr::CreateMask(length)) 
		{ }

	constexpr Port(const Port & port) : _portAddr(port._portAddr), _pinAddr(port._pinAddr),
		Direction(port.Direction), 
		Length(port.Length), Mask(port.Mask) { }

	void inline Set(const uint8_t value) const
	{
		_SFR_IO8(_portAddr) = value;
	}

	void inline Clear() const{
		Set(0);
	}

	uint8_t inline Get() const{
		return _SFR_IO8(_pinAddr);
	}

	void inline Flip() const {
		_SFR_IO8(_pinAddr) ^= 0xff & Mask;
	}

	void operator = (const uint8_t value) const
	{
		Set(value);
	}

	operator uint8_t() const{
		return Get();
	}
};

}


#endif /* ATLPORT_H_ */