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

template<typename T, int ADDR, int OFFSET, int length = sizeof(T)> class PhysPort
{
public:
	typedef T DataType;

	constexpr static int Offset = OFFSET;
	constexpr static int Length = length;
	constexpr static int Address = ADDR;
	constexpr static T Mask = expr::CreateMask(Length);

	inline void Write(const T value) const {
		(*(volatile T *)(Address + Offset)) = value;
	}

	inline T Read() const {
		return (*(volatile T *)(Address + Offset));
	}

	inline operator T () const {
		return Read();
	}

	inline void operator = (const T value) const {
		Write(value);
	}

	inline void Clear() const {
		Write((T)0);
	}

	inline void Set() const {
		Write(Mask);
	}
};

/// <summary>
///	specified the data port.
/// </summary>
/// <typeparam name="TRead">
///	The type of reading port. The port must specify type DataType and must support method DataType Read();
/// </typeparam>
/// <typeparam name="TWrite">
///	The type of writing port. The port must specify type DataType and must support method void Write(const DataType value);
/// </typeparam>
template<typename TRead, typename TWrite>
struct ReadWritePort {
	typedef TRead ReadPortType;
	typedef TWrite WriteportType;
	typedef typename TRead::DataType DataType;
	
	const ReadPortType ReadPort = ReadPortType();
	const WriteportType WritePort = WriteportType();

	inline void Write(const DataType value) const
	{
		WritePort.Write(value);
	}

	inline DataType Read() const {
		return ReadPort.Read();
	}

	inline operator DataType() const {
		return Read();
	}

	inline void operator = (const DataType value) const {
		Write(value);
	}
};

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

/// <summary>
/// specifies the data direction port
/// </summary>
/// <typeparam name="TData">
/// The data port.
/// </typeparam>
/// <typeparam name="TDir">
/// The data direction port
/// </typeparam>
template <typename TData, typename TDir>
struct DataDirectionPort {
	typedef TData DataPortType;
	typedef TDir DirectionPortType;
	typedef typename DirectionPortType::DataType DirectionPortDataType;

	const DataPortType DataPort = DataPortType();
	const DirectionPortType DirectionPort = DirectionPortType();

	inline void Write(const DirectionPortDataType value) const {
		DirectionPort.Write(value);
	}

	inline DirectionPortDataType Read() const {
		return DirectionPort.Read();
	}

	inline operator DirectionPortDataType() const {
		return Read();
	}

	inline void operator = (const DirectionPortDataType value) const {
		Write(value);
	}

	void inline AsInput() const {
		DirectionPort.Write(0);
		DataPort.Write(0);
	}

	void inline AsPullUp() const {
		DirectionPort.Write(0);
		DataPort.Write(DataPort.Mask);
	}
	
	void inline AsOutput() const {
		DirectionPort.Write(DirectionPort.Mask);
	}

	inline void operator = (const DirectionMode mode) const {
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
};

template <typename TDataPort, typename TDirectionPort>
struct DigitalPort {
	typedef TDataPort DataPortType;
	typedef TDirectionPort DataDirectionPortType;
	typedef typename DataPortType::DataType DataType;

	const DataDirectionPortType Direction = DataDirectionPortType();
private:
	const DataPortType _port = DataPortType();
public:
	inline void Write(const DataType value) const
	{
		_port.Write(value);
	}

	inline DataType Read() const {
		return _port.Read();
	}

	inline void Clear() const {
		_port.Write((DataType)0);
	}

	inline void Flip() const {
		_port.Write(_port.Read() ^ _port.Mask);
	}

	void operator = (const DataType value) const
	{
		Write(value);
	}

	operator DataType() const{
		return Read();
	}
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