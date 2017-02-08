
/*

Sample user code for 2 tasks :

- one fast/high rate  HighTask
- one slow/low rate   LowTask

Periods are in ms (see periods.h)

*/

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "comportement.h"
#include "what_mode.h"
#include "periods.h"

#include <stdbool.h> 
#define PORT_C_DROITE NXT_PORT_S1
#define PORT_C_GAUCHE NXT_PORT_S2
#define PORT_C_DISTANCE NXT_PORT_S3
#define PORT_BUTTON NXT_PORT_S4
#define VMAX 30
static int blanc_gauche;
static int blanc_droite;
static int noir_gauche;
static int noir_droite;
static int distanceMax = 0;
/*-----------------------------
   OSEK declarations 
-------------------------------
DON'T MODIFY
------------------------------*/
DeclareCounter(SysTimerCnt);
DeclareResource(lcd);
DeclareTask(LowTask);
DeclareTask(HighTask);

void usr_init();
static bool buf_what_mode[2];
static int actual_mode =0;
static int compteur = 0;
/*------------------------------
 Function to be invoked from a category 2 interrupt
--------------------------------
DON'T MODIFY
------------------------------*/
void user_1ms_isr_type2(void)
{
	StatusType ercd;
	
	/*
	 *  Increment OSEK Alarm System Timer Count
     */
	ercd = SignalCounter( SysTimerCnt );
	if( ercd != E_OK ){
		ShutdownOS( ercd );
	}
}

/* ---- HERE BEGINS YOUR CODE ----*/

/* Init and terminate OSEK */
void ecrobot_device_initialize() {
   /*
      HERE: put here specific code that will be executed ONCE
            when the application starts
      TYPICALLY: initialization of (light) sensors
   */
	ecrobot_init_sonar_sensor(PORT_C_DISTANCE);
	ecrobot_set_light_sensor_active(PORT_C_GAUCHE);
	ecrobot_set_light_sensor_active(PORT_C_DROITE);
}

void ecrobot_device_terminate() {
   /*
      HERE: put here specific code that will be executed ONCE
            when the application stops
      TYPICALLY: finalization of (light) sensors
   */
	ecrobot_term_sonar_sensor(PORT_C_DISTANCE);
	ecrobot_set_light_sensor_inactive(PORT_C_GAUCHE);
	ecrobot_set_light_sensor_inactive(PORT_C_DROITE);
}

/*------------------------------
  Definitions
--------------------------------
shared vars, functions etc
------------------------------*/

int mybuffer;

/* Global user initialization:
   put here any code to be executed:
   - ONCE
   - AFTER devices (and brick) initialization
   - BEFORE the start of reactive loop 
*/
void usr_init(){
	/*Initialisation du buffer pour le mode*/
	buf_what_mode[0] = true;
	buf_what_mode[1] = true;
	
	GetResource(lcd) ;
	
	display_clear(0);
	display_goto_xy(0, 0);	
	display_string("Mettre le robot");
	display_goto_xy(0, 1);	
	display_string("sur le blanc");

// TO DO
	while(!ecrobot_is_ENTER_button_pressed()) {

		blanc_gauche = ecrobot_get_light_sensor(PORT_C_GAUCHE) + 20;
		blanc_droite = ecrobot_get_light_sensor(PORT_C_DROITE) + 20;

		display_clear(1);
		display_goto_xy(0, 0);
			
		display_string("---- Blanc ----");
		
		display_goto_xy(0, 1);
		
		display_string("G => ");
		
		display_goto_xy(5, 1);
		display_int(blanc_gauche, 3);
		display_goto_xy(0, 2);
		
		display_string("D => ");
		
		display_goto_xy(5, 2);
		display_int(blanc_droite, 3) ;
		display_update();
		
		
		display_goto_xy(0, 4);
		display_string("Push button");
		
		systick_wait_ms(800);
	}

	systick_wait_ms(1000);

	while(!ecrobot_is_ENTER_button_pressed()) {

		noir_gauche = ecrobot_get_light_sensor(PORT_C_GAUCHE);
		noir_droite = ecrobot_get_light_sensor(PORT_C_DROITE);

		display_clear(1);
		display_goto_xy(0, 0);
			
		display_string("---- Noir ----");
		
		display_goto_xy(0, 1);
		
		display_string("G => ");
		
		display_goto_xy(5, 1);
		display_int(noir_gauche, 3);
		display_goto_xy(0, 2);
		
		display_string("D => ");
		
		display_goto_xy(5, 2);
		display_int(noir_droite, 3);
		display_update();
		
		display_goto_xy(0, 4);
		display_string("Push button");
	
		systick_wait_ms(800);
	}
	
	systick_wait_ms(1000);
	
	while(!ecrobot_is_ENTER_button_pressed()) {
	
		distanceMax = ecrobot_get_sonar_sensor(PORT_C_DISTANCE);
		display_clear(1);
		display_goto_xy(0, 0);
			
		display_string("-- Distance --");
		
		display_goto_xy(0, 1);
		
		display_string("Dist => ");
		
		display_goto_xy(9, 1);
		display_int(distanceMax, 3);
		display_update();
		
		display_goto_xy(0, 4);	
		display_string("Push button");
		
		systick_wait_ms(800);
	}
	
	systick_wait_ms(1000);


	while(!ecrobot_is_ENTER_button_pressed()) {
	
		display_clear(1);
		display_goto_xy(0, 0);	
		display_string("Start !");
		display_goto_xy(0, 2);	
		display_string("Push button");
		display_update();

		systick_wait_ms(800);
	}
	
	display_clear(1);
	display_goto_xy(0, 0);	
	
	display_string("Calibrage done !");
	
	display_update();

	display_clear(1);

	comportement_init();
	what_mode_init();

	ReleaseResource(lcd);
}


/*------------------------------
  Tasks definition
--------------------------------
- MUST be declared with the
  OSEK macro "TASK"
- The last instruction MUST be
  TerminateTask()
------------------------------*/

//Pour ramener la donnée du capteur entre [0,100]
_real calib(long Sens,_real noir, _real blanc) {
	_real calib_color = (noir - Sens) / (noir - blanc) * 100;
	
	if (calib_color > 100){
		return 100;
	} else if (calib_color < 0) {
		return 0;
	} else {
		return calib_color;
	}
}

//Checking de distance
_real distance_check(int d) {
	if (d > distanceMax){
		return 15;
	} else {
		return 5;
	}
}

TASK(LowTask) { // ==> What_mode

	display_goto_xy(0, 0);	
	display_string("What mode !");
	display_update();

	//Valeur des capteurs
	what_mode_I_distance(distance_check(ecrobot_get_sonar_sensor(PORT_C_DISTANCE)));
	what_mode_I_Cd(calib(ecrobot_get_light_sensor(PORT_C_DROITE),noir_droite, blanc_droite));
	
	what_mode_step();
	
	TerminateTask();
}

TASK(HighTask) { // ==> Comportement 

	if (compteur == 0){
		actual_mode = (actual_mode + 1) % 2;
	}

	display_goto_xy(0, 0);	

	if (buf_what_mode[actual_mode % 2]) {
	
		display_clear(1);
		display_goto_xy(1, 6);
		display_string("J'avance");	
		
	} else {
	
		display_clear(1);
		display_goto_xy(1, 3);	
		display_string("-- Obstacle --");
		display_goto_xy(1, 7);
		display_string("Je tourne !");
	
	}
	
	display_update();
	
	//Valeur des capteurs
	display_goto_xy(0, 4);
	display_int(calib(ecrobot_get_light_sensor(PORT_C_GAUCHE),noir_gauche, blanc_gauche), 3);

	display_goto_xy(0, 5);
	display_int(calib(ecrobot_get_light_sensor(PORT_C_DROITE),noir_droite, blanc_droite), 3);
	display_update();

	comportement_I_Cg(calib(ecrobot_get_light_sensor(PORT_C_GAUCHE),noir_gauche, blanc_gauche));
	comportement_I_Cd(calib(ecrobot_get_light_sensor(PORT_C_DROITE),noir_droite, blanc_droite));
	comportement_I_mode(buf_what_mode[actual_mode % 2]);

	comportement_step();

	compteur = (compteur + 1) % MULT ;
	TerminateTask();
}

void comportement_O_u_d(_real vit) {

	int vit_int = (int) (vit * 100);

	if (vit_int > VMAX) {
		vit_int = VMAX;
	}
	if (vit_int < -VMAX) {
		vit_int = -VMAX;
	}

	display_goto_xy(0, 1);	
	display_int(vit_int, 3);
	display_update();

	ecrobot_set_motor_speed(NXT_PORT_A, vit_int);
}

void comportement_O_u_g(_real vit) {
	
	int vit_int = (int) (vit * 100);

	if (vit_int > VMAX) {
		vit_int = VMAX;
	}
	if (vit_int < -VMAX) {
		vit_int = -VMAX;
	}

	display_goto_xy(0, 2);	
	display_int(vit_int, 3);
	display_update();

	ecrobot_set_motor_speed(NXT_PORT_B, vit_int);
}

void what_mode_O_Mode(_boolean mode) {
	buf_what_mode[(actual_mode + 1) % 2] = mode;
}
