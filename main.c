#include "main.h"
#include "Library/helpers.h"
#include "Library/infractionSystemADT.h"

int main(int argc, char *argv[])
{
    // BORRAR DESPUES!!!!!!!!
    argv[1] = "../DataSets/ticketsNYC.csv";
    argv[2] = "../DataSets/infractionsNYC.csv";

    validateCommandLine(argc);
    validateFiles(argc, argv);

    /*
     * This part maps the fields of the tickets and infractions to match the correct fields
     * of the CSV files. It's important to note that the fields are 0-indexed.
     * It's mandatory to map the fields in order to load the data correctly.
     */
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

    loadQuery1(city);
    loadQuery2(city);
    loadQuery3(city);

    freeInfractionSystem(city);

    fclose(tickets);
    fclose(infractions);
    puts("OK!");
}
