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

char * copyString(char *string)
{
    // Todo: ver lo del error

    char *newString = NULL;
    size_t dim = 0, counter;
    for (counter = 0; string[counter]; counter++)
    {
        if (counter % BLOCK == 0)
        {
            dim += BLOCK;
            newString = realloc(newString, dim * sizeof(char));
        }

        newString[counter] = string[counter];
    }
    newString[counter] = 0;
    return newString;
}

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

void printInfractions(infractionSystemADT system)
{
    for (size_t i = 0; i < system->qtyInfractions; i++)
    {
        printf("%ld, %s\n", system->infractions[i].id, system->infractions[i].name);
    }
}

void printList(infractionList list)
{
    if (!list)
        return;
    printf("%ld, %s\n", list->id, list->name);
    printList(list->tail);
}

void freeInfractionsList(infractionList list)
{
    if (!list)
        return;
    freeInfractionsList(list->tail);
    free(list->name);
    free(list);
}

/* end of auxiliary functions */

infractionSystemADT makeNewInfractionSystem(void)
{
    infractionSystemADT newSystem = calloc(1, sizeof(infractionSystemCDT));
    return newSystem;
}

static infractionList loadInfraction(infractionList infractionL, size_t id, char *name)
{
    if (!infractionL || id < infractionL->id)
    {
        //Make new node and initialize it
        infractionNode *newNode = malloc(sizeof(infractionNode));

        // Todo: aca hacer algo si no se hace el malloc

        newNode->id = id;
        newNode->name = copyString(name);
        newNode->biggest = NULL;
        newNode->carList = NULL;
        newNode->qty = 0;
        newNode->tail = infractionL;
        return newNode;
    }

    if (id == infractionL->id)
    {
        // Todo: aca tendria que dar error porque no puede pasar
        return infractionL;
    }

    infractionL->tail = loadInfraction(infractionL->tail, id, name);
    return infractionL;
}

// The file must be open in read
// IMPORTANT: this function must be called before loadTickets
int loadInfractions(infractionSystemADT system, FILE *infractions, infractionMap map)
{
    // Todo: Aca tendria que dar error
    if (!system)
    {
        return 0;
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
    }

    infraction *infractionVec = malloc(sizeof(infraction) * counter);
    // Todo: Aca tendria que dar error si es NULL

    for (size_t i = 0; i < counter; i++)
    {
        infractionVec[i].id = infractionsL->id;
        infractionVec[i].name = infractionsL->name;
        infractionVec[i].qty = 0;
        infractionVec[i].carList = NULL;
        infractionVec[i].biggest = NULL;
        infractionsL = infractionsL->tail;
    }

    free(tokens);
    freeInfractionsList(infractionsL);

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
