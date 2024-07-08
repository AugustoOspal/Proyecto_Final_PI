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

typedef struct car * carL;

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

void addTicket(infractionSystemADT city, char * date, char * plate, char * agency, size_t fine, size_t id){
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

        //REVISAR SE DEJA PARA EL FINAL
        aux->counterPerInfraction=malloc(qtyInfractions * sizeof(size_t));
        aux->counterPerInfraction[id]++;
       //

        aux->next=l;
        *flag=1;
        return aux;
    }
    if (compear == 0){
        space(l->tickets,l->qtyTickets,idx);
        l->tickets[l->qtyTickets]=idx;
        l->qtyTickets++;

        //lo mkismo
        l->counterPerInfraction[id]++;
        //

        return l;
    }

    l->next=addAgencyRec(l->next,agency,idx,id,qtyInfractions,flag);
    return l;

}

void addAgency(infractionSystemADT city, char * date, char * plate, char * agency, int fine, size_t id,size_t idx){
    char flag=0;
    city->agencyList = addAgencyRec(city->agencyList,agency,city->tickets[city->qtyTickets-1].index,city->tickets[city->qtyTickets-1].infractionID,city->qtyInfractions,&flag);
    city->qtyAgencies+=flag;

}

int binarySearchRec(infraction arr[], int left, int right, int target) {
    if (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid].id == target) {
            return mid;
        }

        if (arr[mid].id < target) {
            return binarySearchRec(arr, mid + 1, right, target);
        }
        else {
            return binarySearchRec(arr, left, mid - 1, target);
        }
    }

    return -1;
}

carL addCarRec(carL l, char * plate,carL * dir){
    int compear;
    if ( l == NULL || (compear=strcmp(l->plate,plate)) > 0 ){
        carL aux= malloc(sizeof(struct car));
        aux->plate=malloc(strlen(plate)+1);
        strcpy(aux->plate,plate);
        aux->counter++;
        aux->next=l;
        *dir=aux;
        return aux;
    }
    if (compear == 0){
        l->counter++;
        *dir=l;
        return l;
    }
    l->next=addCarRec(l->next,plate,dir);
    return l;
}

void addInfraction(infractionSystemADT city, char * date, char * plate, char * agency, size_t fine, size_t id){
    int idx;
    carL dir;
    if ( (idx=binarySearchRec(city->infractions,0,city->qtyInfractions,id)) == -1 ){
        //falta devolver un error
    }
    city->infractions[idx].qty++;
    city->infractions[idx].carList= addCarRec(city->infractions[idx].carList,plate,&dir);
    if ( city->infractions[idx].biggest == NULL ||  dir->counter > city->infractions[idx].biggest->counter ){
        city->infractions[idx].biggest=dir;
    }
    else if (dir->counter == city->infractions[idx].biggest->counter ){
        if ( strcmp(dir->plate,city->infractions[idx].biggest->plate) < 0 )
            city->infractions[idx].biggest=dir;
    }

}

char** totalTicketsPerInfraction(infractionSystemADT city){
    char * rta[city->qtyInfractions];
    for ( int i=0 ,t=city->qtyInfractions; t != 0 ; t--, i++ ){

    }
}