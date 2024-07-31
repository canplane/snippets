/* Board 3 - Ultrasonic
 *
 * pin :
 *   +5V, GND.
 *   in/out - PE4(INT4)
 * interrupt :
 *   T/C0_OC, INT4
 *
 * USONIC_dist
 *
 */

#ifndef                 __USONIC_H__
#define                 __USONIC_H__

#include                "pub.h"

volatile int            USONIC_temp = 25;

volatile int            USONIC_dist = 1000;
static volatile unsigned int        _USONIC_tick;

volatile unsigned char  _USONIC_occupied;

// T/C 0의 compare match, INT4 사용
void
USONIC_init(void)
{
    USONIC_dist = 0;

    // init INT4(PE4)
    on(EIMSK, _BV(INT4));       // INT4 Interrupt Set
    on(EICRB, 0x03);            // 상승 에지에서 인터럽트

    // init T/C0_OC
    on(TCCR0A, _BV(WGM01));     // CTC Mode
    on(TCCR0A, _BV(CS01));      // clk/8 Prescaler
    TCNT0 = 0;
    OCR0A = 19;                 // 1cycle -> 10us으로 세팅 : 1 cycle = (OCR0A + 1)/(16 Mhz/N)
    TIMSK0 = _BV(OCIE0A);       // T/C0 Output Compare Match INT
    //TIFR0 =
    sei();

    // TCNT : 현재까지 센 펄수 수, OCR : 인터럽트 발생 지점,
    // TIFR : 인터럽트 조건을 만족하면 자동으로 해당 비트 세트되고, TIMSK 역시 세트된 상태면 실제 인터럽트 발생. 그런데 임의로 세트해서 발생시킬 수도 있는 듯.(R/W)

    _USONIC_occupied = FALSE;
}

ISR(TIMER0_COMP_vect) { _USONIC_tick++; }
ISR(INT4_vect)
{
	unsigned int tmp;
    tmp = _USONIC_tick;

    if (EICRB & 0x03) {
        off(EICRB, 0x03);                           // low state
        _USONIC_tick = 0;
    } else {
        on(EICRB, _BV(ISC41) | _BV(ISC40));         // INT4 Rising Edge / INT Set
        //_USONIC_pulse_end = tmp;
        
        // distance = velocity * time. 10 us마다 갱신. 단위 mm
        USONIC_dist = (331.5 + (0.6 * USONIC_temp)) * (tmp * 0.00001 / 2) * 1000;
        _USONIC_occupied = FALSE;
    }
}

void
USONIC_trigger(void)
{
    if (_USONIC_occupied)
        return;
    _USONIC_occupied = TRUE;

    cli();              // clear interrupt
    off(PORTE, 0x10);   // PE4 clear
    on(DDRE, 0x10);     // PE4 pin is output    
    udelay(500);

    on(PORTE, 0x10);    // output set during 5 us
    udelay(5);

    off(PORTE, 0x10);   // PE4 clear
    udelay(100);

    off(DDRE, 0x10);    // PE4 pin is input
    udelay(100);

    sei();				// set interrupt

    mdelay(100);
}


#endif
