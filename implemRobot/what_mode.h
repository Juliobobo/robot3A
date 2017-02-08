/********
* ec2c version 0.67
* context   method = STATIC
* ext call  method = PROCEDURES
* c header file generated for node : what_mode 
* to be used with : what_mode.c 
********/
#ifndef _what_mode_EC2C_H_FILE
#define _what_mode_EC2C_H_FILE
/* This program needs external declarations */
#include "what_mode_ext.h"
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
//MODULE: what_mode 2 1
//IN: _real Cd
//IN: _real distance
//OUT: _boolean Mode
#ifndef _what_mode_EC2C_SRC_FILE
/*-------- Input procedures -------------*/
extern void what_mode_I_Cd(_real);
extern void what_mode_I_distance(_real);
/*-------- Reset procedure -----------*/
extern void what_mode_reset();
/*--------Context init = context reset --------*/
#define what_mode_init what_mode_reset
/*-------- Step procedure -----------*/
extern void what_mode_step();
#endif
#endif
