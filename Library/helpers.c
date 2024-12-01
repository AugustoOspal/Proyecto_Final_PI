#include "helpers.h"
#include "htmlTable.h"

static void checkMemory(void *pointer)
{
    if (!pointer || errno == ENOMEM)
    {
        puts(ERROR_ALLOCATING_MEMORY_M);
        exit(ERROR_ALLOCATING_MEMORY);
    }
}

char *size_tToString(size_t num)
{
    int digits = (num == 0);
    size_t aux = num;

    while(aux > 0)
    {
        digits++;
        aux /= 10;
    }

    errno = 0;
    char * out = malloc((digits + 1) * sizeof(char));
    checkMemory(out);

    for(int i = (digits - 1); i >= 0; i--)
    {
        out[i] = num % 10 + '0';
        num /= 10;
    }

    out[digits] = 0;
    return out;
}

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
        fprintf(stderr, "%s\n", ERROR_NUMBER_INPUT_FILES_M);
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
    fprintf(fileCSV, "%s\n", HEADER_LINE_QUERRY1);

    // This one already checks if the system or infractions is empty
    sortInfractions(system);
    infractionToBegining(system);

    while (hasNextInfraction(system))
    {
        size_t qty = getInfractionQty(system);

        char *qtyS = size_tToString(qty);
        char *name = getInfractionName(system);

        addHTMLRow(table, name, qtyS);
        fprintf(fileCSV, "%s;%lu\n", name, qty);
        setNextInfraction(system);

        free(name);
        free(qtyS);
    }

    closeHTMLTable(table);
    fclose(fileCSV);
}

void loadQuery2(infractionSystemADT system)
{
    FILE *fileCSV = fopen("querry2.csv", "w");
    htmlTable table = newTable("query2.html", 3, "issuingAgency", "infraction", "tickets");

    checkFile(fileCSV);
    fprintf(fileCSV, "%s\n", HEADER_LINE_QUERRY2);

    agencyToBegining(system);
    while (hasNextAgency(system))
    {
        size_t qty;
        char *agency = getAgencyName(system);
        char *infraction = getMostPopularInfractionForAgency(system, &qty);
        char *qtyS = size_tToString(qty);

        setNextAgency(system);
        addHTMLRow(table, agency, infraction, qtyS);
        fprintf(fileCSV, "%s;%s;%lu\n", agency, infraction, qty);

        free(agency);
        free(infraction);
        free(qtyS);
    }

    closeHTMLTable(table);
    fclose(fileCSV);
}

void loadQuery3(infractionSystemADT system)
{
    FILE *file = fopen("querry3.csv", "w");
    htmlTable table = newTable("query3.html", 3, "infraction", "plate", "tickets");

    checkFile(file);
    fprintf(file, "%s\n", HEADER_LINE_QUERRY3);

    infractionToBegining(system);
    while (hasNextInfraction(system))
    {
        size_t qty;
        char *name = getInfractionName(system);
        char *plate = getPlateWithTheMostInfractions(system, &qty);
        char *qtyS = size_tToString(qty);
        if (plate && name)
        {
            addHTMLRow(table, name, plate, qtyS);
            fprintf(file, "%s;%s;%lu\n", name, plate, qty);
        }

        free(plate);
        free(name);
        free(qtyS);

        setNextInfraction(system);
    }

    closeHTMLTable(table);
    fclose(file);
}
