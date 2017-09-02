#include "AdminUI.h"
#include "Robot.h"
#include "Pilot.h"


int main(void){
	AdminUI_init();
	AdminUI_run();
	AdminUI_free();
	return 0;
}
