#ifndef PROYECTO_FINAL_PI_TICKETSADT_H
#define PROYECTO_FINAL_PI_TICKETSADT_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 500
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

/*
 * Returns the quantity of tickets loaded
 */
size_t loadTickets(infractionSystemADT system, FILE *ticketsFile, ticketMap map);

/*
 * Returns the qty of infractions loaded
 */
size_t loadInfractions(infractionSystemADT system, FILE *infractions, infractionMap map);

/*
 * Sorts the infractions in the system by the quantity of tickets
 * and if two tickets have the same quantity, it sorts them by the infraction name.
 * If the system or infractions is empty, it returns 0
 */
int sortInfractions(infractionSystemADT system);

int hasNextInfraction(infractionSystemADT system);

// If system or infraction is empty, it returns 0
int infractionToBegining(infractionSystemADT system);

/*
 * If it was already in the last one it doesn't do anything
 * If the system or infractions is empty, it returns 0
*/
int setNextInfraction(infractionSystemADT system);

// Returns a copy of the infraction name, so it must be freed after use
char *getInfractionName(infractionSystemADT system);

size_t getInfractionID(infractionSystemADT system);

/*
 * Returns the quantity of infractions for the current infraction
 * If there are no infractions, it returns 0
 */
size_t getInfractionQty(infractionSystemADT system);

/*
 * Returns the plate with the most counter for this infraction and leaves the quantity in the pointer.
 * It returns a copy of the plate, so it must be freed after use
 * If there are no infractions, it returns NULL ant sets the quantity to 0
*/
char *getPlateWithTheMostInfractions(infractionSystemADT system, size_t *qty);

// If there are no agencies, it returns 0 else 1
int agencyToBegining(infractionSystemADT system);

int hasNextAgency(infractionSystemADT system);

// If it was already in the last one it doesn't do anything
void setNextAgency(infractionSystemADT system);

/*
 * Returns a copy of the agency name, so it must be freed after use
 * If there are no agencies or no system, it returns NULL
 */
char *getAgencyName(infractionSystemADT system);

/*
 * Returns the most popular infraction for the agency that is currently being processed.
 * It returns a copy of the infraction name, so it must be freed after use.
 * If there are no infractions, it returns NULL and sets the quantity to 0.
*/
char * getMostPopularInfractionForAgency(infractionSystemADT system, size_t *qty);

size_t getQtyTickets(infractionSystemADT system);

size_t getQtyInfractions(infractionSystemADT system);

void freeInfractionSystem(infractionSystemADT system);

#endif //PROYECTO_FINAL_PI_TICKETSADT_H
