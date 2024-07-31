#ifndef                 __NODES_H__
#define                 __NODES_H__


#define                 CAN_12_ENGINE           1
#define                 CAN_13_TEMP             1

#define                 CAN_42_DIRSIG           1
#define                 CAN_42_SPEED_DIFF       2


#define                 GEAR_FWD                0
#define                 GEAR_REV                1

#define                 DIRSIG_NONE             0
#define                 DIRSIG_L                1
#define                 DIRSIG_R                2


/* joystick calibration - direction, threshold */
#define                 JOY_DIR                 -1   // 1 or -1 : 1이면 축 값이 높으면 증가, -1이면 감소
#define                 JOY_THRES_H             43
#define                 JOY_THRES_L             20


#endif
