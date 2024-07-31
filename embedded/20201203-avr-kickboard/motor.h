/* Board 2 - DC Motor, RC Servo Motor
 *
 * pin :
 *   +5V, GND.
 *   out - PE1, PE0, PE3(OC3A), PE5(OC3C)
 * interrupt :
 *   nothing.
 *
 * # DC Motor
 * PE1 : IN2, PE0 : IN1, PE3 : EN_A(OC3A 비교 일치 파형)
 *
 * # RC Servo Motor
 * PE5 : Servo_1(OC3C 비교 일치 파형)
 *
 */

#ifndef                 __MOTOR_H__
#define                 __MOTOR_H__

#include                "pub.h"


#define                 _MOTOR_SERVO            0x20        // PE5
#define                 _MOTOR_EN               0x08        // PE3
#define                 _MOTOR_IN2              0x02        // PE1
#define                 _MOTOR_IN1              0x01        // PE0

/* used to calculate */
#define                 _MOTOR_PRESCALE         64
#define                 _MOTOR_SERVO_PERIOD     25          // RC servo 모터 주기 25 msec
#define                 _MOTOR_LEVEL            25           // <- 5
#define                 _MOTOR_MEASURED         125         // F_CPU/2/_MOTOR_PRESCALE/1000


static volatile int     _MOTOR_speed = 0, _MOTOR_deg = 0;

// T/C3_OC_A는 DC 모터(_MOTOR_EN), _C는 RC Servo 모터(_MOTOR_IN2, _IN1)
void
MOTOR_init(void)
{
    // init port : PG3/1/0, PC[7:0]
    on(DDRE, _MOTOR_SERVO | _MOTOR_EN | _MOTOR_IN2 | _MOTOR_IN1);             // DC 모터

    TCCR3A = TCCR3B = 0;
    on(TCCR3A, _BV(COM3A1) | _BV(COM3C1));                  // OC A, C 출력 모드 설정. 비교 일치 발생 시 모두 OC3A(PE3), OC3C(PE5)는 LOW로 바뀜
    on(TCCR3B, _BV(CS31) | _BV(CS30));                      // 분주비 64
    on(TCCR3B, _BV(WGM33)), on(TCCR3A, _BV(WGM31));         // 위상 교정 PWM, TOP는 ICR3
    
    // TOP = 3125, PWM 파형은 40Hz(25msec)
    // 위상 교정 PWM 모드에서 PWM 주파수는 F_CPU / (2 * PRESCALE * TOP)
    ICR3 = _MOTOR_MEASURED * _MOTOR_SERVO_PERIOD;

    OCR3C = 70;                                             // 최저값(output compare) PE5 pin output
}

// 0 <= |speed| <= 25, speed < 0면 counter-clockwise
void
MOTOR_DC_cntl(int speed)
{
    if (_MOTOR_speed == speed || speed < -(_MOTOR_LEVEL) || speed > _MOTOR_LEVEL)
        return;
    if (_MOTOR_speed * speed < 0) {
        off(PORTE, _MOTOR_IN1), off(PORTE, _MOTOR_IN2);
        //mdelay(400);
    }
    _MOTOR_speed = speed;

    if (speed > 0) {                    // clockwise
        on(PORTE, _MOTOR_IN1), off(PORTE, _MOTOR_IN2);
        OCR3A = (ICR3 / _MOTOR_LEVEL) * speed;
    } else if (speed < 0) {             // counter-clockwise
        off(PORTE, _MOTOR_IN1), on(PORTE, _MOTOR_IN2);
        OCR3A = (ICR3 / _MOTOR_LEVEL) * (-speed);
    } else {                            // motor stop
        off(PORTE, _MOTOR_IN1), off(PORTE, _MOTOR_IN2);
    }
    //mdelay(400);

    /*off(PORTE, _MOTOR_IN2 | _MOTOR_IN1);
    //mdelay(400);
    if (speed > 0) {                    // clockwise
        OCR3A = (ICR3 / _MOTOR_LEVEL) * speed;
        on(PORTE, _MOTOR_IN1);
    } else if (speed < 0) {             // counter-clockwise
        OCR3A = (ICR3 / _MOTOR_LEVEL) * (-speed);
        on(PORTE, _MOTOR_IN2);
    } else {                            // motor stop
    }
    mdelay(400);*/
}
// Servo 모터 회전 제어(0 <= deg <= 180 : clockwise)
void
MOTOR_servo_cntl(int deg)
{
    if (_MOTOR_deg == deg || deg < 0 || deg > 180)
        return;
    _MOTOR_deg = deg;

    OCR3C = _MOTOR_MEASURED * (1.6*deg/180 + (0.15*deg/180 + 0.6));
    //mdelay(400);
}


/* deprecated */
int
MOTOR_to_speed(unsigned int volt, unsigned int max)     // DC, y
{
    float score;
    score = 54 * volt / max;
    if (score < 5)
        return -25;
    if (score < 10)
        return -20;
    if (score < 15)
        return -15;
    if (score < 20)
        return -10;
    if (score < 25)
        return -5;
    if (score < 30)
        return 0;
    if (score < 35)
        return 5;
    if (score < 40)
        return 10;
    if (score < 45)
        return 15;
    if (score < 50)
        return 20;
    return 25;
}
/* deprecated */
int
MOTOR_to_deg(unsigned int volt, unsigned int max)      // Servo, x
{
    int deg;
    deg = 180 * volt / max;
    if (-10 < volt && volt < 10)
        return 0;
    return deg;
}


#endif
