cmake_minimum_required(VERSION 3.16)
project(final_pi)

set(CMAKE_C_FLAGS "-Wall -pedantic -std=c99 -lm -g -fsanitize=address -DNYC")

add_executable(compileNYC main.c Library/helpers.c
        Library/helpers.h
        Library/infractionSystemADT.c
        Library/infractionSystemADT.h
        Library/htmlTable.c
        Library/htmlTable.h
)

add_custom_target(runNYC
        COMMAND compileNYC
        DEPENDS compileNYC
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)