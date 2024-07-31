/* PD0/1 Switch, PB7 LED [테스트 완료]
 *
 * pin :
 *   in - PD1(INT1), PD0(INT0)
 *   out - PB7
 * interrupt :
 *   INT1, INT0
 *
 * # Switch
 * PD1 : SW 2, PD0 : SW 1
 * 각각 INT1, INT0 인터럽트와 관련(버튼 누르면 하강 에지 -> 발생)
 * 
 * # LED
 * PB7에 HIGH 가하면 on
 */

#ifndef                 __SW_LED_H__
#define                 __SW_LED_H__

#include                "pub.h"


/* Switch */

void
SW_enable_int(void)
{
    on(EIMSK, _BV(INT1) | _BV(INT0));       // INT0, INT1 인터럽트 활성화
    off(EICRA, 0x0F), on(EICRA, 0x0A);      // 하강 에지(누른 상태)에서 인터럽트
    sei();
}

void
SW_init(void)
{
    // init port : PD1 - SW 2, PD0 - SW 1
    off(DDRD, 0x03);                        
    on(PORTD, 0x03);                        // PD0, PD1 풀업 저항 사용
}

#define                 SW_1_pushed()         	( (PIND & 0x01) == 0 )
/* ISR(INT0_vect) {} */
#define                 SW_2_pushed()         	( (PIND & 0x02) == 0 )
/* ISR(INT1_vect) {} */


/* LED */

#define                 LED_off()             	( on(PORTB, 0x80) )
#define                 LED_on()               	( off(PORTB, 0x80) )
#define                 LED_toggle()            ( (PORTB & 0x80) ? off(PORTB, 0x80) : on(PORTB, 0x80) )

void
LED_init(void)
{
    // PB7 - LED
    on(DDRB, 0x80);
	LED_off();
}


#endif
