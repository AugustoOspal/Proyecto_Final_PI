#include "helpers.h"
#include "htmlTable.h"

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
    FILE *fileCSV = fopen("querry1.csv", "w");
    htmlTable table =  newTable("query1.html", 2, "infraction", "tickets");

    checkFile(fileCSV);
    if (!table)
    {
        // Todo: mensaje de error
    }

    fprintf(fileCSV, "%s\n", HEADER_LINE_QUERRY1);

    // This one already checks if the system or infractions is empty
    if (!sortInfractions(system))
    {
        // Todo: mensaje de error
    }

    infractionToBegining(system);

    while (hasNextInfraction(system))
    {
        size_t qty = getQtyTickets(system);
        char *name = getInfractionName(system);

        addHTMLRow(table, name, qty);
        fprintf(fileCSV, "%s;%lu\n", name, qty);
        setNextInfraction(system);

        free(name);
    }

    closeHTMLTable(table);
    fclose(fileCSV);
}

void loadQuery2(infractionSystemADT system)
{
    FILE *fileCSV = fopen("querry2.csv", "w");
    htmlTable table = newTable("query2.html", 3, "issuingAgency", "infraction", "tickets");

    checkFile(fileCSV);
    if (!table)
    {
        // Todo: mensaje de error
    }

    fprintf(fileCSV, "%s\n", HEADER_LINE_QUERRY2);

    if (!agencyToBegining(system))
    {
        // Todo: mensaje de error
    }

    while (hasNextAgency(system))
    {
        size_t qty;
        char *agency = getAgencyName(system);
        char *infraction = getMostPopularInfractionForAgency(system, &qty);

        setNextAgency(system);
        addHTMLRow(table, agency, infraction, qty);
        fprintf(fileCSV, "%s;%s;%lu\n", agency, infraction, qty);

        free(agency);
        free(infraction);
    }

    closeHTMLTable(table);
    fclose(fileCSV);
}

void loadQuery3(infractionSystemADT system)
{
    FILE *file = fopen("querry3.csv", "w");
    htmlTable table = newTable("query3.html", 3, "infraction", "plate", "tickets");

    checkFile(file);
    if (!table)
    {
        // Todo: mensaje de error
    }

    fprintf(file, "%s\n", HEADER_LINE_QUERRY3);

    if (!infractionToBegining(system))
    {
        // Todo: mensaje de error
    }

    while (hasNextInfraction(system))
    {
        size_t qty;
        char *name = getInfractionName(system);
        char *plate = getPlateWithTheMostInfractions(system, &qty);
        if (plate && name)
        {
            addHTMLRow(table, name, plate, qty);
            fprintf(file, "%s;%s;%lu\n", getInfractionName(system), plate, qty);
            free(plate);
            free(name);
        }
        setNextInfraction(system);
    }

    closeHTMLTable(table);
    fclose(file);
}
