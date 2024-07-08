#include "infractionSystemADT.h"
#include <stdlib.h>
#include <string.h>

#define BLOCK_TICKETS 1000
#define BLOCK_IDX 50


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
    car *carList;
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
    size_t len;
    size_t qtyTickets;
    size_t *tickets;
    infractionCounter *countInf;
    infractionCounter *max;
    struct agency *next;
}agency;

typedef struct agency * agencyList;

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
    infraction * infractions;
    ticket * tickets;
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
        if (counter % BLOCK_IDX == 0)
        {
            dim += BLOCK_IDX;
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
        free(list->tickets);
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
        freeCarList(system->infractions[i].carList);
    }
    free(system->infractions);

    freeAgencyList(system->agencyList);

    for (size_t i = 0; i < system->qtyTickets; i++)
    {
        free(system->tickets[i].plate);
        free(system->tickets[i].date);
        free(system->tickets[i].agency);
    }
    free(system->tickets);
    
    free(system);
}

static void initializeInfractions(infractionSystemADT system, infractionCounter * countInf, size_t lastIdx)
{
    for (size_t i = 0; i < system->qtyInfractions; i++)
    {
        countInf[i].id = system->infractions[i].id;
        countInf[i].counter = 0;
        countInf[i].name = system->infractions[i].name;
    }
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

static agencyList addAgencyRec(agencyList l, char * agency, size_t idx, size_t infIdx, infractionSystemADT system)
{
    int cmp;
    size_t id = system->tickets[idx].infractionID;

    if (l == NULL || (cmp = strcmp(l->name,agency)) > 0)
    {
        // Create new node
        agencyList newAgency = malloc(sizeof(struct agency));
        newAgency->name = copyString(agency);
        newAgency->tickets = malloc(BLOCK_TICKETS * sizeof(size_t));
        newAgency->tickets[0] = idx;
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
        if (l->qtyTickets % BLOCK_TICKETS == 0)
        {
            l->tickets = realloc(l->tickets, BLOCK_TICKETS * sizeof(size_t));
            checkMemory(l->tickets);
        }

        l->tickets[l->qtyTickets] = idx;
        l->qtyTickets++;
        l->countInf[infIdx].counter++;

        if (l->countInf[infIdx].counter > l->max->counter)
        {
            l->max = &(l->countInf[infIdx]);
        }

        else if(l->countInf[infIdx].counter == l->max->counter && strcmp(l->countInf[infIdx].name,l->max->name) > 0)
        {
            l->max = &(l->countInf[infIdx]);
        }

        return l;
    }

    l->next = addAgencyRec(l->next, agency, idx, infIdx, system);
    return l;
}

void addAgency(infractionSystemADT system, char * agency, size_t idx)
{
    size_t infIdx, id;

    id = system->tickets[idx].infractionID;
    infIdx = binarySearchRec(system->infractions, 0, system->qtyInfractions - 1, id);

    system->agencyList = addAgencyRec(system->agencyList, agency, idx, infIdx, system);
}

static carList addCarRec(carList l, char * plate, infractionSystemADT system, size_t idx)
{
    int cmp;

    if (l == NULL ||(cmp = strcmp(l->plate, plate)) < 0)
    {
        carList aux = malloc(sizeof(struct car));
        aux->plate = copyString(plate);
        aux->counter++;
        aux->next = l;

        if (system->infractions[idx].biggest == NULL)
        {
            system->infractions[idx].biggest = aux;
        }

        else if(aux->counter == system->infractions[idx].biggest->counter && strcmp(aux->plate,system->infractions[idx].biggest->plate) < 0)
        {
            system->infractions[idx].biggest = aux;
        }
        return aux;
    }

    if (cmp == 0)
    {
        l->counter++;

        if (l->counter > system->infractions[idx].biggest->counter)
        {
            system->infractions[idx].biggest = l;
        }

        else if(l->counter == system->infractions[idx].biggest->counter && strcmp(l->plate,system->infractions[idx].biggest->plate) < 0)
        {
            system->infractions[idx].biggest = l;
        }

        return l;
    }

    l->next = addCarRec(l->next, plate,system,idx);
    return l;
}

void addInfraction(infractionSystemADT system, char * plate, size_t id)
{
    int idx = binarySearchRec(system->infractions, 0, system->qtyInfractions - 1, id);

    system->infractions[idx].qty++;
    system->infractions[idx].carList = addCarRec(system->infractions[idx].carList, plate, system, idx);
}


void addTicket(infractionSystemADT system, char * date, char * plate, char * agency, size_t fine, size_t id)
{
    if (system->qtyTickets % BLOCK_TICKETS == 0)
    {
        system->tickets = realloc(system->tickets, BLOCK_TICKETS * sizeof(ticket));
        checkMemory(system->tickets);
    }

    size_t idx = system->qtyTickets;

    system->tickets[idx].plate = copyString(plate);
    system->tickets[idx].date = copyString(date);
    system->tickets[idx].agency = copyString(agency);
    system->tickets[idx].fine = fine;
    system->tickets[idx].infractionID = id;
    system->tickets[idx].index = idx;
    system->qtyTickets++;

    addAgency(system, agency, idx);
    addInfraction(system, plate, id);
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
        addTicket(system, tokens[map.date], tokens[map.plate], tokens[map.agency], atoi(tokens[map.fine]), atoi(tokens[map.infractionID]));
        counter++;
        if (qtyTokens != map.fields)
        {
            puts(ERROR_INVALID_NUMBER_FIELDS_M);
            exit(ERROR_INVALID_NUMBER_FIELDS);
        }

        free(tokens);
    }

    system->tickets = realloc(system->tickets, counter * sizeof(ticket));
    return counter;
}

// Tester functions

void printInfractions(infractionSystemADT system)
{
    for (size_t i = 0; i < system->qtyInfractions; i++)
    {
        printf("Infraction ID: %lu\n", system->infractions[i].id);
        printf("Infraction Name: %s\n", system->infractions[i].name);
        printf("Infraction Qty: %lu\n", system->infractions[i].qty);
        printf("Infraction Biggest: %s\n", system->infractions[i].biggest->plate);
        printf("Infraction Biggest Counter: %lu\n", system->infractions[i].biggest->counter);
        puts("Car List:");
        carList aux = system->infractions[i].carList;
        while (aux)
        {
            printf("Plate: %s\n", aux->plate);
            printf("Counter: %lu\n", aux->counter);
            aux = aux->next;
        }
    }
}

void printTickets(infractionSystemADT system)
{
    for (size_t i = 0; i < system->qtyTickets; i++)
    {
        printf("Ticket Plate: %s\n", system->tickets[i].plate);
        printf("Ticket Date: %s\n", system->tickets[i].date);
        printf("Ticket Agency: %s\n", system->tickets[i].agency);
        printf("Ticket Fine: %lu\n", system->tickets[i].fine);
        printf("Ticket Infraction ID: %lu\n", system->tickets[i].infractionID);
        printf("Ticket Index: %lu\n", system->tickets[i].index);
    }
}

void printAgencies(infractionSystemADT system)
{
    for (size_t i = 0; i < system->qtyAgencies; i++)
    {
        printf("Agency Name: %s\n", system->agencyList[i].name);
        printf("Agency Qty Tickets: %lu\n", system->agencyList[i].qtyTickets);
        printf("Agency Max Infraction: %s\n", system->agencyList[i].max->name);
        printf("Agency Max Infraction Counter: %lu\n", system->agencyList[i].max->counter);
        puts("Agency Tickets:");
        for (size_t j = 0; j < system->agencyList[i].qtyTickets; j++)
        {
            printf("Ticket Index: %lu\n", system->agencyList[i].tickets[j]);
        }
        puts("Agency Infractions:");
        for (size_t j = 0; j < system->qtyInfractions; j++)
        {
            printf("Infraction ID: %lu\n", system->agencyList[i].countInf[j].id);
            printf("Infraction Name: %s\n", system->agencyList[i].countInf[j].name);
            printf("Infraction Counter: %lu\n", system->agencyList[i].countInf[j].counter);
        }
    }
}

void printInfractionSystem(infractionSystemADT system)
{
    printInfractions(system);
    printTickets(system);
    printAgencies(system);
}

// End of tester functions