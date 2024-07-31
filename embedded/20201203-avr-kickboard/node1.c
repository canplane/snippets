/* NODE 1
 * --------
 * Board 1 - CDS, Temperature Sensor
 * LED : 전조등
 * SW 1 : 시동
 * 
 * 1 -> 2 : 시동
 * 1 -> 3 : 온도 보정
 */

#include                "nodes.h"

#include                "pub.h"
#include                "sw_led.h"
#include                "lcd.h"
#include                "adc.h"
#include                "urt1.h"
#include                "myCANLib.h"

#include                "cds_temp.h"


                                        // rcv, -, -, -, { sen, type, 데이터들
struct MOb              msg_12_ENGINE = { 0x02, 0, EXT, 8, { 1, CAN_12_ENGINE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };
struct MOb              msg_13_TEMP = { 0x03, 0, EXT, 8, { 1, CAN_13_TEMP, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };

unsigned char           engine, engine_prev = FALSE;

int                     temp_prev = -1;

// INT0: 시동 on, INT1: 시동 off
ISR(INT0_vect)
{
    engine = TRUE;
}
ISR(INT1_vect)
{
    engine = FALSE;
}


int
main(void)
{
    SW_init(), LED_init(), LCD_init();
    SW_enable_int();
    //URT1_init();
    //stdout = URT1_out, stdin = URT1_in;

    can_init(b500k);

    CDS_TEMP_init();

    while (1) {
        /* LCD */
        sprintf(strbuf, "ENGINE:%s", engine ? "ON" : "OFF"), LCD_cll_puts(0, 0, strbuf);

        CDS_TEMP_get_and_alter();
        sprintf(strbuf, "LIGHT:%2d TEMP:%2d", CDS_TEMP_cds, CDS_TEMP_temp), LCD_cll_puts(1, 0, strbuf);


        /* 시동 */
        if (engine != engine_prev) {
            msg_12_ENGINE.data[2] = engine;
            can_tx(7, &msg_12_ENGINE, 0);

            engine_prev = engine;
        }


        /* 전조등 */
        if (CDS_TEMP_cds <= 6)
            LED_on();
        else
            LED_off();

        
        /* 온도 보정 */
        if (CDS_TEMP_temp != temp_prev) {
            msg_13_TEMP.data[2] = temp_prev = CDS_TEMP_temp;
            can_tx(7, &msg_13_TEMP, 0);
        }


        mdelay(200);
    }

    return 0;
}
