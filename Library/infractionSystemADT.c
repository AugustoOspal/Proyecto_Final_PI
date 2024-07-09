#include "infractionSystemADT.h"
#include <stdlib.h>
#include <string.h>

#define BLOCK_IDX 255
#define INITIALS 5000
#define HASHSIZE 5000


// ERROR CODES
#define ERROR_ALLOCATING_MEMORY 1
#define ERROR_REPEATED_INFRACTION 2
#define ERROR_INVALID_SYSTEM 3
#define ERROR_INFRACTION_NOT_FOUND 4
#define ERROR_INVALID_NUMBER_FIELDS 5

#define ERROR_ALLOCATING_MEMORY_M "Memory allocation error"
#define ERROR_REPEATED_INFRACTION_M "Repeated infraction with different name"
#define ERROR_INVALID_SYSTEM_M "Invalid system"
#define ERROR_INFRACTION_NOT_FOUND_M "Infraction not found"
#define ERROR_INVALID_NUMBER_FIELDS_M "Invalid number of fields"

typedef struct car
{
    char *plate;
    size_t counter;
    struct car *next;
}car;

typedef struct car * carList;

typedef struct infraction
{
    size_t id;
    size_t qty;
    char *name;
    carList vec[INITIALS];
    car *biggest;
}infraction;

typedef struct infractionCounter
{
    size_t id;
    size_t counter;
    char *name;
}infractionCounter;


typedef struct agency
{
    char *name;
    size_t qtyTickets;
    infractionCounter *countInf;
    infractionCounter *max;
    struct agency *next;
}agency;

typedef struct agency * agencyList;

typedef struct infractionSystemCDT
{
    infraction * infractions;
    agency * agencyList;
    size_t qtyInfractions;
    size_t qtyTickets;
    size_t qtyAgencies;
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

static size_t hash(char *s)
{
    size_t hashval;
    for (hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + 31 * hashval;
    }

    return hashval % HASHSIZE;
}

static void checkMemory(void *pointer)
{
    if (!pointer)
    {
        puts(ERROR_ALLOCATING_MEMORY_M);
        exit(ERROR_ALLOCATING_MEMORY);
    }
}

static char * copyString(const char *string)
{
    char *newString = NULL;
    size_t len = strlen(string);
    newString = malloc(len + 1);
    checkMemory(newString);
    memcpy(newString, string, len + 1);
    return newString;
}

static size_t binarySearchRec(infraction arr[], size_t low, size_t high, size_t target)
{
    // Target not found
    if (high < low)
    {
        return (size_t)-1;
    }

    size_t mid = low + (high - low) / 2;

    // Target found, return its position
    if (target == arr[mid].id)
    {
        return mid;
    }

        // Search in the left half
    else if (target < arr[mid].id)
    {
        return binarySearchRec(arr, low, mid - 1, target);
    }

        // Search in the right half
    else
    {
        return binarySearchRec(arr, mid + 1, high, target);
    }
}

static char ** sectionString(char *string, char *delimiters, size_t *dimVec)
{
    size_t counter = 0, dim = 0;

    char *token, **tokens = NULL;

    token = strtok(string, delimiters);
    for (size_t i = 0; token; i++)
    {
        if (counter % BLOCK_IDX == 0)
        {
            dim += BLOCK_IDX;
            tokens = realloc(tokens, dim * sizeof(char *));
            checkMemory(tokens);
        }

        counter++;
        tokens[i] = token;
        token = strtok(NULL, delimiters);
    }

    *dimVec = counter;
    tokens = realloc(tokens, counter * sizeof(char *));
    checkMemory(tokens);
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

static void freeCarList(carList list)
{
    if (list)
    {
        freeCarList(list->next);
        free(list->plate);
        free(list);
    }
}

static void freeAgencyList(agencyList list)
{
    if (list)
    {
        freeAgencyList(list->next);
        free(list->name);
        free(list->countInf);
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
        puts(ERROR_REPEATED_INFRACTION_M);
        exit(ERROR_REPEATED_INFRACTION);
    }

    infractionL->tail = loadInfraction(infractionL->tail, id, name);
    return infractionL;
}

static void initializeInfractions(infractionSystemADT system, infractionCounter * countInf, size_t lastIdx)
{
    checkMemory(countInf);
    for (size_t i = 0; i < system->qtyInfractions; i++)
    {
        countInf[i].id = system->infractions[i].id;
        countInf[i].counter = 0;
        countInf[i].name = system->infractions[i].name;
    }
}

static agencyList addAgencyRec(agencyList l, char * agency, size_t id, size_t infIdx, infractionSystemADT system)
{
    int cmp;

    if (l == NULL || (cmp = strcmp(l->name,agency)) > 0)
    {
        // Create new node
        agencyList newAgency = malloc(sizeof(struct agency));
        newAgency->name = copyString(agency);
        newAgency->qtyTickets = 1;
        newAgency->countInf = malloc(system->qtyInfractions * sizeof(infractionCounter));

        initializeInfractions(system, newAgency->countInf, id);

        newAgency->countInf[infIdx].counter++;
        newAgency->max = &(newAgency->countInf[infIdx]);

        newAgency->next = l;
        system->qtyAgencies++;
        return newAgency;
    }

    if (cmp == 0)
    {
        l->qtyTickets++;
        l->countInf[infIdx].counter++;

        if (l->countInf[infIdx].counter > l->max->counter || (l->countInf[infIdx].counter == l->max->counter && strcmp(l->countInf[infIdx].name,l->max->name) > 0))
        {
            l->max = &(l->countInf[infIdx]);
        }

        return l;
    }

    l->next = addAgencyRec(l->next, agency, id, infIdx, system);
    return l;
}

static void addAgency(infractionSystemADT system, char * agency, size_t id)
{
    size_t infIdx = binarySearchRec(system->infractions, 0, system->qtyInfractions - 1, id);
    system->agencyList = addAgencyRec(system->agencyList, agency, id, infIdx, system);
}

static carList addCarList(carList list, char *plate, infractionSystemADT system, size_t idx)
{
    int cmp;
    carList prev, current = list;

    // Search for the plate
    while(current != NULL && (cmp = strcmp(current->plate, plate)) < 0)
    {
        prev = current;
        current = current->next;
    }

    if (current != NULL && cmp == 0)
    {
        current->counter++;

        if (!system->infractions[idx].biggest || (current->counter > system->infractions[idx].biggest->counter || (current->counter == system->infractions[idx].biggest->counter && strcmp(current->plate, system->infractions[idx].biggest->plate) < 0)))
        {
            system->infractions[idx].biggest = current;
        }

        return list;
    }

    carList newCar = malloc(sizeof(struct car));
    checkMemory(newCar);

    newCar->plate = copyString(plate);
    newCar->counter = 1;
    newCar->next = current;

    if (current == list)
    {
        list = newCar;
        newCar->next = NULL;
        if (!system->infractions[idx].biggest || (system->infractions[idx].biggest->counter == 0 || (system->infractions[idx].biggest->counter == 1 && strcmp(newCar->plate, system->infractions[idx].biggest->plate) < 0)))
        {
            system->infractions[idx].biggest = newCar;
        }
    }

    else
    {
        prev->next = newCar;
    }

    return list;
}

static void addInfraction(infractionSystemADT system, char * plate, size_t id)
{
    int idx = binarySearchRec(system->infractions, 0, system->qtyInfractions - 1, id);

    size_t hashValue = hash(plate);

    system->infractions[idx].qty++;
    system->infractions[idx].vec[hashValue] = addCarList(system->infractions[idx].vec[hashValue], plate, system, idx);
}

static void addTicket(infractionSystemADT system, char * date, char * plate, char * agency, size_t fine, size_t id)
{
    system->qtyTickets++;

    addAgency(system, agency, id);
    addInfraction(system, plate, id);
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
        puts(ERROR_INVALID_SYSTEM_M);
        exit(ERROR_INVALID_SYSTEM);
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

        for (size_t j = 0; j < INITIALS; j++)
        {
            infractionVec[i].vec[j] = NULL;
        }

        infractionVec[i].biggest = NULL;
        infractionsL = infractionsL->tail;
    }

    freeInfractionsList(aux);

    system->qtyInfractions = counter;
    system->infractions = infractionVec;
    return counter;
}

int loadTickets(infractionSystemADT system, FILE *ticketsFile, ticketMap map)
{
    if (!system)
    {
        puts(ERROR_INVALID_SYSTEM_M);
        exit(ERROR_INVALID_SYSTEM);
    }

    size_t qtyTokens, counter = 0;
    char buffer[BUFFER_SIZE], **tokens;

    // Skips the first line
    fgets(buffer, BUFFER_SIZE, ticketsFile);
    while (fgets(buffer, BUFFER_SIZE, ticketsFile))
    {
        tokens = sectionString(buffer, DELIMITER, &qtyTokens);

        if (qtyTokens != map.fields)
        {
            puts(ERROR_INVALID_NUMBER_FIELDS_M);
            exit(ERROR_INVALID_NUMBER_FIELDS);
        }

        addTicket(system, tokens[map.date], tokens[map.plate], tokens[map.agency], atoi(tokens[map.fine]), atoi(tokens[map.infractionID]));
        counter++;

        free(tokens);
    }

    return counter;
}

void freeInfractionSystem(infractionSystemADT system)
{
    for (size_t i = 0; i < system->qtyInfractions; i++)
    {
        free(system->infractions[i].name);

        for (size_t j = 0; j < INITIALS; j++)
        {
            freeCarList(system->infractions[i].vec[j]);
        }
    }
    free(system->infractions);

    freeAgencyList(system->agencyList);

    free(system);
}
