#ifndef PROYECTO_FINAL_PI_TICKETSADT_H
#define PROYECTO_FINAL_PI_TICKETSADT_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define FIELDS 2
#define BUFFER_SIZE 255
#define DELIMITER ";\n\r"

typedef struct ticketMap
{
    size_t plate;
    size_t date;
    size_t agency;
    size_t fine;
    size_t infractionID;
    size_t fields;
}ticketMap;

typedef struct infractionMap
{
    size_t id;
    size_t infractionName;
    size_t fields;
}infractionMap;

typedef struct infractionSystemCDT *infractionSystemADT;

infractionSystemADT makeNewInfractionSystem(void);

int loadTickets(infractionSystemADT system, FILE *tickets, FILE *infractions);

int loadInfractions(infractionSystemADT system, FILE *infractions, infractionMap map);

void freeInfractionSystem(infractionSystemADT system);


/* Auxiliary functions */

char * getLine();

/*
 * Splits string in tokens separated by the characters
 * in the string delimiters
 */
char ** sectionString(char *string, char *delimiters, size_t *dimVec);




#endif //PROYECTO_FINAL_PI_TICKETSADT_H
