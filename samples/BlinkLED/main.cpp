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

#include <atlport.h>


int main(void)
{
	const atl::Port thePort = atl::std::PortB;
	const int pinMask = (1 << 3);
    thePort.Direction = atl::Output;

    while (1) 
    {
		thePort.Set(pinMask);
		_delay_ms(1000);
		thePort.Clear();
		_delay_ms(1000);
    }
}

