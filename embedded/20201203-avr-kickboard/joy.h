/* Board 4 - Joystick
 *
 * pin :
 *   +5V, GND.
 *   in - PF1(x축), PF0(y축)
 * interrupt :
 *   ADC_vect
 * 
 * PF1: ADC1 조이스틱 x축, PF0: ADC0 조이스틱 y축
 *
 * ADMUX가 0x40이면 ADC0(PF0), 0x41이면 ADC1(PF1) 입력 변환
 *
 */

#ifndef                 __JOY_H__
#define                 __JOY_H__

#include                "adc.h"
#include                "urt1.h"
#include                "pub.h"


#define                 JOY_init()              ( ADC_init() )

#define                 _JOY_FLAG_Y             0
#define                 _JOY_FLAG_X             1

static unsigned char    _JOY_flag = _JOY_FLAG_Y;
unsigned int            JOY_y = 25, JOY_x = 25;     // [0..50]

int
JOY_get_and_alter()
{
    if (_JOY_flag == _JOY_FLAG_Y) {         // ADC0(y축)
        JOY_y = ADC_data * 50 / 1023;
        _JOY_flag = _JOY_FLAG_X;
        ADMUX = 0x41;
    } else if (_JOY_flag == _JOY_FLAG_X) {  // ADC1(x축)
        JOY_x = ADC_data * 50 / 1023;
        _JOY_flag = _JOY_FLAG_Y;
        ADMUX = 0x40;
    } else
        _JOY_flag = _JOY_FLAG_Y;
    
    return _JOY_flag;
}


#endif
