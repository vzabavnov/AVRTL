/*
 * BlinkLED3.cpp
 *
 * Created: 4/14/2017 11:39:03 PM
 * Author : Vadim Zabavnov
 * this is example how to use PinPort
 */ 
 
 #ifndef F_CPU
 #define F_CPU 800000UL
 #endif

#include <avr/io.h>
#include <util/delay.h>

#include <atlstd.h>


int main(void)
{
	// using digital port with pin ports
	const atl::DigitalPort<atl::PinPort<atl::std::PhysPORTB, 0, 2, 4>, atl::PinPort<atl::std::PhysDDRB, 0, 2, 4>> pinPort;

	// set as output. this call will set out only pins 2, 3 and 4. pins 0 and 1 still input pins 
	pinPort.Direction.Write(0xff);
	
	for (int i = 0; i < 5; i++) 
    {
		// set LED2 on, all other off
		pinPort = 0b0011;  
		_delay_ms(1000);
		pinPort = 0b0101;
		_delay_ms(1000);
		pinPort = 0b0110;
		_delay_ms(1000);
    }

	// using pin port with digital port
	const atl::PinPort<atl::std::DigitalPortB, 0, 2, 4> pinPort2;

	// write direction as input directly to data port using expression
	pinPort2.DataPort.Direction.Write(atl::expr::CreateBitMask<atl::std::DigitalPortB::DataType, 0, 2, 4>());
	for (int i = 0; i < 5; i++)
	{
		// set LED2 on, all other off
		pinPort2 = 0b0011;
		_delay_ms(1000);
		pinPort2 = 0b0101;
		_delay_ms(1000);
		pinPort2 = 0b0110;
		_delay_ms(1000);
	}

}

