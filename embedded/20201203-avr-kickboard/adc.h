/* ADC
 *
 * pin :
 *   in - PF[1:0]
 * interrupt :
 *   ADC_vect
 *
 * ADMUX가 0x40이면 ADC0(PF0), 0x41이면 ADC1(PF1) 입력 변환
 *
 */

#ifndef                 __ADC_H__
#define                 __ADC_H__

#include                "pub.h"


unsigned int            ADC_data;

void
ADC_init(void)
{
    /*// init port : PF1(ADC1), PF0(ADC0)
    off(DDRF, 0x03);        // 아날로그 입력 

    on(ADMUX, _BV(REFS0));  // 기준전압; 외부 캐퍼시터 가진 AVcc(AREF 핀)
                            // AD변환 데이터 정렬; 오른쪽 정렬 
                            // AD변환 채널 선택; PortF 0 핀
                            // -> 0x40
      
    //DDRF  = 0xFC;         // PortF[3..0] 입력으로 설정, PortF[7..4] 출력으로 설정 
    DIDR0 = 0x03;           // 디지털 입력 불가 PortF[3..0]

    on(ADCSRA, _BV(ADEN) | _BV(ADSC) | _BV(ADIE));
    // ADC 인에이블, ADC 변환 시작, ADC인터럽트 인에이블 
    // ADC 클럭 설정; XTAL의1/2(8MHz)*/
    ADMUX = 0x40;   // ��������; �ܺ� ĳ�۽��� ���� AVcc(AREF ��)
                    // AD��ȯ ������ ����; ������ ���� 
                    // AD��ȯ ä�� ����; PortF 0 ��    

    DDRF = 0xf0;    // PortF[3..0] �Է����� ����, PortF[7..4] ������� ���� 
    DIDR0 = 0x0f;   // ������ �Է� �Ұ� PortF[3..0]

    ADCSRA = 0xc8;  // ADC �ο��̺�, ADC ��ȯ ����, ADC���ͷ�Ʈ �ο��̺� 
                    // ADC Ŭ�� ����; XTAL��1/2(8MHz)
    sei();
}


ISR(ADC_vect)
{
    ADC_data = ADC;
    ADCSRA = 0xc8;      //on(ADCSRA, _BV(ADSC));
}


#endif
