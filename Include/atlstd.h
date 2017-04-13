/*
 * atlstd.h
 *
 * Created: 3/31/2017 12:29:59 AM
 *  Author: Vadim Zabavnov
 */ 

#ifndef ATLSTD_H_
#define ATLSTD_H_

#include <atlport.h>

namespace atl {
namespace std {

using namespace atl;


//map AVR physical ports

#ifdef PORTA

#ifdef PA7
constexpr int PORTA_LENGTH = 8;
#elif PA6
constexpr int PORTA_LENGTH = 7;
#elif PA5
constexpr int PORTA_LENGTH = 6;
#elif PA4
constexpr int PORTA_LENGTH = 5;
#elif PA3
constexpr int PORTA_LENGTH = 4;
#elif PA2
constexpr int PORTA_LENGTH = 3;
#elif PA1
constexpr int PORTA_LENGTH = 2;
#elif PA0
constexpr int PORTA_LENGTH = 1;
#endif

typedef PhysPort<uint8_t, _SFR_IO_ADDR(PORTA), __SFR_OFFSET, PORTA_LENGTH> PhysPORTA;
typedef PhysPort<uint8_t, _SFR_IO_ADDR(DDRA), __SFR_OFFSET, PORTA_LENGTH> PhysDDRA;
typedef PhysPort<uint8_t, _SFR_IO_ADDR(PINA), __SFR_OFFSET, PORTA_LENGTH> PhysPINA;
typedef ReadWritePort<PhysPINA, PhysPORTA> DataPortA;
typedef DataDirectionPort<PhysPORTA, PhysDDRA> DataDirectionPortA;
typedef DigitalPort<DataPortA, DataDirectionPortA> DigitalPortA;

#endif // PORTA

#ifdef PORTB

#ifdef PB7
constexpr int PORTB_LENGTH = 8;
#elif PB6
constexpr int PORTB_LENGTH = 7;
#elif PB5
constexpr int PORTB_LENGTH = 6;
#elif PB4
constexpr int PORTB_LENGTH = 5;
#elif PB3
constexpr int PORTB_LENGTH = 4;
#elif PB2
constexpr int PORTB_LENGTH = 3;
#elif PB1
constexpr int PORTB_LENGTH = 2;
#elif PB0
constexpr int PORTB_LENGTH = 1;
#endif

typedef PhysPort<uint8_t, _SFR_IO_ADDR(PORTB), __SFR_OFFSET, PORTB_LENGTH> PhysPORTB;
typedef PhysPort<uint8_t, _SFR_IO_ADDR(DDRB), __SFR_OFFSET, PORTB_LENGTH> PhysDDRB;
typedef PhysPort<uint8_t, _SFR_IO_ADDR(PINB), __SFR_OFFSET, PORTB_LENGTH> PhysPINB;
typedef ReadWritePort<PhysPINB, PhysPORTB> DataPortB;
typedef DataDirectionPort<PhysPORTB, PhysDDRB> DataDirectionPortB;
typedef DigitalPort<DataPortB, DataDirectionPortB> DigitalPortB;

#endif // PORTB

#ifdef PORTC

#ifdef PC7
constexpr int PORTC_LENGTH = 8;
#elif PC6
constexpr int PORTC_LENGTH = 7;
#elif PC5
constexpr int PORTC_LENGTH = 6;
#elif PC4
constexpr int PORTC_LENGTH = 5;
#elif PC3
constexpr int PORTC_LENGTH = 4;
#elif PC2
constexpr int PORTC_LENGTH = 3;
#elif PC1
constexpr int PORTC_LENGTH = 2;
#elif PC0
constexpr int PORTC_LENGTH = 1;
#endif

typedef PhysPort<uint8_t, _SFR_IO_ADDR(PORTC), __SFR_OFFSET, PORTC_LENGTH> PhysPORTC;
typedef PhysPort<uint8_t, _SFR_IO_ADDR(DDRC), __SFR_OFFSET, PORTC_LENGTH> PhysDDRC;
typedef PhysPort<uint8_t, _SFR_IO_ADDR(PINC), __SFR_OFFSET, PORTC_LENGTH> PhysPINC;
typedef ReadWritePort<PhysPINC, PhysPORTC> DataPortC;
typedef DataDirectionPort<PhysPORTC, PhysDDRC> DataDirectionPortC;
typedef DigitalPort<DataPortC, DataDirectionPortC> DigitalPortC;

#endif // PORTC

#ifdef PORTD

#ifdef PD7
constexpr int PORTD_LENGTH = 8;
#elif PD6
constexpr int PORTD_LENGTH = 7;
#elif PD5
constexpr int PORTD_LENGTH = 6;
#elif PD4
constexpr int PORTD_LENGTH = 5;
#elif PD3
constexpr int PORTD_LENGTH = 4;
#elif PD2
constexpr int PORTD_LENGTH = 3;
#elif PD1
constexpr int PORTD_LENGTH = 2;
#elif PD0
constexpr int PORTD_LENGTH = 1;
#endif

typedef PhysPort<uint8_t, _SFR_IO_ADDR(PORTD), __SFR_OFFSET, PORTD_LENGTH> PhysPORTD;
typedef PhysPort<uint8_t, _SFR_IO_ADDR(DDRD), __SFR_OFFSET, PORTD_LENGTH> PhysDDRD;
typedef PhysPort<uint8_t, _SFR_IO_ADDR(PIND), __SFR_OFFSET, PORTD_LENGTH> PhysPIND;
typedef ReadWritePort<PhysPIND, PhysPORTD> DataPortD;
typedef DataDirectionPort<PhysPORTD, PhysDDRD> DataDirectionPortD;
typedef DigitalPort<DataPortD, DataDirectionPortD> DigitalPortD;

#endif // PORTD


}
}

#endif /* ATLSTD_H_ */