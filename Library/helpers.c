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
        FILE *file = fopen(argv[i], "r");
        if (!argv[i] || !file)
        {
            fclose(file);
            puts(ERROR_EMPTY_FILE_M);
            exit(2);
        }

        fclose(file);
    }
}