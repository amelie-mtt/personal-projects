#include <stdio.h>
#include <unistd.h>
#include "Robot.h"
#include "lightSensor.h"
#include <stdlib.h>

ContactSensor * capteur;

struct Speed_t{
	Cmd mD;
	Cmd mG;
};



MyRobot * my_robot_constructeur()
{
	MyRobot * this;
	this = (MyRobot * ) malloc(sizeof(MyRobot));
	this->mD = Motor_open(MOT_B);
	if (this->mD == NULL) PProseError("Ouverture du port B");
	this->mG = Motor_open(MOT_C);
	if (this->mG == NULL) PProseError("Ouverture du port C");
	this->contact = ContactSensor_open(CAPT_A);
	if (this->contact == NULL) PProseError("ouverture capteur ");
	return this;

}


void setWheelsVelocity(WheelVelocity vr, WheelVelocity vl)
{
	Wheel_right= vr;
	Wheel_left= vl;
	if (Motor_setCmd(Wheel_right.moteur, Wheel_right.commande) == -1) {
		PProseError("Commande moteur port B");
	}
	if (Motor_setCmd(Wheel_left.moteur, Wheel_left.commande) == -1) {
		PProseError("Commande moteur port C");
	}
}


bool_e hasBumped(MyRobot * robot)
{
	if(ContactSensor_getStatus(capteur == PRESSED)) return TRUE;
	else return FALSE;
}

Speed getRobotSpeed(MyRobot * robot)
{
	static Speed speed;

	speed.mD = Motor_getCmd(mD);
	speed.mG = Motor_getCmd(mG);
	return speed;

}


SensorsState getSensorsState(MyRobot * robot)
{
	static SensorsState sensor;
	sensor.contact = ContactSensor_getStatus(robot->contact);
	return sensor;
}

void robot_free(MyRobot * robot)
{
	Motor_close(robot->mD);
	Motor_close(robot->mG);
	ContactSensor_close(robot->contact);
}
