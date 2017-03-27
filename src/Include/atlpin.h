/*
 * atlpin.h
 *
 * Created: 3/23/2017 3:31:54 PM
 *  Author: Vadim Zabavnov
 */ 


#ifndef ATLPIN_H_
#define ATLPIN_H_

#include <atlport.h>

namespace atl
{

class Pin {
	class PinDirection {
		const int _pin;
		const atl::Port _port;
		const uint8_t _mask;
		public:
		constexpr PinDirection(const atl::Port& port, const int pin) : _pin(pin), _port(port), _mask(1 << _pin){}

		void operator = (const DirectionMode mode) const {
			switch(mode) {
				case Input:
				_port.Direction = _port.Direction & ~_mask;
				_port = _port & ~_mask;
				break;
				case PullUp:
				_port.Direction = _port.Direction & ~_mask;
				_port = _port | _mask;
				break;
				default:
				_port.Direction = _port.Direction | _mask;
			}
		}
	};

	const int _pin;
	const atl::Port _port;
	public:
	const uint8_t Mask;
	const PinDirection Direction;

	constexpr Pin(const atl::Port& port, const int pin) : _pin(pin), _port(port), Mask(1 << pin), Direction(port, pin) { }
	constexpr Pin(const Pin & pin) : _pin(pin._pin), _port(pin._port), Mask(pin.Mask), Direction(pin._port, pin._pin) { }

	void inline Set() const {
		_port = _port | Mask;
	}

	void inline Set(const bool value) {
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