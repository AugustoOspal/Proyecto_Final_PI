#include "helpers.h"

void validateCommandLine(int argc)
{
    if (argc != NUMBER_INPUT_FILES + 1)
    {
        puts(ERROR_NUMBER_INPUT_FILES_M);
        exit(ERROR_NUMBER_INPUT_FILES);
    }
}

void validateFiles(int argc, char *argv[])
{
    for (size_t i = 1; i < argc; i++)
    {
        if (!argv[i] || !fopen(argv[i], "r"))
        {
            puts(ERROR_EMPTY_FILE_M);
            exit(2);
        }
    }
}