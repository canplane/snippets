/* USART 1
 *
 * pin :
 *   nothing.
 * interrupt :
 *   USART1_UDRE_vect, USART1_RX_vect
 *
 */

#ifndef                 __URT1_H__
#define                 __URT1_H__

#include                "pub.h"


//#define                 _URT1_RX            0x04
//#define                 _URT1_TX            0x08

void
URT1_init(void)
{
    // PD3/2
    //on(DDRD, _URT1_TX);
    //off(DDRD, _URT1_RX);                    // INT2, INT3 사용 불가능

    UCSR1A = 0x00;                          // serial states clear

    UCSR1B = (_BV(RXEN1) | _BV(TXEN1));     // 0x18: 송수신 활성화

    UCSR1B |= _BV(RXCIE1);                  // 수신 완료 인터럽트 허용
    //안 됨 - 인터럽트 말고는 다 먹통되는 듯 : UCSR1B |= _BV(UDRIE1);                  // 송신 데이터 레지스터 준비 완료 인터럽트 허용
    sei();
   
    // 비동기(UMSEL1 = 0), 패리티 없음(UPM1[1:0] = 00), 1비트 정지 비트(USBS1 = 0)
    UCSR1C = (_BV(UCSZ11) | _BV(UCSZ10));   // 0x06: 8비트 데이터
    
    UBRR1H = 0;
    UBRR1L = 103;                           // 16MHz 9600bps set
}

void
URT1_putc(unsigned char c)
{
    while (!(UCSR1A & _BV(UDRE1)));       // 송신 가능 대기
	UDR1 = c;                               // 데이터 전송
}
/* ISR(USART1_UDRE_vect) {} */
char
URT1_getc()
{
    while (!(UCSR1A & _BV(RXC1)));         // 데이터 수신 대기
	return UDR1;
}
/* ISR(USART1_RX_vect) {} */

void
URT1_puts(char *s)
{
    while (*s)
		URT1_putc(*s++);
}
#define					usart_transmit_string(s)       ( URT1_puts(s) )     // redirection


/* file type */

#define                 URT1_RX             0x04
static int
_URT1_std_putc(char c, FILE *stream)
{
    if (c == '\n')
		URT1_putc('\r');
    URT1_putc(c);
	return c;
}
static int
_URT1_std_getc(FILE *stream)
{
	return (int)URT1_getc();
}
static FILE        		_URT1_OUT          	= FDEV_SETUP_STREAM(_URT1_std_putc, NULL, _FDEV_SETUP_WRITE);
static FILE				_URT1_IN			= FDEV_SETUP_STREAM(NULL, _URT1_std_getc, _FDEV_SETUP_READ);
FILE                    *URT1_out           = &_URT1_OUT;
FILE                    *URT1_in            = &_URT1_IN;


/* UART1 to stdout/in */

//stdout = URT1_out, stdin = URT1_in;


#endif
