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

typedef struct infractionsCDT * infractionsADT;

infractionSystemADT makeNewInfractionSystem(void);

int loadTickets(infractionSystemADT system, FILE *ticketsFile, ticketMap map);

int loadInfractions(infractionSystemADT system, FILE *infractions, infractionMap map);

int hasNextInfraction(infractionSystemADT system);

void infractionToBegining(infractionSystemADT system);

void setNextInfraction(infractionSystemADT system);

// Returns a copy of the infraction name, so it must be freed after use
char *getInfractionName(infractionSystemADT system);

size_t getInfractionID(infractionSystemADT system);

size_t getInfractionQty(infractionSystemADT system);

/*
 * Returns the plate with the most counter for this infraction and leaves the quantity in the pointer.
 * It returns a copy of the plate, so it must be freed after use
 * If there are no infractions, it returns NULL ant sets the quantity to 0
*/
char *getPlateWithTheMostInfractions(infractionSystemADT system, size_t *qty);


void agencyToBegining(infractionSystemADT system);

int hasNextAgency(infractionSystemADT system);

// If it was already in the last one it doesn't do anything
void setNextAgency(infractionSystemADT system);

/*
 * Returns a copy of the agency name, so it must be freed after use
 * If there are no agencies or no system, it returns NULL
 */
char *getAgencyName(infractionSystemADT system);

/*
 * Returns the most popular infraction for the agency that is currently being processed
 * If there are no infractions, it returns NULL and sets the quantity to 0
*/
size_t getMostPopularInfractionForAgency(infractionSystemADT system, size_t *qty);

size_t getQtyTickets(infractionSystemADT system);

size_t getQtyInfractions(infractionSystemADT system);

void freeInfractionSystem(infractionSystemADT system);

#endif //PROYECTO_FINAL_PI_TICKETSADT_H
