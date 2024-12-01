#ifndef PROYECTO_FINAL_PI_HELPERS_H
#define PROYECTO_FINAL_PI_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main.h"
#include "../Library/infractionSystemADT.h"

#define HEADER_LINE_QUERRY1 "infraction;tickets"
#define HEADER_LINE_QUERRY2 "issuingAgency;infraction;tickets"
#define HEADER_LINE_QUERRY3 "infraction;plate;tickets"

int checkFile(FILE *file);

void validateCommandLine(int argc);
void validateFiles(int argc, char *argv[]);

void loadQuery1(infractionSystemADT system);
void loadQuery2(infractionSystemADT system);
void loadQuery3(infractionSystemADT system);


#endif //PROYECTO_FINAL_PI_HELPERS_H
