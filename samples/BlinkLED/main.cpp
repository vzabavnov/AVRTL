/*
 * BlinkLED.cpp
 *
 * Created: 3/27/2017 2:41:39 PM
 * Author : Vadim Zabavnov
 */ 

 #ifndef F_CPU
 #define F_CPU 800000UL
 #endif

#include <avr/io.h>
#include <util/delay.h>

#include <atlexpr.h>
#include <atlstd.h>

int main(void)
{
	const atl::std::DigitalPortB thePort;
	const int pinMask = atl::expr::CreateBitMask(3);
    thePort.Direction = atl::Output;

    while (1) 
    {
		thePort.Write(pinMask);
		_delay_ms(1000);
		thePort.Clear();
		_delay_ms(1000);
    }
}

