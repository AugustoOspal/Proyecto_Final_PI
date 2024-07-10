# Proyecto Final Programación Imperativa


### Source Codes 

- main.c: The file responsible for creating the .csv files and the .html file. This file could work as an example of the library.
- helpers.c: Contains the functions for the front-end and some extras that might be useful such us a memory checker.
- htmlTables.c: Contains functions and a ADT for creating html files with ease.


### Header files

- main.h: Contains some error codes and two constants, one for a buffer used main.c and the delimiter that separates the data from the data file, assuming the keywords are united by that character.
- helper.h: It has the prototypes for the functions in helpers.c. It also contains some constant strings to mark the top of the csv files and the html files
- htmlTables.h In contains the prototypes of the functions in htmlTables.c and the pointer to the ADT

### Other files

- Makefile: Responsible for making the executables to process the data
- Structure_objets.puml: It contains the structures that we used in the infractionSystem ADT in a practical diagram

### Subdirectories 

- Library: It contains helpers, htmlTable, and infractionSystem.

## Comands

make all: creates the executable for New York and Chicago

make NYC: creates the executable just for New York

make CHI: creates the executable just for Chicago

make infractionSystemADT.o: compiles the infractionSystemADT library

make htmlTable.o: compiles the htmlTables library

make helpers.o: compiles the helpers library

make clean: deletes the .out and .o files from the main directory

## How to run the proyect

- 1: We have to go to the directory of the project
- 2: We execute either make all, make NYC or make CHI depending on which city data you want to process
- 3: You will have either parkingTicketsNYC.out or parkingTicketsCHI.out, or both, so now you have to type in the command line one of both files follow by the tickets file and the infractions file. It important to keep the order of the files. Remember that the program only process data from a .csv file
- 4: Finally there are 6 files that will be created, all of them containing the process data.

## Authors
- Lucas Rodriguez
- Augusto Ospal Felipe Madeo

## Contact info.
- Augusto Ospal
  - Work email: aospalmadeo@itba.edu.ar
  - Personal email: augustoospal@gmail.com
- Lucas Rodriguez
  - github: 1ucasrn