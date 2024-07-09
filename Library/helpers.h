#ifndef PROYECTO_FINAL_PI_HELPERS_H
#define PROYECTO_FINAL_PI_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main.h"
#include "../Library/infractionSystemADT.h"

void validateCommandLine(int argc);
void validateFiles(int argc, char *argv[]);

char ** splitString(const char * string, const char token);

#endif //PROYECTO_FINAL_PI_HELPERS_H
