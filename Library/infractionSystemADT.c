#include "infractionSystemADT.h"
#include <stdlib.h>
#include <string.h>
#include <string.h>

#define BLOCK_TICKETS 1000
#define BLOCK_IDX 50

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

typedef struct agency * agencyL;

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


// SIEMPRE LLAMAR PRIMERO A ADDTICKET ANTES Q ADDAGENCY

infractionSystemADT new(){
    infractionSystemADT aux = calloc(1,sizeof(infractionSystemCDT));

    return aux;
}

void addTicket(infractionSystemADT city, char * date, char * plate, char * agency, int fine, int id){
    if ( BLOCK_TICKETS % city-> qtyTickets == 0 ){
        city->tickets = realloc(city->tickets,BLOCK_TICKETS * sizeof(ticket));
        // falta hacer cuando realloc no encuentra espacion en memoria
    }
    int idx = city->qtyTickets;

    city->tickets[idx].plate=malloc(strlen(plate)+1);
    strcpy(city->tickets[idx].plate,plate);

    city->tickets[idx].date=malloc(strlen(date)+1);
    strcpy(city->tickets[idx].date,date);

    city->tickets[idx].agency=malloc(strlen(agency)+1);
    strcpy(city->tickets[idx].agency,agency);

    city->tickets[idx].fine=fine;
    city->tickets[idx].infractionID=id;
    city->tickets[idx].index=idx;
    city->qtyTickets++;

}

void space(size_t * aux, size_t qty,size_t idx){
    if ( idx >= qty ){
        aux=realloc(aux,idx*sizeof(size_t));
        // lo mismo
    }
    else if ( BLOCK_TICKETS % qty == 0 ){
        aux = realloc(aux,BLOCK_IDX * sizeof(size_t));
        // falta hacer cuando realloc no encuentra espacion en memoria
    }
}

agencyL addAgencyRec( agencyL l,char * agency, size_t idx ,size_t id, size_t qtyInfractions, char * flag){
    int compear;
    if ( l == NULL || (compear=strcmp(l->name,agency)) > 0){
        agencyL aux = malloc(sizeof(struct agency));
        int size=strlen(agency);
        aux->name=malloc(size+1);
        strcpy(aux->name,agency);
        aux->len=size;
        space(aux->tickets,aux->qtyTickets,idx);
        aux->tickets[aux->qtyTickets]=idx;
        aux->qtyTickets++;

        //esperar a rta
        aux->counterPerInfraction=malloc(qtyInfractions * sizeof(size_t));
        aux->counterPerInfraction[id]++;

        aux->next=l;
        *flag=1;
        return aux;
    }
    if (compear == 0){
        space(l->tickets,l->qtyTickets,idx);
        l->tickets[l->qtyTickets]=idx;
        l->qtyTickets++;

        //esperar a rta
        l->counterPerInfraction[id]++;
        return l;
    }

    l->next=addAgencyRec(l->next,agency,idx,id,qtyInfractions,flag);
    return l;

}

void addAgency(infractionSystemADT city, char * date, char * plate, char * agency, int fine, int id,int idx){
    char flag=0;
    city->agencyList = addAgencyRec(city->agencyList,agency,city->tickets[city->qtyTickets-1].index,city->tickets[city->qtyTickets-1].infractionID,city->qtyInfractions,&flag);
    city->qtyAgencies+=flag;

}

