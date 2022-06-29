##https://cran.r-project.org/bin/macosx/
## Licensed under the MIT Licence
## (C) 2014 Christoph Martin
## For licence text go to http://opensource.org/licenses/MIT

## Makefile
# change to your prefered compiler
CC=gcc
# replace with name of the executable
OUTPUTNAME=Projet_C_2022
# add all source files here but with '.o' instead of '.c'
OBJS= integration.o affichage.o fir.o iir.o mesure.o fichiers.o main.o #lecture.o test_lecture.o fichiers.o		



# POUR COMPLIER : ecrire "make all exec" dans le terminal pour compiler et executer directement
default: all

all: $(OBJS)
	$(CC) -o $(OUTPUTNAME) $(OBJS)


debug: $(OBJS)
	$(CC) -g -o $(OUTPUTNAME) $(OBJS)

opt: $(OBJS)
	$(CC) -O3 -o $(OUTPUTNAME) $(OBJS)

.PHONY: clean
clean:
	rm *.o
	rm $(OUTPUTNAME)

exec:
	./$(OUTPUTNAME)
