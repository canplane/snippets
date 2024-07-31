/* Board 1 - Temperature(ADC0(PF0)), CDS(ADC1(PF1))
 *
 * pin :
 *   +5V, GND.
 *   in - PF0(ADC0)
 * interrupt :
 *   ADC_vect
 * 
 * ADMUX가 0x40이면 ADC0(PF0) 입력 변환
 *
 * cds와 temp 선 바꿔가면서 하는건가? 잘 모르겠다.
 */

#ifndef                 __CDS_TEMP_H__
#define                 __CDS_TEMP_H__

#include                "adc.h"
#include                "pub.h"


#define                 CDS_TEMP_init()         ( ADC_init() )

/*ISR(ADC_vect)
{
    ADC_data = ADC;
    ADCSRA = 0xc8;      //on(ADCSRA, _BV(ADSC));
}*/

#define                 _CDS_TEMP_FLAG_CDS      0
#define                 _CDS_TEMP_FLAG_TEMP     1

static unsigned char    _CDS_TEMP_flag = _CDS_TEMP_FLAG_TEMP;
unsigned int            CDS_TEMP_cds, CDS_TEMP_temp;    // cds: [1..10], temp: /10

unsigned int
CDS_to_score(unsigned int converted)                    // score: [1..10]  -> ex) gauges[CDS_to_score(CDS_TEMP_cds) - 1]
{
	if (converted > 1000)
        return 10;
	else if (converted > 950)
        return 9;
	else if (converted > 900)
        return 8;
	else if (converted > 850)
        return 7;
	else if (converted > 800)
        return 6;
	else if (converted > 750)
        return 5;
	else if (converted > 700)
        return 4;
	else if (converted > 650)
        return 3;
	else if (converted > 600)
        return 2;
	return 1;
}
unsigned int
TEMP_to_score(unsigned int converted)
{
    return converted / 20;
}

int
CDS_TEMP_get_and_alter()
{
    if (_CDS_TEMP_flag == _CDS_TEMP_FLAG_TEMP) {        // ADC0(Temperature)
        CDS_TEMP_temp = TEMP_to_score(ADC_data);
        _CDS_TEMP_flag = _CDS_TEMP_FLAG_CDS;
        ADMUX = 0x41;
    } else if (_CDS_TEMP_flag == _CDS_TEMP_FLAG_CDS) {  // ADC1(CDS)
        CDS_TEMP_cds = CDS_to_score(ADC_data);
        _CDS_TEMP_flag = _CDS_TEMP_FLAG_TEMP;
        ADMUX = 0x40;                                   // 다음은 ADC0(Temperature)
    } else
        _CDS_TEMP_flag = _CDS_TEMP_FLAG_TEMP;
    
    return _CDS_TEMP_flag;
}

#endif
