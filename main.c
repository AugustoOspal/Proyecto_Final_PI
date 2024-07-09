#include "main.h"
#include "Library/helpers.h"
#include "Library/infractionSystemADT.h"

int main(int argc, char *argv[])
{
    // BORRAR DESPUES!!!!!!!!
//    argv[1] = "../DataSets/ticketsNYC15000000.csv";
//    argv[2] = "../DataSets/infractionsNYC.csv";

    validateCommandLine(argc);
    validateFiles(argc, argv);

#if defined(NYC)
    ticketMap mapTicket = {0, 1, 4, 3, 2, 5};
    infractionMap mapInfraction = {0, 1, 2};
#elif defined(CHI)
    ticketMap mapTicket = {1, 0, 2, 4, 3, 5};
    infractionMap mapInfraction = {0, 1, 2};
#else
    puts(ERROR_INVALID_CITY_CODE_M);
    return ERROR_INVALID_CITY_CODE;
#endif

    FILE *tickets = fopen(argv[1], "r");
    FILE *infractions = fopen(argv[2], "r");

    infractionSystemADT city = makeNewInfractionSystem();
    loadInfractions(city, infractions, mapInfraction);
    loadTickets(city, tickets, mapTicket);



    freeInfractionSystem(city);

    fclose(tickets);
    fclose(infractions);
    puts("OK!");
}

