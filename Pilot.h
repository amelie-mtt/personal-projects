#ifndef PILOT_H
#define PILOT_H

#include "Robot.h"


typedef struct PiloteState_t PiloteState;
typedef struct VelocityVector_t VelocityVector;

extern void pilot_init();
extern void pilot_free();
extern void stop();
extern void sendMvt();
extern void setVelocity(VelocityVector velo);
extern void check();
extern PiloteState getState(); // = piloteState

#endif
