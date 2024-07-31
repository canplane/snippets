/* LCD [테스트 완료]
 *
 * pin :
 *   out - PC[7:0], PG[2:0]
 * interrupt :
 *   nothing.
 *
 * 16 characters per a line -> row[0:1], col[0:15]
 * 
 */

#ifndef                 __LCD_H__
#define                 __LCD_H__

#include                "pub.h"


#define                 _LCD_RS                 0x01
#define                 _LCD_RW                 0x02
#define                 _LCD_E                  0x04

#define                 LCD_clear()            ( LCD_cmd(0x01) )

static void
_LCD_pulse(void)
{
    on(PORTG, _LCD_E);
    udelay(100);
    off(PORTG, _LCD_E);
}

void
LCD_cmd(unsigned char cmd)
{
    off(PORTG, _LCD_RS | _LCD_RW);
    
    PORTC = cmd;
    _LCD_pulse();
}

void
LCD_init(void)
{
    // init port : PG3/1/0, PC[7:0]
    on(DDRG, _LCD_E | _LCD_RW | _LCD_RS);
    on(DDRC, 0xff);

    mdelay(40);
    
    PORTC = 0x38;   // function set
    _LCD_pulse();
    udelay(40);

    PORTC = 0x0C;   // display ON/OFF control
    udelay(40);
    _LCD_pulse();

    PORTC = 0x01;   // clear display
    mdelay(2);
    _LCD_pulse();

    PORTC = 0x06;   // entry mode set
    _LCD_pulse();

	// clear
	LCD_clear();
	mdelay(50);
}

static void
_LCD_writec(unsigned char c)
{
    on(PORTG, _LCD_RS), off(PORTG, _LCD_RW);

    PORTC = c;
    _LCD_pulse();
}

static void
_LCD_seek(char row, char col)
{
    off(PORTG, _LCD_RS | _LCD_RW);

    if (row == 0)
        PORTC = col + 0x80;
    else if (row == 1)
        PORTC = col + 0xC0;
    _LCD_pulse();
}

void
LCD_puts(char row, char col, char *s)
{
    int i;
    _LCD_seek(row, col);
    for (i = 0; s[i] && (col + i < 16); i++)
        _LCD_writec(s[i]);
    /*_LCD_seek(row, col);
    while (*s)
        _LCD_writec(*s++);*/
}

void
LCD_cll_puts(char row, char col, char *s)   // clear line and put string
{
    LCD_puts(row, 0, "                ");
    LCD_puts(row, col, s);
}
#define                 LCD_clear_line(row)    ( LCD_puts((row), 0, "                ") )

void
LCD_cls_puts(char row, char col, char *s)   // clear all screen and put string
{
    LCD_clear();
    LCD_puts(row, col, s);
}

void
LCD_putc(char row, char col, char c)
{
    _LCD_seek(row, col);
    _LCD_writec(c);
}


#endif
