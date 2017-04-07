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
const atl::DigitalPin<atl::std::DigitalPortB, 3> GreenLed;
const atl::DigitalPin<atl::std::DigitalPortB, 4> YellowLED;

int main(void)
{
	redLED.Direction = atl::Output;
	GreenLed.Direction = atl::Output;
	YellowLED.Direction = atl::Output;

	redLED.Clear();
	GreenLed.Set();
	YellowLED.Set();

    while (1) 
    {
		_delay_ms(1000);
		redLED.Flip();
		GreenLed.Flip();
		_delay_ms(1000);
		GreenLed.Flip();
		YellowLED.Flip();
		_delay_ms(1000);
		YellowLED.Flip();
		redLED.Flip();
	}
}

