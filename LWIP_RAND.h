#ifndef LWIP_RAND
#include "pico/rand.h"
// Use the pico_rand library which goes to reasonable lengths to try to provide good entropy
#define LWIP_RAND() get_rand_32()
#endif