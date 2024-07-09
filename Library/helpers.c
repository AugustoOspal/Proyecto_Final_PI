#include "helpers.h"

int checkFile(FILE *file)
{
    if (!file)
    {
        fclose(file);
        puts(ERROR_EMPTY_FILE_M);
        return ERROR_EMPTY_FILE;
    }

    return 0;
}

void validateCommandLine(int argc)
{
    if (argc != NUMBER_INPUT_FILES + 1)
    {
        puts(ERROR_NUMBER_INPUT_FILES_M);
        exit(ERROR_NUMBER_INPUT_FILES);
    }
}

void validateFiles(int argc, char *argv[])
{
    for (size_t i = 1; i < argc; i++)
    {
        FILE *file = fopen(argv[i], "r");
        checkFile(file);
        fclose(file);
    }
}

void loadQuery1(infractionSystemADT system)
{
    FILE *file = fopen("querry1.csv", "w");
    checkFile(file);

    fprintf(file, "%s\n", HEADER_LINE_QUERRY1);

    // This one already checks if the system or infractions is empty
    if (!sortInfractions(system))
    {
        // Todo: mensaje de error
    }

    infractionToBegining(system);

    while (hasNextInfraction(system))
    {
        fprintf(file, "%s;%lu\n", getInfractionName(system), getInfractionQty(system));
        setNextInfraction(system);
    }

    fclose(file);
}

void loadQuery2(infractionSystemADT system)
{
    FILE *file = fopen("querry2.csv", "w");
    checkFile(file);

    fprintf(file, "%s\n", HEADER_LINE_QUERRY2);

    if (!agencyToBegining(system))
    {
        // Todo: mensaje de error
    }

    while (hasNextAgency(system))
    {
        setNextAgency(system);
        fprintf(file, "%s;%s;%lu\n", getAgencyName(system), getInfractionName(system), getInfractionQty(system));
    }

    fclose(file);
}

void loadQuery3(infractionSystemADT system)
{
    FILE *file = fopen("querry3.csv", "w");
    checkFile(file);

    fprintf(file, "%s\n", HEADER_LINE_QUERRY3);

    if (!infractionToBegining(system))
    {
        // Todo: mensaje de error
    }

    while (hasNextInfraction(system))
    {
        setNextInfraction(system);
        size_t qty;
        char *plate = getPlateWithTheMostInfractions(system, &qty);
        if (plate)
        {
            fprintf(file, "%s;%s;%lu\n", getInfractionName(system), plate, qty);
            free(plate);
        }
    }

    fclose(file);
}
