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

int main(void)
{
    const atl::Pin redLED = atl::Pin(atl::std::PortB, 3);
    const atl::Pin GreenLed = atl::Pin(atl::std::PortB, 4);

	redLED.Direction = atl::Output;
	GreenLed.Direction = atl::Output;

	redLED.Set();
	GreenLed.Clear();
    while (1) 
    {
		_delay_ms(1000);
		redLED.Flip();
		GreenLed.Flip();
    }
}

