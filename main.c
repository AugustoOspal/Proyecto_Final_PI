#include "main.h"
#include "helpers.h"

int main(int argc, char *argv[])
{
    validateCommandLine(argc);
    validateFiles(argc, argv);
}