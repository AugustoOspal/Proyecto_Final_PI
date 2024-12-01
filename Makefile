COMPILER=gcc
CHI_OUTPUT_FILE=parkingTicketCHI.out
NYC_OUTPUT_FILE=parkingTicketsNYC.out
CFLAGS=-Wall -pedantic -std=c99 -fsanitize=address
TRASHFILES=*.out *.o

all: CHI NYC

CHI: infractionSystemADT.o htmlTable.o helpers.o main.c
	@$(COMPILER) $(CFLAGS) infractionSystemADT.o htmlTable.o helpers.o main.c -DCHI -o parkingTicketsCHI.out

NYC: infractionSystemADT.o htmlTable.o helpers.o main.c
	@$(COMPILER) $(CFLAGS) infractionSystemADT.o htmlTable.o helpers.o main.c -DNYC -o parkingTicketsNYC.out

infractionSystemADT.o: Library/infractionSystemADT.c
	@$(COMPILER) -c Library/infractionSystemADT.c $(CFLAGS) -o infractionSystemADT.o

htmlTable.o: Library/htmlTable.c
	@$(COMPILER) -c Library/htmlTable.c $(CFLAGS) -o htmlTable.o

helpers.o: Library/helpers.c
	@$(COMPILER) -c Library/helpers.c $(CFLAGS) -o helpers.o

clean:
	@rm -f $(TRASHFILES)

