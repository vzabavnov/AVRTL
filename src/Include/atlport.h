/*
 * atlport.h
 *
 * Created: 3/20/2017 9:13:08 PM
 *  Author: Vadim Zabavnov
 */ 


#ifndef ATLPORT_H_
#define ATLPORT_H_

#include <avr/io.h>

#ifndef  __cpp_constexpr
#error At least C++11 is requered
#endif
	
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


class Port {
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

	const int _portAddr;
	const int _pinAddr;

	constexpr uint8_t CreateMask(const int length) const {
		return length <= 0 ? 0 : (1 << (length - 1)) | CreateMask(length - 1);
	}
public:
	const PortDirection Direction;
	const int Length;
	const uint8_t Mask;
	
	constexpr Port(const int portAddr, const int ddrAddr, const int pinAddr, const int length = sizeof(uint8_t)) : _portAddr(portAddr), _pinAddr(pinAddr),
		Direction(portAddr, ddrAddr), 
		Length(length), 
		Mask(CreateMask(length)) 
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

namespace std {

/*********************
	define existing ports
**********************/

#ifdef PORTA
const Port PortA = Port(_SFR_IO_ADDR(PORTA), _SFR_IO_ADDR(DDRA), _SFR_IO_ADDR(PINA));
#endif

#ifdef PORTB
const Port PortB = Port(_SFR_IO_ADDR(PORTB), _SFR_IO_ADDR(DDRB), _SFR_IO_ADDR(PINB));

#ifdef PORTC
const Port PortC = Port(_SFR_IO_ADDR(PORTC), _SFR_IO_ADDR(DDRC), _SFR_IO_ADDR(PINC));
#endif

#ifdef PORTD
const Port PortD = Port(_SFR_IO_ADDR(PORTD), _SFR_IO_ADDR(DDRD), _SFR_IO_ADDR(PIND));
#endif

#endif
}

}


#endif /* ATLPORT_H_ */