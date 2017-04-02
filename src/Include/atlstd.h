/*
 * atlstd.h
 *
 * Created: 3/31/2017 12:29:59 AM
 *  Author: Vadim Zabavnov
 */ 

#ifndef ATLSTD_H_
#define ATLSTD_H_

#include "atlport.h"

namespace atl {
namespace std {

using namespace atl;

// standard ports

#ifdef PORTA
constexpr Port PortA = Port(_SFR_IO_ADDR(PORTA), _SFR_IO_ADDR(DDRA), _SFR_IO_ADDR(PINA));
#endif

#ifdef PORTB
constexpr Port PortB = Port(_SFR_IO_ADDR(PORTB), _SFR_IO_ADDR(DDRB), _SFR_IO_ADDR(PINB));
#endif

#ifdef PORTC
constexpr Port PortC = Port(_SFR_IO_ADDR(PORTC), _SFR_IO_ADDR(DDRC), _SFR_IO_ADDR(PINC));
#endif

#ifdef PORTD
constexpr Port PortD = Port(_SFR_IO_ADDR(PORTD), _SFR_IO_ADDR(DDRD), _SFR_IO_ADDR(PIND));
#endif

}
}

#endif /* ATLSTD_H_ */