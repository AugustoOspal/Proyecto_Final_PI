#include "infractionSystemADT.h"
#include <stdlib.h>
#include <string.h>
#include <string.h>

#define BLOCK_TICKETS 1000
#define BLOCK_IDX 50


// ERROR CODES
#define ERROR_ALLOCATING_MEMORY 1
#define ERROR_REPEATED_INFRACTION 2
#define ERROR_INVALID_SYSTEM 3
#define ERROR_INFRACTION_NOT_FOUND 4

#define ERROR_ALLOCATING_MEMORY_M "Memory allocation error"
#define ERROR_REPEATED_INFRACTION_M "Repeated infraction with different name"
#define ERROR_INVALID_SYSTEM_M "Invalid system"
#define ERROR_INFRACTION_NOT_FOUND_M "Infraction not found"

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
    infractionCounter max;
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
        addTicket(system,
                  tokens[map.date],
                  tokens[map.plate],
                  tokens[map.agency],
                  atoi(tokens[map.fine]),
                  atoi(tokens[map.infractionID]));
        counter++;

        free(tokens);
    }
}

void addTicket(infractionSystemADT system, char * date, char * plate, char * agency, size_t fine, size_t id)
{
    if (system-> qtyTickets % BLOCK_TICKETS == 0)
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

    addAgency(system, date, plate, agency, fine,id, idx);
    addInfraction(system, date, plate,agency ,fine, id);
}

static void space(size_t * aux, size_t qty,size_t idx)
{
    if (idx >= qty)
    {
        aux = realloc(aux,idx*sizeof(size_t));
        checkMemory(aux);
    }

    else if (BLOCK_TICKETS % qty == 0)
    {
        aux = realloc(aux, BLOCK_IDX * sizeof(size_t));
        checkMemory(aux);
    }
}

static void initializeInfractions(infractionSystemADT system, infractionCounter * countInf, size_t lastIdx)
{
    for (size_t i = 0; i < system->qtyInfractions; i++)
    {
        countInf[i].id = system->infractions[i].id;
        countInf[i].counter = countInf[i].id == lastIdx;
        countInf[i].name = system->infractions[i].name;
    }
}

static agencyList addAgencyRec( agencyList l,char * agency, size_t idx ,size_t id,infractionSystemADT system ,int infIdx,char * flag)
{
    int compear;
    if (l == NULL || (compear = strcmp(l->name,agency)) > 0)
    {
        // Create new node
        agencyList aux = malloc(sizeof(struct agency));
        aux->name= copyString(agency);
        
        // Gerenate space for tickets
        space(aux->tickets,aux->qtyTickets,idx);

        aux->tickets[aux->qtyTickets]=idx;
        aux->qtyTickets++;


        aux->countInf=malloc(system->qtyInfractions * sizeof(infractionCounter));
        initializeInfractions(system,l->countInf,id);
        aux->countInf[infIdx].counter++;
        
        aux->next=l;
        *flag=1;
        return aux;
    }

    if (compear == 0)
    {
        space(l->tickets,l->qtyTickets,idx);
        l->tickets[l->qtyTickets]=idx;
        l->qtyTickets++;
        l->countInf[infIdx].counter++;

        return l;
    }

    l->next=addAgencyRec(l->next,agency,idx,id,system,flag);
    return l;

}

void addAgency(infractionSystemADT system, char * date, char * plate, char * agency, int fine, size_t id,size_t idx) {
    char flag = 0;
    int infIdx = binarySearchRec(system->infractions, 0, system->qtyInfractions, id);
    system->agencyList = addAgencyRec(system->agencyList, agency, system->tickets[system->qtyTickets - 1].index,
                                      system->tickets[system->qtyTickets - 1].infractionID, system, infIdx,
                                      &flag);
    system->qtyAgencies += flag;
    if (!system->agencyList->max || system->agencyList->countInf[infIdx].counter > system->agencyList->max->counter)
    {
        system->agencyList->max->counter = system->agencyList->countInf[infIdx].counter;
        system->agencyList->max->id = system->agencyList->countInf[infIdx].id;
        system->agencyList->max->name = (system->infractions[infIdx].name);
    }
    
    elseif(system->agencyList->countInf[infIdx].counter == system->agencyList->max->counter && strcmp(system->agencyList->countInf[infIdx].name,system->agencyList->max->name) > 0)
    {
        system->agencyList->max->counter = system->agencyList->countInf[infIdx].counter;
        system->agencyList->max->id = system->agencyList->countInf[infIdx].id;
        system->agencyList->max->name = system->infractions[infIdx].name;
    }
}

static int binarySearchRec(infraction arr[], int left, int right, int target)
{
    if (left <= right) 
    {
        int mid = left + (right - left) / 2;

        if (arr[mid].id == target) 
        {
            return mid;
        }

        if (arr[mid].id < target) 
        {
            return binarySearchRec(arr, mid + 1, right, target);
        }
        
        else 
        {
            return binarySearchRec(arr, left, mid - 1, target);
        }
    }

    return -1;
}

static carList addCarRec(carList l, char * plate,carList * dir)
{
    int compear;
    if (l == NULL ||(compear = strcmp(l->plate, plate)) > 0)
    {
        carList aux = malloc(sizeof(struct car));
        aux->plate = copyString(plate);
        aux->counter++;
        aux->next = l;
        *dir = aux;
        return aux;
    }
    
    if (compear == 0){
        l->counter++;
        *dir = l;
        return l;
    }
    l->next = addCarRec(l->next, plate, dir);
    return l;
}

void addInfraction(infractionSystemADT system, char * date, char * plate, char * agency, size_t fine, size_t id)
{
    carList dir;
    int idx = binarySearchRec(system->infractions,0,system->qtyInfractions,id);
    
    if (idx == -1)
    {
        puts(ERROR_INFRACTION_NOT_FOUND_M);
        exit(ERROR_INFRACTION_NOT_FOUND);
    }
    
    system->infractions[idx].qty++;
    system->infractions[idx].carList= addCarRec(system->infractions[idx].carList,plate,&dir);

    if (system->infractions[idx].biggest == NULL || dir->counter > system->infractions[idx].biggest->counter )
    {
        system->infractions[idx].biggest=dir;
    }
    
    else if (dir->counter == system->infractions[idx].biggest->counter && strcmp(dir->plate,system->infractions[idx].biggest->plate) < 0)
    {
            system->infractions[idx].biggest=dir;
    }
}