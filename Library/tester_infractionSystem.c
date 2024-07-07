#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "infractionSystemADT.h"

int main(void)
{
    puts("infractionSystemADT");

    // sectionString
    size_t dim;
    char string[] = "59;EXPIRED METER CENTRAL BUSINESS DISTRICT";
    char delimiters[] = ";";
    char ** strings = sectionString(string, delimiters, &dim);

    assert(dim == 2);
    assert(strcmp(strings[0], "59") == 0);
    assert(strcmp(strings[1], "EXPIRED METER CENTRAL BUSINESS DISTRICT") == 0);
    puts("OK: sectionSort");

    // loadInfractions
    FILE *file = fopen("../DataSets/infractionsNYC.csv", "r");
    infractionSystemADT system = makeNewInfractionSystem();
    infractionMap map = {0, 1};
    loadInfractions(system, file, map);
}