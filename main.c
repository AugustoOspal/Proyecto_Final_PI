#include "main.h"
#include "helpers.h"

int main(int argc, char *argv[])
{
    validateCommandLine(argc);
    validateFiles(argc, argv);
    int a;
    //Testing
    FILE *file = fopen(argv[1], "r");
    char buffer[2000] = {0};
    printf("%s", fgets(buffer, 2000, file));
}

