/********
* ec2c version 0.67
* c file generated for node : comportement 
* context   method = STATIC
* ext call  method = PROCEDURES
********/
/* This program needs external declarations */
#define _comportement_EC2C_SRC_FILE
#include "comportement.h"
/*--------
 * the following ``constants'' must be defined:
extern _real pi;
extern _real kp_teta;
extern _real ki_teta;
--------*/
/*--------
Internal structure for the call
--------*/
typedef struct  {
   
   //INPUTS
   _real _Cg;
   _real _Cd;
   _boolean _mode;
   //OUTPUTS
   _real _u_d;
   _real _u_g;
   //REGISTERS
   _real M24;
   _boolean M24_nil;
   _boolean M21;
} comportement_ctx;

// Single Static Context
static comportement_ctx ctx;
/*--------
Output procedures must be defined,
Input procedures must be used:
--------*/
void comportement_I_Cg(_real V){
   ctx._Cg = V;
}
void comportement_I_Cd(_real V){
   ctx._Cd = V;
}
void comportement_I_mode(_boolean V){
   ctx._mode = V;
}
extern void comportement_O_u_d(_real);
extern void comportement_O_u_g(_real);
#ifdef CKCHECK
extern void comportement_BOT_u_d();
extern void comportement_BOT_u_g();
#endif
/*--------
Internal reset input procedure
--------*/
static void comportement_reset_input(){
   //NOTHING FOR THIS VERSION...
}
/*--------
Reset procedure
--------*/
void comportement_reset(){
   ctx.M24_nil = _true;
   ctx.M21 = _true;
   comportement_reset_input();
}
/*--------
Step procedure
--------*/
void comportement_step(){
//LOCAL VARIABLES
   _real L5;
   _real L16;
   _real L19;
   _real L15;
   _real L13;
   _real L20;
   _real L12;
   _real L10;
   _real L25;
   _real L9;
   _real L32;
   _boolean L31;
   _real L33;
   _real L30;
   _real L29;
   _real L36;
   _real L34;
   _real L28;
   _real L27;
   _real L8;
   _real L4;
   _real L38;
   _real L37;
   _real L3;
   _real L44;
   _real L43;
   _real L42;
   _real L41;
   _real T24;
//CODE
   L5 = (1.000000 / 2.000000);
   L16 = (pi / 200.000000);
   L19 = (ctx._Cd - ctx._Cg);
   L15 = (L16 * L19);
   L13 = (0.002000 * L15);
   if (ctx.M21) {
      L20 = 0.000000;
   } else {
      L20 = ctx.M24;
   }
   L12 = (L13 + L20);
   L10 = (ki_teta * L12);
   L25 = (kp_teta * L15);
   L9 = (L10 + L25);
   L32 = (2.000000 * L9);
   L31 = (L32 < 0.000000);
   L33 = (- L32);
   if (L31) {
      L30 = L33;
   } else {
      L30 = L32;
   }
   L29 = (- L30);
   L36 = (ctx._Cd + ctx._Cg);
   L34 = (0.005000 * L36);
   L28 = (L29 + L34);
   L27 = (2.000000 * L28);
   L8 = (L9 + L27);
   L4 = (L5 * L8);
   L38 = (- 1.000000);
   L37 = (L38 * 0.400000);
   if (ctx._mode) {
      L3 = L4;
   } else {
      L3 = L37;
   }
   comportement_O_u_d(L3);
   L44 = (- L9);
   L43 = (L44 + L27);
   L42 = (L5 * L43);
   if (ctx._mode) {
      L41 = L42;
   } else {
      L41 = 0.400000;
   }
   comportement_O_u_g(L41);
   T24 = L12;
   ctx.M24 = T24;
   ctx.M24_nil = _false;
   ctx.M21 = ctx.M21 && !(_true);
}
