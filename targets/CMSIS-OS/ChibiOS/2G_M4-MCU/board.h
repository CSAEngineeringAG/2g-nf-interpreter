// use board definition file of hardware version 1 if USE_M4MCU_V3 is not defined

#ifdef USE_M4MCU_V3
#include "board-v3.h"
#else
#include "board-v1.h"
#endif