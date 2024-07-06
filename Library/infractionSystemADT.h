#ifndef PROYECTO_FINAL_PI_TICKETSADT_H
#define PROYECTO_FINAL_PI_TICKETSADT_H

#include <stddef.h>

typedef struct infractionSystemCDT *infractionSystemADT;

infractionSystemADT makeNewInfractionSystem(void);

void freeInfractionSystem(infractionSystemADT system);

#endif //PROYECTO_FINAL_PI_TICKETSADT_H
