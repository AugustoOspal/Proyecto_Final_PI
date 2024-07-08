#include "infractionSystemADT.h"

// ERROR CODES
#define ERROR_ALLOCATING_MEMORY 1
#define ERROR_repeatInfraction 4

#define ERROR_ALLOCATING_MEMORY_M "Memory allocation error"

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

typedef struct infractionNode
{
    size_t id;
    size_t qty;
    char *name;
    car *carList;
    car *biggest;
    struct infractionNode *tail;
}infractionNode;

typedef struct infractionNode *infractionList;

/* Auxiliary Functions */

static void checkMemory(void *pointer)
{
    if (!pointer)
    {
        puts(ERROR_ALLOCATING_MEMORY_M);
        exit(ERROR_ALLOCATING_MEMORY);
    }
}

static char * copyString(char *string)
{
    char *newString = NULL;
    size_t dim = 0, counter;
    for (counter = 0; string[counter]; counter++)
    {
        if (counter % BLOCK == 0)
        {
            dim += BLOCK;
            newString = realloc(newString, dim * sizeof(char));
            checkMemory(newString);
        }

        newString[counter] = string[counter];
    }
    newString[counter] = 0;
    return newString;
}

static char ** sectionString(char *string, char *delimiters, size_t *dimVec)
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
            checkMemory(tokens);
        }

        counter++;
        tokens[i] = token;
        token = strtok(NULL, delimiters);
    }

    *dimVec = counter;
    tokens = realloc(tokens, counter * sizeof(char *));
    return tokens;
}

static void freeInfractionsList(infractionList list)
{
    if (list)
    {
        freeInfractionsList(list->tail);
        free(list);
    }
}

static infractionList loadInfraction(infractionList infractionL, size_t id, char *name)
{
    if (!infractionL || id < infractionL->id)
    {
        //Make new node and initialize it
        infractionNode *newNode = malloc(sizeof(infractionNode));
        checkMemory(newNode);

        newNode->id = id;
        newNode->name = copyString(name);
        newNode->biggest = NULL;
        newNode->carList = NULL;
        newNode->qty = 0;
        newNode->tail = infractionL;
        return newNode;
    }

    if (id == infractionL->id && strcmp(name, infractionL->name) == 0)
    {
        puts("Repeated infraction in the file");
        exit(4);
    }

    infractionL->tail = loadInfraction(infractionL->tail, id, name);
    return infractionL;
}

/* end of auxiliary functions */

infractionSystemADT makeNewInfractionSystem(void)
{
    infractionSystemADT newSystem = calloc(1, sizeof(infractionSystemCDT));
    return newSystem;
}

// The file must be open in read
// IMPORTANT: this function must be called before loadTickets
int loadInfractions(infractionSystemADT system, FILE *infractions, infractionMap map)
{
    if (!system)
    {
        puts("Invalid system");
        exit(3);
    }

    size_t qtyTokens, counter = 0;
    char buffer[BUFFER_SIZE], **tokens;

    infractionList infractionsL = NULL;

    // Skips the first line
    fgets(buffer, BUFFER_SIZE, infractions);
    while (fgets(buffer, BUFFER_SIZE, infractions))
    {
        tokens = sectionString(buffer, DELIMITER, &qtyTokens);
        infractionsL = loadInfraction(infractionsL, atoi(tokens[map.id]), tokens[map.infractionName]);
        counter++;

        free(tokens);
    }

    infraction *infractionVec = malloc(sizeof(infraction) * counter);
    checkMemory(infractionVec);

    infractionList aux = infractionsL;
    for (size_t i = 0; i < counter; i++)
    {
        infractionVec[i].id = infractionsL->id;
        infractionVec[i].name = infractionsL->name;
        infractionVec[i].qty = 0;
        infractionVec[i].carList = NULL;
        infractionVec[i].biggest = NULL;
        infractionsL = infractionsL->tail;
    }

    freeInfractionsList(aux);

    system->qtyInfractions = counter;
    system->infractions = infractionVec;
    return counter;
}

void freeInfractionSystem(infractionSystemADT system)
{
    for (size_t i = 0; i < system->qtyInfractions; i++)
    {
        free(system->infractions[i].name);
    }
    free(system->infractions);
    free(system);
}
