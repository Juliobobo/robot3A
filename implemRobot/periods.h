
//----------------------------
//User real-time parameters
//----------------------------

#define HighTask_OFFSET  1    //starts immediately
#define HighTask_PERIOD  10 //called every 1 second

#define MULT 3

#define LowTask_OFFSET  1   //starts immediately
#define LowTask_PERIOD  HighTask_PERIOD * MULT //called every 3 second
