#include "main.h"
#include "Library/helpers.h"
#include "infractionSystemADT.h"

int main(int argc, char *argv[])
{
    validateCommandLine(argc);
    validateFiles(argc, argv);

#if defined(NYC)
    ticketMap mapTicket = {0, 1, 4, 3, 2};
    infractionsMap mapInfraction = {0, 1};
#elif defined(CHI)
    ticketMap mapTicket = {1, 0, 2, 4, 3};
    infractionsMap mapInfraction = {0, 1};
#else
    puts(ERROR_INVALID_CITY_CODE_M);
    return ERROR_INVALID_CITY_CODE;
#endif

    FILE *tickets = fopen(argv[1], "r");
    FILE *infractions = fopen(argv[2], "r");

    infractionSystemADT city = makeNewInfractionSystem(void);
    loadInfractions(city, infractions, mapInfraction);
    loadTickets(city, tickets, mapTicket);

}