/* NODE 4
 * --------
 * Board 4 - Joystick
 * LED : 우측 지시등
 * SW 1 : 좌측 지시등
 * SW 2 : 우측 지시등
 * 
 * 4 -> 2 : 속력, 좌측 지시등
 */

#include                "nodes.h"

#include                "pub.h"
#include                "sw_led.h"
#include                "lcd.h"
#include                "adc.h"
#include                "urt1.h"
#include                "myCANLib.h"

#include                "joy.h"


/* joystick calibration - axis */
#define                 JOY_val                 JOY_x


struct MOb              msg_42_DIRSIG = { 0x02, 0, EXT, 8, { 4, CAN_42_DIRSIG, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };
struct MOb              msg_42_SPEED_DIFF = { 0x02, 0, EXT, 8, { 4, CAN_42_SPEED_DIFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };


/* state variables */

unsigned char           dir_signal = DIRSIG_NONE, dir_signal_prev = DIRSIG_NONE;


/* interrupts */

// INT0: 좌측지시등 toggle, INT1: 우측지시등 toggle
ISR(INT0_vect)
{
    if (dir_signal == DIRSIG_L)
        dir_signal = DIRSIG_NONE;
    else
        dir_signal = DIRSIG_L;
}
ISR(INT1_vect)
{
    if (dir_signal == DIRSIG_R)
        dir_signal = DIRSIG_NONE;
    else
        dir_signal = DIRSIG_R;
}


int
main(void)
{
    SW_init(), LED_init(), LCD_init();
    SW_enable_int();
    //URT1_init();
    //stdout = URT1_out, stdin = URT1_in;

    can_init(b500k);

    JOY_init();

    while (1) {
        /* LCD */
        switch (dir_signal) {
            case DIRSIG_NONE:
                LCD_cll_puts(0, 0, "NO SIGNAL");
                break;
            case DIRSIG_L:
                LCD_cll_puts(0, 0, "LEFT SIGNAL ON");
                break;
            case DIRSIG_R:
                LCD_cll_puts(0, 0, "RIGHT SIGNAL ON");
                break;
        }
        if (JOY_val > JOY_THRES_H)
            LCD_cll_puts(1, 0, (JOY_DIR == -1) ? "SPEED DOWN" : "SPEED UP");
        else if (JOY_val < JOY_THRES_L)
            LCD_cll_puts(1, 0, (JOY_DIR == -1) ? "SPEED UP" : "SPEED DOWN");
        else
            LCD_clear_line(1);
        // sprintf(strbuf, "(X:%2d Y:%2d)", JOY_x, JOY_y), LCD_cll_puts(1, 0, strbuf);  // for debugging


        /* 방향 지시등 */
        if (dir_signal != dir_signal_prev) {
            if (dir_signal == DIRSIG_R)
                LED_on();
            else
                LED_off();

            msg_42_DIRSIG.data[2] = dir_signal;
            can_tx(7, &msg_42_DIRSIG, 0);

            dir_signal_prev = dir_signal;
        }


        /* Joystick 갱신 */
        JOY_get_and_alter();


        /* 속력 */
        msg_42_SPEED_DIFF.data[2] = JOY_val;
        can_tx(7, &msg_42_SPEED_DIFF, 0);

        
        mdelay(40);
    }

    return 0;
}
