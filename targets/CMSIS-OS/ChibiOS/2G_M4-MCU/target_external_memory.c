// switch external memory definitions depending on the hardware version

#ifdef USE_M4MCU_V3
#include "target_external_memory_v3.c"
#else
#include "target_external_memory_v1.c"
#endif