#include "infractionSystemADT.h"

#define BLOCK 50

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


infractionSystemADT makeNewInfractionSystem(void)
{
    infractionSystemADT newSystem = calloc(1, sizeof(infractionSystemCDT));
    return newSystem;
}

// The file must be open in read
int loadInfractions(infractionSystemADT system, FILE *infractions, infractionMap map)
{
    // Todo: Aca tendria que dar error
    if (!system)
    {
        return 0;
    }

    size_t dim;
    char **tokens;
    char buffer[BUFFER_SIZE];

    // Skips the first line
    fgets(buffer, BUFFER_SIZE, infractions);
    while (fgets(buffer, BUFFER_SIZE, infractions))
    {
        tokens = sectionString(buffer, DELIMITER, &dim);
        // Aca va load ticket

    }

    return 1;
}

/*
 * Auxiliary functions
 */

char ** sectionString(char *string, char *delimiters, size_t *dimVec)
{
    size_t counter = 0, dim = 0;

    char *token, **tokens = NULL;

    token = strtok(string, delimiters);
    for (size_t i = 0; token; i++)
    {
        if (counter % BLOCK == 0)
        {
            dim += BLOCK;
            tokens = realloc(tokens, dim * sizeof(char *));

            // Todo: Si aca es NULL tiene que dar ERROR
        }

        counter++;
        tokens[i] = token;
        token = strtok(NULL, delimiters);
    }

    *dimVec = counter;
    tokens = realloc(tokens, counter * sizeof(char *));
    return tokens;
}

