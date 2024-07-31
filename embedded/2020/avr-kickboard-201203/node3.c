/* NODE 3
 * --------
 * Board 3 - Ultrasonic Sensor
 * 
 * 1 -> 3 : 온도 보정
 */

#include                "nodes.h"

#include                "pub.h"
#include                "sw_led.h"
#include                "lcd.h"
#include                "adc.h"
#include                "urt1.h"
#include                "myCANLib.h"

#include                "usonic.h"


struct MOb              rmsg;

unsigned char           rear_collision_warn = FALSE;

// CAN 수신 인터럽트 처리 루틴
ISR(CANIT_vect)
{
    CANIT_vect_rx(&rmsg);
    switch (rmsg.data[0]) {
        case 1:
            switch (rmsg.data[1]) {
                case CAN_13_TEMP:
                    USONIC_temp = rmsg.data[2];
                    break;
            }    
            break;
    }
}

int
main(void)
{
    int cnt = 0;

    SW_init(), LED_init(), LCD_init();
    //SW_enable_int();
    //URT1_init();
    //stdout = URT1_out, stdin = URT1_in;

    can_init(b500k);
    can_int_rx_set(1, 0x03, EXT, 8, 0x1fffffff, 0x05);

    USONIC_init();

    while (1) {
        /* LCD */
        sprintf(strbuf, "DIST:%4dmm %2d'C", USONIC_dist, USONIC_temp), LCD_cll_puts(0, 0, strbuf);
        LCD_cll_puts(1, 0, rear_collision_warn ? "PROXIMITY WARN" : "");


        /* Ultrasonic 갱신 */
        USONIC_trigger();


        /* 후방 충돌 경고 - 3회 경고 누적 */
        if (!rear_collision_warn) {
            if (USONIC_dist < 300) {
                if (cnt < 3)
                    cnt++;
            } else {
                if (cnt > 0)
                    cnt--;
            }
        } else {
            if (USONIC_dist < 300) {
                if (cnt > 0)
                    cnt--;
            } else {
                if (cnt < 3)
                    cnt++;
            }
        }
        if (cnt == 3) {
            cnt = 0;

            rear_collision_warn = !rear_collision_warn;
            if (rear_collision_warn)
                LED_on();
            else
                LED_off();
        }


        mdelay(200);
    }

    return 0;
}
