/*
 * BlinkLED2.cpp
 *
 * Created: 3/28/2017 1:46:08 AM
 * Author : Vadim Zabavnov
 */ 

 #ifndef F_CPU
 #define F_CPU 800000UL
 #endif

#include <avr/io.h>
#include <util/delay.h>

#include <atlpin.h>
#include <atlstd.h>

const atl::DigitalPin<atl::std::DigitalPortB, 2> redLED;
const atl::DigitalPin<atl::std::DigitalPortB, 3> GreenLED;
const atl::DigitalPin<atl::std::DigitalPortB, 4> YellowLED;

int main(void)
{
	redLED.Direction = atl::Output;
	GreenLED.Direction = atl::Output;
	YellowLED.Direction = atl::Output;

	redLED.Clear();
	GreenLED.Set();
	YellowLED.Set();

    while (1) 
    {
		_delay_ms(1000);
		redLED.Flip();
		GreenLED.Flip();
		_delay_ms(1000);
		GreenLED.Flip();
		YellowLED.Flip();
		_delay_ms(1000);
		YellowLED.Flip();
		redLED.Flip();
	}
}

