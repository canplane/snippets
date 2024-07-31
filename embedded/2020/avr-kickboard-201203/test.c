#include                "pub.h"
#include                "sw_led.h"
#include                "lcd.h"
#include                "adc.h"
#include                "urt1.h"


// delay 있어야겠다 싶으면 넣자. LCD_clear라든가 init 후라든가
#define                 EXPERIMENT              2
#if EXPERIMENT == 1

ISR(INT0_vect)
{
	LED_on();
    LCD_cll_puts(1, 0, "LED is on");
	printf("LED is on\n");
}
ISR(INT1_vect)
{
	LED_off();
    LCD_cll_puts(1, 0, "LED is off");
	printf("LED is off\n");
}

#elif EXPERIMENT == 2

#define                 BOARD                   2
#if BOARD == 1
#include                "cds_temp.h"
#elif BOARD == 2
#include                "motor.h"
#elif BOARD == 3
#include                "usonic.h"
#elif BOARD == 4
#include                "joy.h"
#endif

#elif EXPERIMENT == 3

#define                 CAN_W                   1
#define                 CAN_R                   2
#define                 CAN_RW                  3
#define                 CAN_R_INT               4
#define                 CAN_RW_INT              5   // 중간 노드는 인터럽트 방식 잘 안되는거 같다 안에 폴링이 있어서? 그냥 송신이 폴링이니까 수신도 폴링으로 두는게 나을듯

#define                 CAN_TYPE                CAN_R_INT
#include                "myCANLib.h"

//                                    id  rtr ide dlc   data[8]
struct MOb              CAN_tmsg = { 0x23, 0, EXT, 8, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };
// id :  CAN ID
// rtr(원격 전송 요청) :  0이면 CAN 메시지가 데이터 프레임. 1이면 CAN 메시지가 원격 프레임(데이터 버스 상의 어떤 노드에서 다른 노드로 데이터를 전송하여 줄 것을 요청할 때 사용. 데이터 필드는 없다.)
// ide :  표준 혹은 확장 포맷 구분 :  STD | EXT
// dlc :  데이터 길이 설정(0에서 8까지)
struct MOb              CAN_rmsg;

#if CAN_TYPE == CAN_R_INT
// CAN recieve interrupt
ISR(CANIT_vect)
{
    _CANIT_vect_rx(&CAN_rmsg);
    LCD_puts(1, 0, (char *)CAN_rmsg.data);
    printf("'%s' received\n", (char *)CAN_rmsg.data);
}
#elif CAN_TYPE == CAN_RW_INT
int                     CAN_received = FALSE;

ISR(CANIT_vect)
{
    _CANIT_vect_rx(&CAN_rmsg);
    CAN_received = TRUE;
}
#endif

#endif


int main(void)
{
    SW_init(), LED_init(), LCD_init();
    URT1_init();
    stdout = URT1_out, stdin = URT1_in;
    //sei();

    LCD_puts(0, 0, "Experiment"), LCD_puts(0, 11, itoa(EXPERIMENT, strbuf));

#if EXPERIMENT == 1         /* Switch, LED, USART1 */

    while (1);

#elif EXPERIMENT == 2       /* Board 1..4 */
    LCD_puts(0, 12, "-"), LCD_puts(0, 13, itoa(BOARD, strbuf));
    printf("Board : %d\n", BOARD);

#if BOARD == 1
    CDS_TEMP_init();
#elif BOARD == 2
    MOTOR_init();
#elif BOARD == 3
    USONIC_init();
#elif BOARD == 4
    JOY_init();
#endif

#if BOARD == 1                  /* CDS, Temperature */
    LCD_puts(1, 0, "TMP"), LCD_puts(1, 8, "CDS");
    while (1) {
        CDS_TEMP_get_and_alter();
        sprintf(strbuf, "%04d", CDS_TEMP_temp), LCD_puts(1, 3, strbuf);
        sprintf(strbuf, "%04d", CDS_TEMP_cds), LCD_puts(1, 11, strbuf);
        printf("Temperature: %d, CDS: %d\n", CDS_TEMP_temp, CDS_TEMP_cds);
    }
#elif BOARD == 2                /* DC, RC Servo Motor */
    printf("1. Forward Fast, 0 deg\n");
    MOTOR_DC_cntl(25), MOTOR_servo_cntl(0);   // 한쪽 끝
    mdelay(3000);

    printf("2. Stop\n");   // forward에서 바로 reverse 가면 터짐
    MOTOR_DC_cntl(0);
    mdelay(1000);
    
    printf("3. Reverse Fast, 180 deg\n");
    MOTOR_DC_cntl(-25), MOTOR_servo_cntl(180);     // 반대쪽 끝
    mdelay(3000);

    printf("4. Stop\n");
    MOTOR_DC_cntl(0);
    mdelay(1000);
    
    printf("5. Forward slow, 135 deg\n");
    MOTOR_DC_cntl(10), MOTOR_servo_cntl(135);     // 약간 돌아옴
    mdelay(3000);

    printf("6. Stop\n");
    MOTOR_DC_cntl(0);
    mdelay(1000);

    printf("7. Reverse slow, 45 deg\n");
    MOTOR_DC_cntl(MOTOR_to_speed(10, 50)), MOTOR_servo_cntl(MOTOR_to_deg(10, 50));  // 반대쪽 끝에서 약간 못 미침
    mdelay(3000);

    printf("8. Stop, 90 deg\n");
    MOTOR_DC_cntl(MOTOR_to_speed(25, 50)), MOTOR_servo_cntl(MOTOR_to_deg(25, 50));  // 멈춤
    mdelay(1000);

    printf("9. Stop, 0 deg\n");
    MOTOR_DC_cntl(0), MOTOR_servo_cntl(0);      // 멈춤 유지
    mdelay(1000);
#elif BOARD == 3                /* Ultrasonic */
    LCD_puts(1, 0, "DIST: ");
    while (1) {
        USONIC_trigger();
        sprintf(strbuf, "%04dmm", USONIC_dist), LCD_puts(1, 6, strbuf);
        printf("Distance: %dmm\n", USONIC_dist);
    }
#elif BOARD == 4                /* Joystick */
    LCD_puts(1, 0, "X: "), LCD_puts(1, 6, "Y: ");
    while (1) {
        JOY_get_and_alter();
        sprintf(strbuf, "%02d", JOY_x), LCD_puts(1, 3, strbuf);
        sprintf(strbuf, "%02d", JOY_y), LCD_puts(1, 9, strbuf);
        printf("X: %d, Y: %d\n", JOY_x, JOY_y);
    }
#endif

#elif EXPERIMENT == 3       /* CAN (polling) */
    LCD_puts(0, 12, "-"), LCD_puts(0, 13, itoa(CAN_TYPE, strbuf));
    printf("CAN Type : %d\n", CAN_TYPE);

    can_init(b250k);

#if CAN_TYPE == CAN_W           /* 송신부 */
    int i = 0;

    while (1) {
        sprintf((char *)CAN_tmsg.data, "Hello %2d", i = (i + 1) % 50);
        LCD_puts(1, 0, (char *)CAN_tmsg.data);
        printf("transferring '%s'\n", (char *)CAN_tmsg.data);
        can_tx(7, &CAN_tmsg, 0);
        //or can_tx(0, &CAN_tmsg, 0);  // obj=1 , rtr=
        mdelay(1000);
    }
#elif CAN_TYPE == CAN_R         /* 수신부(폴링 방식) */
    can_rx_set(1, 0x23, EXT, 8, 0x1fffffff, 0x05);
    //or can_rx_set(0, 0x23, EXT, 8, 0x00000000, 0x00);
    
    while (1) {
        can_rx(1, &CAN_rmsg);
        //or can_rx(0, &CAN_rmsg);
        LCD_puts(1, 0, (char *)CAN_rmsg.data);
        printf("'%s' received\n", (char *)CAN_rmsg.data);

        udelay(100);
    }
#elif CAN_TYPE == CAN_RW        /* 중간 노드 */
    can_rx_set(1, 0x23, EXT, 8, 0x1fffffff, 0x05);

    while (1) {
        can_rx(1, &CAN_rmsg);
        can_tx(7, &CAN_rmsg, 0);
        LCD_puts(1, 0, (char *)CAN_rmsg.data);
        printf("'%s' passed\n", (char *)CAN_rmsg.data);

        udelay(100);
    }
#elif CAN_TYPE == CAN_R_INT     /* 수신부(인터럽트 방식) */
    //
    // can_rx_set(1, 0x2, EXT, 8, 0x00000000, 0x00);  // receive all
    // can_rx_set(1, 0x23, EXT, 8, 0x1fffffff, 0x05);
    can_int_rx_set(1, 0x23, EXT, 8, 0x1fffffff, 0x05);
        // when ID mask is 0000 0000, MOb 1 no filtering
        // when ID mask is ffff ffff, MOb 1 filtering
        // when ID mask is ffff 0000, MOb 1 partial filtering
        // RTR mask 1, IDE mask 1;
    while (1) {
        // can_rx(1, &CAN_rmsg);

        udelay(100);
    }
#elif CAN_TYPE == CAN_RW_INT    /* 중간 노드(인터럽트 방식) */
    can_int_rx_set(1, 0x23, EXT, 8, 0x1fffffff, 0x05);

    while (1) {
        if (CAN_received) {
            CAN_received = FALSE;
            //can_tx(7, &CAN_rmsg, 0);
            LCD_cll_puts(1, 0, (char *)CAN_rmsg.data);
            printf("'%s' passed\n", (char *)CAN_rmsg.data);
        }

        udelay(100);    // delay 안 넣어주면 위에 if 문도 동작 안하는 듯. while 문 안에는 기본적으로 조금의 delay라도 넣어줘야 할 거 같다
        // CAN_received가 volatile이 아니라서 그런 거 아님?
    }
#endif

#endif

    LCD_clear();
    LCD_puts(0, 0, "END");
    printf("END\n");
    mdelay(1000);

    return 0;
}
