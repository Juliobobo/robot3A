/********
* ec2c version 0.67
* context   method = STATIC
* ext call  method = PROCEDURES
* c header file generated for node : comportement 
* to be used with : comportement.c 
********/
#ifndef _comportement_EC2C_H_FILE
#define _comportement_EC2C_H_FILE
/* This program needs external declarations */
#include "comportement_ext.h"
/*-------- Predefined types ---------*/
#ifndef _EC2C_PREDEF_TYPES
#define _EC2C_PREDEF_TYPES
typedef int _boolean;
typedef int _integer;
typedef char* _string;
typedef double _real;
typedef double _double;
typedef float _float;
#define _false 0
#define _true 1
#endif
/*--------- Pragmas ----------------*/
//MODULE: comportement 3 2
//IN: _real Cg
//IN: _real Cd
//IN: _boolean mode
//OUT: _real u_d
//OUT: _real u_g
#ifndef _comportement_EC2C_SRC_FILE
/*-------- Input procedures -------------*/
extern void comportement_I_Cg(_real);
extern void comportement_I_Cd(_real);
extern void comportement_I_mode(_boolean);
/*-------- Reset procedure -----------*/
extern void comportement_reset();
/*--------Context init = context reset --------*/
#define comportement_init comportement_reset
/*-------- Step procedure -----------*/
extern void comportement_step();
#endif
#endif
