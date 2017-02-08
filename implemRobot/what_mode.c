/********
* ec2c version 0.67
* c file generated for node : what_mode 
* context   method = STATIC
* ext call  method = PROCEDURES
********/
/* This program needs external declarations */
#define _what_mode_EC2C_SRC_FILE
#include "what_mode.h"
/*--------
 * the following ``constants'' must be defined:
extern _real distanceMin;
--------*/
/*--------
Internal structure for the call
--------*/
typedef struct  {
   
   //INPUTS
   _real _Cd;
   _real _distance;
   //OUTPUTS
   _boolean _Mode;
   //REGISTERS
   _boolean M35;
   _boolean M35_nil;
   _boolean M33;
   _boolean M33_nil;
   _boolean M12;
   _boolean M12_nil;
   _boolean M27;
   _boolean M27_nil;
   _boolean M22;
   _boolean M22_nil;
   _boolean M9;
} what_mode_ctx;

// Single Static Context
static what_mode_ctx ctx;
/*--------
Output procedures must be defined,
Input procedures must be used:
--------*/
void what_mode_I_Cd(_real V){
   ctx._Cd = V;
}
void what_mode_I_distance(_real V){
   ctx._distance = V;
}
extern void what_mode_O_Mode(_boolean);
#ifdef CKCHECK
extern void what_mode_BOT_Mode();
#endif
/*--------
Internal reset input procedure
--------*/
static void what_mode_reset_input(){
   //NOTHING FOR THIS VERSION...
}
/*--------
Reset procedure
--------*/
void what_mode_reset(){
   ctx.M35_nil = _true;
   ctx.M33_nil = _true;
   ctx.M12_nil = _true;
   ctx.M27_nil = _true;
   ctx.M22_nil = _true;
   ctx.M9 = _true;
   what_mode_reset_input();
}
/*--------
Step procedure
--------*/
void what_mode_step(){
//LOCAL VARIABLES
   _boolean L6;
   _boolean L8;
   _boolean L5;
   _boolean L32;
   _boolean L31;
   _boolean L4;
   _boolean L34;
   _boolean L3;
   _boolean L2;
   _boolean T35;
   _boolean T33;
   _boolean L17;
   _boolean L16;
   _boolean L21;
   _boolean L26;
   _boolean L25;
   _boolean L28;
   _boolean L24;
   _boolean L30;
   _boolean L29;
   _boolean L23;
   _boolean L20;
   _boolean L19;
   _boolean L15;
   _boolean L14;
   _boolean L13;
   _boolean T12;
   _boolean T27;
   _boolean T22;
//CODE
   L6 = (ctx._distance < distanceMin);
   if (ctx.M9) {
      L8 = _false;
   } else {
      L8 = ctx.M12;
   }
   L5 = (L6 || L8);
   if (ctx.M9) {
      L32 = _false;
   } else {
      L32 = ctx.M33;
   }
   L31 = (! L32);
   L4 = (L5 && L31);
   if (ctx.M9) {
      L34 = _false;
   } else {
      L34 = ctx.M35;
   }
   L3 = (L4 != L34);
   L2 = (! L3);
   what_mode_O_Mode(L2);
   T35 = L3;
   T33 = L5;
   L17 = (ctx._Cd > 50.000000);
   L16 = (L17 && L3);
   if (ctx.M9) {
      L21 = _false;
   } else {
      L21 = ctx.M22;
   }
   if (ctx.M9) {
      L26 = _false;
   } else {
      L26 = ctx.M27;
   }
   L25 = (L26 || L16);
   L28 = (! L8);
   L24 = (L25 && L28);
   L30 = (ctx._Cd < 50.000000);
   L29 = (L30 && L3);
   L23 = (L24 && L29);
   L20 = (L21 || L23);
   L19 = (L20 && L28);
   L15 = (L16 && L19);
   L14 = (L8 || L15);
   L13 = (L14 && L28);
   T12 = L13;
   T27 = L24;
   T22 = L19;
   ctx.M35 = T35;
   ctx.M35_nil = _false;
   ctx.M33 = T33;
   ctx.M33_nil = _false;
   ctx.M12 = T12;
   ctx.M12_nil = _false;
   ctx.M27 = T27;
   ctx.M27_nil = _false;
   ctx.M22 = T22;
   ctx.M22_nil = _false;
   ctx.M9 = ctx.M9 && !(_true);
}
