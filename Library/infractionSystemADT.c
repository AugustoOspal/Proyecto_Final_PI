#include "infractionSystemADT.h"

typedef struct car
{
    char *plate;
    size_t counter;
    struct car *next;
}car;

typedef struct infraction
{
    size_t id;
    size_t qty;
    char *name;
    car *carList;
    car *biggest;
}infraction;

typedef struct agency
{
    char *name;
    size_t len;
    size_t qtyTickets;
    size_t *tickets;
    size_t *counterPerInfraction;
    struct agency *next;
}agency;

typedef struct ticket
{
    char *plate;
    char *date;
    char *agency;
    size_t fine;
    size_t infractionID;
    size_t index;
}ticket;

typedef struct infractionSystemCDT
{
    infraction *infractions;
    ticket *tickets;
    agency *agencyList;
    size_t qtyInfractions;
    size_t qtyTickets;
    size_t qyuAgencies;
}infractionSystemCDT;

