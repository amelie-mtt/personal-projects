#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "AdminUI.h"
#include "Pilot.h"
#include "Robot.h"

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/*librairies pour les sockets*/
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "defs.h"


//static int tps_attente;
//static int tempo = 1;

static bool_e keepGoing = TRUE;
static void AdminUI_run ();

struct VelocityVector_t {
    WheelVelocity vr;
    WheelVelocity vl;
};

struct Speed_t {
    WheelVelocity mD;
    WheelVelocity mG;
};

struct SensorsState_t
{
	ContactSensor contactFloor;
	ContactSensor contactFront;
};

struct PilotState_t {
    VelocityVector vel;
    SensorsState sens;
};

struct Direction_t {
    STOP,
    DROITE,
    GAUCHE,
    AVANCER,
    RECULER,
    IDLE = 0
}


void AdminUI_init(){
  Pilot_init();
};

void AdminUI_ask4Log(){
  PilotState state;
  Pilot_check();
  state = Pilot_getState();
  printf("roue droite : %i% \nroue gauche : %i% \ncontactAvant : %i \ncontactSol : %i \n",
  state.vel.vr, state.vel.vl, state.sens.contactFront, state.sens.contactFloor);

}

void AdminUI_askClearLog(){
  clearLog();
}

void AdminUI_askMvt(Direction dir){
    VelocityVector vel;
    switch (dir) {
        case AVANCER :
            vel.vl = +10;
            vel.vr = +10;
        break;
        case RECULER :
            vel.vl = -10;
            vel.vr = -10;
        break;
        case GAUCHE :
            vel.vl = +20;
            vel.vr = +10;
        break;
        case DROITE :
            vel.vl = +10;
            vel.vr = +20;
        break;
        case STOPPER :
            vel.vl = 0;
            vel.vr = 0;
        break;
    }
    Pilot_setVelocity(vel);
}

static void Admin_display(){

  int res;
  while (keepGoing == TRUE){
    printf ("que voulez vous faire ??\n", );
    printf ("tapez A pour avancer");
	  printf ("tapez C pour Vérifier si le robot s'est crasher ");
	  printf ("tapez R pour netoyer");
	  printf ("tapez Q pour quiter");
	  res=scanf("que voulez vous faire?");
    switch{
  		case (res==A):
      printf("pour diriger le robot entrer e, x, s, d ou q  ");
  			AdminUI_run();
  		  break;
  		case (res==C):
  			ask4log();
  		  break;
  		case (res==R):
  			askClearLog();
  		  break;
  		case (res==Q):
  			quite();
  		  break;
    default: printf("ERROR [] Action inconnue\n ");
  	}
  }
}

//Pour sortir du programme
static void Admin_run(){
  /* Variables impliquées dans la temporisation. */
  int clocks_per_msec = CLOCKS_PER_SEC / 1000;
  int tps_attente;
  volatile clock_t c0, c1;
  Direction direction;
  char dir;
  scanf(" %c", &dir);
  if(dir != 'e'){
      switch(dir) {
          case 'e': direction = AVANCER; break;
          case 'x': direction = RECULER; break;
          case 's': direction = GAUCHE; break;
          case 'd': direction = DROITE; break;
          case 'q': direction = STOPPER; break;
      }
      ask4Log(direction);
      /* Gestion de la temporisation. */
		c1 = clock();

		tps_attente = (tempo * CLOCKS_PER_SEC - c1 + c0) / clocks_per_msec;
		printf("attente = %d \n", tps_attente);

		if (tps_attente > 0) {
			usleep(tps_attente * 1000);
		} else {
			printf("\ntemps de traitement > %d sec ! \n\n", tempo);
		}
		fflush(stdout);
    }
}

void AdminUI_free(){
    Pilot_free();
}

void AdminUI_quit(int dum){
    keepGoing = FALSE;
    Pilot_stop();
}
void AdminUI_start(){
    AdminUI_display();
}

/*

int main (void){
    int un_socket;
    struct sockaddr_in adresse_du_serveur;

    un_socket = socket(AF_INET,SOCK_STREAM,0);
    adresse_du_serveur.sin_family = AF_INET;
    adresse_du_serveur.sin_port=htons(PORT_DU_SERVEUR);
    adresse_du_serveur.sin_addr= *((struct in_addr*)gethostbyname("127.0.0.1")->h_addr_list[0]);
    connect(un_socket,(struct sockaddr *)&adresse_du_serveur,sizeof(adresse_du_serveur));

    read(un_socket,&donnees,sizeof(donnees));
    donnees.age_capitaine = ntohl(donnees.age_capitaine);
    printf("Donnee recue : \nMessage : %s\nAge du capitaine : %d\n",donnees.message,donnees.age_capitaine);

    close(un_socket);

    return 0;
}

*/
