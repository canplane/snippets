/* NODE 2
 * --------
 * Board 2 - DC, Servo Motor
 * LED : 좌측 지시등
 * SW 1 : 전진 기어
 * SW 2 : 후진 기어
 * 
 * 1 -> 2 : 시동
 * 4 -> 2 : 속력, 좌측 지시등
 */

#include                "nodes.h"

#include                "pub.h"
#include                "sw_led.h"
#include                "lcd.h"
#include                "adc.h"
#include                "urt1.h"
#include                "myCANLib.h"

#include                "motor.h"


struct MOb              rmsg;

unsigned char           engine = FALSE, engine_prev = FALSE;
unsigned char           dir_signal = DIRSIG_NONE, dir_signal_prev = DIRSIG_NONE;

unsigned char           gear = GEAR_FWD, gear_prev = GEAR_FWD, gear_set_failed = FALSE;
int                     speed = 0, speed_diff = 0;

// INT0: 전진 기어, INT1: 후진 기어
ISR(INT0_vect)
{
    if (engine && gear != GEAR_FWD) {
        if (!speed)     // 기어를 바꾸는 건 정지 상태일 때만
            gear = GEAR_FWD;
        else
            gear_set_failed = TRUE;
    }
}
ISR(INT1_vect)
{
    if (engine && gear != GEAR_REV) {
        if (!speed)     // 기어를 바꾸는 건 정지 상태일 때만
            gear = GEAR_REV;
        else
            gear_set_failed = TRUE;
    }
}

// CAN 수신 인터럽트 처리 루틴
ISR(CANIT_vect)
{
    CANIT_vect_rx(&rmsg);
    // printf("CANIT_vect: { %d, %d, %d, %d, %d, %d, %d, %d }\n", rmsg.data[0], rmsg.data[1], rmsg.data[2], rmsg.data[3], rmsg.data[4], rmsg.data[5], rmsg.data[6], rmsg.data[7]);  // for debugging
    switch (rmsg.data[0]) {     // 발신 노드 
        case 1:
            switch (rmsg.data[1]) {     // 타입
                case CAN_12_ENGINE:
                    engine = rmsg.data[2];
                    break;
            }    
            break;
        case 4:
            switch (rmsg.data[1]) {
                case CAN_42_DIRSIG:
                    dir_signal = rmsg.data[2];
                    break;
                case CAN_42_SPEED_DIFF:
                    if (rmsg.data[2] > JOY_THRES_H)
                        speed_diff = JOY_DIR;
                    else if (rmsg.data[2] < JOY_THRES_L)
                        speed_diff = -(JOY_DIR);
                    else
                        speed_diff = 0;
                    break;
            }
            break;
    }
}


int
main(void)
{
    SW_init(), LED_init(), LCD_init();
    SW_enable_int();
    URT1_init();
    stdout = URT1_out, stdin = URT1_in;

    can_init(b500k);
    can_int_rx_set(1, 0x02, EXT, 8, 0x1fffffff, 0x05);

    MOTOR_init();

    while (1) {
        /* 상태 변수 변경 감지 */
        if (engine != engine_prev) {
            printf("set engine %s\n", engine ? "on" : "off");
            
            engine_prev = engine;
        }
        if (gear != gear_prev) {
            switch (gear) {
                case GEAR_FWD:
                    msg = "SET GEAR FORWARD";
                    printf("set gear forward\n");
                    break;
                case GEAR_REV:
                    msg = "SET GEAR REVERSE";
                    printf("set gear reverse\n");
                    break;
            }

            gear_prev = gear;
        }
        if (gear_set_failed) {
            msg = "NOT IN REST";
            printf("failed to change gear: not in rest\n");

            gear_set_failed = FALSE;
        }

        /* LCD */
        if (!engine) {                      // engine is off
            LCD_cll_puts(0, 0, "ENGINE IS OFF");
            LCD_clear_line(1);
        } else {                            // normal state                       
            sprintf(strbuf, "SPEED:%2dkm/h", speed), LCD_cll_puts(0, 0, strbuf);
            sprintf(strbuf, "GEAR:%s", (gear == GEAR_FWD) ? "FORWARD" : "REVERSE"), LCD_cll_puts(1, 0, strbuf);
            if (msg) {
                LCD_cll_puts(1, 0, msg);
                mdelay(300);
                msg = NULL;
            }
        }


        /* 방향 지시등 */
        if (dir_signal != dir_signal_prev) {
            if (dir_signal == DIRSIG_L)
                LED_on();
            else
                LED_off();

            dir_signal_prev = dir_signal;
        }


        /* Motor */
        if (!engine) {              // engine is off
            MOTOR_servo_cntl(0);        // 동력 차단
            MOTOR_DC_cntl(0);           // 엔진 정지
            speed = speed_diff = 0;
        } else {                    // engine is on
            MOTOR_servo_cntl(180);      // 동력 연결
            if (gear == GEAR_FWD) {     // if forward
                if (speed_diff > 0) {
                    if (speed < 25) {
                        speed++;
                        printf("accelerated: %dkm/h\n", speed);
                    } else {
                        printf("speed limit: %dkm/h\n", speed);
                    }
                } else if (speed_diff < 0) {
                    if (speed > 0) {
                        speed--;
                        printf("braked: %dkm/h\n", speed);
                    } else {
                        printf("stopped\n");
                    }
                }
                MOTOR_DC_cntl(speed);
            } else {                    // if reverse
                if (speed_diff > 0) {
                    if (speed < 10) {
                        speed++;
                        printf("accelerated: %dkm/h\n", -speed);
                    } else {
                        printf("speed limit: %dkm/h\n", -speed);
                    }
                } else if (speed_diff < 0) {
                    if (speed > 0) {
                        speed--;
                        printf("braked: %dkm/h\n", -speed);
                    } else {
                        printf("stopped\n");
                    }
                }
                MOTOR_DC_cntl(-speed);
            }
            speed_diff = 0;
        }


        mdelay(40);
    }

    return 0;
}
