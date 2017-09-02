#include "prose.h"
#ifndef ROBOT_H
#define ROBOT_H


typedef struct SensorsState_t SensorsState;
typedef struct ContactSensor sens;
typedef struct Speed_t Speed;


typedef struct
{
	Motor * mD;	/**< Le moteur droit. */
	Motor * mG;	/**< Le moteur gauche. */
	ContactSensor * contact;
} MyRobot;

Motor * mD;
Motor * mG;

typedef struct WheelVelocity_t
{
	Cmd commande;
	Motor * moteur
} WheelVelocity;

WheelVelocity Wheel_left;
WheelVelocity Wheel_right;


/**
 * Constructeur de mon robot.
 */

MyRobot * my_robot_contructeur();

extern void robot_free();

extern void setWheelsVelocity(MyRobot * robot,WheelVelocity vr, WheelVelocity vl);
extern bool_e hasBumped(MyRobot * robot);
extern Speed getRobotSpeed(MyRobot * robot);
extern SensorsState getSensorsState(MyRobot * robot);

#endif
