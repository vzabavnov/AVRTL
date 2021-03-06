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
	constexpr static T Mask = expr::CreateMask<T>(Length);

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
template<typename TRead, typename TWrite = TRead>
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

template <typename TDigitalPort, typename TDirectionPort>
struct DigitalPort {
	typedef TDigitalPort DataPortType;
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

/// <summary>
///	The port to read and write a digital number of type specified by TDigitalPort::DataType
/// </summary>
/// <typeref name="TReadWritePort">
/// The port to read and write data to and from. the port must support methods DataType Read() and void Write(DataType value), as well as tghe port must define type DataType.
/// </typeref>
/// <typeref name="length">
/// Specified how many bits is used for the number
/// </typeref>
/// <typeref name="offset">
/// Specified the offset.
/// </typeref>
template <typename TReadWritePort, int length, int offset = 0>
struct NumericPort {
	typedef TReadWritePort ReadWritePortType;
	typedef typename ReadWritePortType::DataType DataType;

	const int Offset = offset;
	const int Length = length;

	const DataType Mask = atl::expr::CreateMask<DataType>(length, offset);

	const ReadWritePortType DataPort = ReadWritePortType();
	
	constexpr inline DataType CreateValueToWrite(const DataType value) const {
		return (value << Offset) & Mask;
	}

	constexpr inline DataType CreateValieFromRead(const DataType value) const {
		return (value & Mask) >> Offset;
	}

	inline void Write(const DataType value) const {
		DataPort.Write(CreateValueToWrite(value));
	}

	inline DataType Read() const {
		return CreateValieFromRead(DataPort.Read());
	}

	void operator = (const DataType value) const {
		Write(value);
	}

	operator DataType() const {
		return Read();
	}
};


template <int... pins>
struct PinPort;

template <int pin>
struct PinPort {
	
};

}

#endif /* ATLPORT_H_ */