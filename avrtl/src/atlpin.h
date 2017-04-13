/*
 * atlpin.h
 *
 * Created: 3/23/2017 3:31:54 PM
 *  Author: Vadim Zabavnov
 */ 


#ifndef ATLPIN_H_
#define ATLPIN_H_

#include <atlport.h>
#include <atlexpr.h>

namespace atl
{
template <typename TDigitalPort, int pin>
struct DigitalPinDirection {
	typedef TDigitalPort DigitalPortType;
	typedef typename DigitalPortType::DataType DataType;
	typedef typename DigitalPortType::DataDirectionPortType DataDirectionPortType;
	typedef typename DigitalPortType::DataPortType DataPortType;

	const DataType Mask = DataType(1) << pin;
private:
	const DataDirectionPortType _direction = DataDirectionPortType();
	const DataPortType _port = DataPortType();
public:
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
		_direction = _direction & ~Mask;
		_port = _port & ~Mask;
	}

	void inline AsPullUp() const {
		_direction = _direction & ~Mask;
		_port = _port | Mask;
	}

	void inline AsOutput() const {
		_direction = _direction | Mask;
	}
};

template <typename TPort, int pin>
struct DigitalPin {
	typedef TPort DigitalPortType;
	typedef typename DigitalPortType::DataType DataType;
	typedef typename DigitalPortType::DataDirectionPortType DataDirectionPortType;
private:
	const DigitalPortType _port = DigitalPortType();
public:
	const DataType Mask = DataType(1) << pin;

	const DataDirectionPortType Direction = DataDirectionPortType();

	void inline Set() const {
		_port = _port | Mask;
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