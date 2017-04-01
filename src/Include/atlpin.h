/*
 * atlpin.h
 *
 * Created: 3/23/2017 3:31:54 PM
 *  Author: Vadim Zabavnov
 */ 


#ifndef ATLPIN_H_
#define ATLPIN_H_

#include "atlport.h"
#include "atlexpr.h"

namespace atl
{

class PinDirection {
	const int _pin;
	const atl::Port _port;
public:
	const uint8_t Mask;
	
	constexpr PinDirection(const atl::Port& port, const int pin) : _pin(pin), _port(port), Mask(expr::CreateBitMask(pin)) { }

	void operator = (const DirectionMode mode) const {
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
		_port.Direction = _port.Direction & ~Mask;
		_port = _port & ~Mask;
	}

	void inline AsPullUp() const {
		_port.Direction = _port.Direction & ~Mask;
		_port = _port | Mask;
	}

	void inline AsOutput() const {
		_port.Direction = _port.Direction | Mask;
	}
};

class Pin {
	const int _pin;
	const atl::Port _port;
public:
	const uint8_t Mask;
	const PinDirection Direction;

	constexpr Pin(const atl::Port& port, const int pin) : _pin(pin), _port(port), Mask(expr::CreateBitMask(pin)), Direction(port, pin) { }
	constexpr Pin(const Pin & pin) : _pin(pin._pin), _port(pin._port), Mask(pin.Mask), Direction(pin._port, pin._pin) { }

	void inline Set() const {
		_port = _port | Mask;
	}

	void inline Set(const bool value) const {
		if ( value )
			Set();
		else
			Clear();
	}

	bool inline Get() const {
		return (_port & Mask) != 0;
	}

	void inline Clear() const {
		_port = _port & ~Mask;
	}

	void inline Flip() const {
		_port = _port ^ Mask;
	}
};

}

#endif /* ATLPIN_H_ */