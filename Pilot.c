#include <stdio.h>
#include <assert.h>
#include "Pilot.h"
#include "pmu_tools.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#ifdef TRACE_ON
#define TRACE(fmt,...) do {\
fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__,\
__func__, ##__VA_ARGS__);\
fflush(stderr);} while(0)
#else
#define TRACE(fmt,...)
#endif


/*librairies pour les sockets
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "commun.h"*/

#define NB_STATE 4
#define NB_EVENT 3

struct VelocityVector_t{
	WheelVelocity vr;
	WheelVelocity vl;
};

struct SensorsState_t
{
	ContactSensor contact;
};

struct Speed_t
{
	WheelVelocity mD;
	WheelVelocity mG;
};

struct PiloteState_t{
	VelocityVector velo;
	SensorsState sensor;
};

typedef enum
{

	IDLE,				// etatt off
	RUNNING,		// etat on
	FORGET,			// pas de changement detat, mais consommation de l'event
	DEATH,			// MAE détruite
} State;

typedef enum
{
	NOP_A = 0,			// On ne fait rien
	STOP_MVT,
	SEND_MVT,
} TransitionAction;

typedef enum
{
	SET_VELOCITY,
	CHECK,
	EVAL_BUMP,
} EventType;

typedef struct{
	EventType type;
	VelocityVector velo;
} Event;

typedef struct{
	TransitionAction type;
	VelocityVector vel;
} Action;

// descriptoin d'une transaction
typedef struct {
	State toState;
	TransitionAction Action;
} Transition;

static Transition myTransition [NB_STATE][NB_EVENT] =
  {
    [IDLE][SET_VELOCITY]= {RUNNING, SEND_MVT},
		[IDLE][STOP_MVT]={DEATH,SEND_MVT},
		[RUNNING][SET_VELOCITY]={RUNNING,SEND_MVT},
		[RUNNING][CHECK]={IDLE,SEND_MVT},
		[RUNNING][STOP_MVT]={DEATH,SEND_MVT},
  };


State myState = DEATH;
static VelocityVector velocityStop;

void pilote_action(TransitionAction anAction)
{
	switch (anAction.type)
	{
		case NOP_A:
			break;
		case SEND_MVT:
		if(anAction.velo.vr !=0 && anAction.velo.vl !=0){
			sendMvt(anAction.velo);
		}else{
			sendMvt(velocityStop);
		}
			break;
		case STOP_MVT: pilot_free();
			break;
		case EVAL_BUMP: setVelocity();
			break;
		default: break;
	}
}

void pilot_run(Event *Event)
{
	Action anction;
	State aState;

	assert(myState!=DEATH);

	anAction = myTransition[myState][aEvent.type].Action.type;
	anAction.velo=aEvent.velo;
	anState = myTransition[myState][aEvent.type].toState;

	if (aState != FORGET) // FORGET_S A IMPLEMENTER .....
	{
		myState=aState;
		pilote_action(anAction); //fonction start à implémenter plus heau sur le modele de LAmp_performAction
	}else
}



void pilot_init()
{
	ProSE_Intox_init("127.0.0.1", 12345);
	robot = my_robot_constructeur();
	velocityStop.vr = 0;
	velocityStop.vl = 0;
	myState=IDLE;
}

void pilot_free()
{
	Robot_free(robot);
	myState=DEATH_S; //DEATH_S a comprendre
}

void stop (){
    Event aEvent;
    aEvent.type = SET_VELOCITY;
    aEvent.velo = velocityStop;
    ProSE_Intox_close();
    Pilot_run(aEvent);
}

void sendMvt (VelocityVector velo){
    assert(robot != NULL);
    setWheelsVelocity(robot, velo.vr, velo.vl);
}

void setVelocity (VelocityVector velo){
    Event aEvent;
    aEvent.type = SET_VELOCITY;
    aEvent.velo = velo;
    Pilot_run(aEvent);
}

void check (){
    Event aEvent;
    if (hasBumped(robot)){
        aEvent.type = SET_VELOCITY;
        aEvent.velo = velocityStop;
        Pilot_run(aEvent);
    }
}

PilotState getState (){
    PilotState state;
    state.velo.vr = -getRobotSpeed(robot).mD;
    state.velo.vl = -getRobotSpeed(robot).mG;
    state.contact = getSensorsState(robot);
    return state;
}
