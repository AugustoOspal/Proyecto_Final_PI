#ifndef PROYECTO_FINAL_PI_TICKETSADT_H
#define PROYECTO_FINAL_PI_TICKETSADT_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct infractionSystemCDT * infractionSystemADT;


infractionSystemADT makeNewInfractionSystem(void);

int loadTickets(infractionSystemADT system, FILE *ticketsFile, ticketMap map);

int loadInfractions(infractionSystemADT system, FILE *infractions, infractionMap map);

void freeInfractionSystem(infractionSystemADT system);


void addTicket(infractionSystemADT city, char * date, char * plate, char * agency, size_t fine, size_t id);

void addAgency(infractionSystemADT system, char * agency, size_t idx);

void addInfraction(infractionSystemADT system, char * plate, size_t id);

#endif //PROYECTO_FINAL_PI_TICKETSADT_H
