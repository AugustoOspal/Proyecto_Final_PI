#include "main.h"
#include "Library/helpers.h"
#include "infractionSystemADT.h"

int main(int argc, char *argv[])
{
    validateCommandLine(argc);
    validateFiles(argc, argv);

#if defined(NYC)
    ticketMap map = {0, 1, 4, 3, 2};
#elif defined(CHI)
    ticketMap map = {1, 0, 2, 4, 3};
#else
    puts(ERROR_INVALID_CITY_CODE_M);
    return ERROR_INVALID_CITY_CODE;
#endif

    infractionSystemADT city = makeNewInfractionSystem(void);
    loadTickets(city, argv[1], argv[2]);

    //Testing
    FILE *file = fopen(argv[1], "r");
    char buffer[2000] = {0};
    printf("%s", fgets(buffer, 2000, file));
}