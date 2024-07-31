/* Used publicly [테스트 완료]
 *
 *
 */

#ifndef                 __PUB_H__
#define                 __PUB_H__

#include                <avr/io.h>
#include                <avr/interrupt.h>
#include                <util/atomic.h>
#include				<stdio.h>
#include                <string.h>


#define                 TRUE                    1
#define                 FALSE                   0

#define                 F_CPU                   16000000L

#define                 off(reg, bits)          ( (reg) &= ~(bits) )
#define                 on(reg, bits)           ( (reg) |= (bits) )
#define                 mask(reg, bits)         ( (reg) & (bits) )

char                    strbuf[128];

char                    *msg = NULL;

char *
itoa(int i, char *s)
{
    sprintf(s, "%d", i);
    return s;
}


/* score, gauge */

#define                 to_score(adc_data, max)     ( (adc_data) * (max) / 1023 )

char                    *gauges[10] = {
    "000000000",
	"00000000 ",
	"0000000  ",
	"000000   ",
	"00000    ",
	"0000     ",
	"000      ",
	"00       ",
    "0        ",
    "         "
};


/* delay */

void
udelay(unsigned int usecs)
{
    unsigned int i;
    for (i = 0; i < usecs; i++) {   // 4 cycle
        asm("PUSH R0");             // + 2 cycle
        asm("POP R0");              // + 2 cycle
        asm("PUSH R0");             // + 2 cycle
        asm("POP R0");              // + 2 cycle = 12 cycle : 1 us for 11.0592 MHz 
        asm("PUSH R0");             // + 2 cycle
        asm("POP R0");              // + 2 cycle = 16 cycle : 1 us for 16 MHz
    }
}

void
mdelay(unsigned int msecs)
{
    unsigned int i;
    for (i = 0; i < msecs; i++)
        udelay(1000);
}


#endif
