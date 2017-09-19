but: compil

FILES  = algorithmeDeComparaison.o \
	lectureDeFichier.o \
	option.o \
	main.o

FLAGS = -ansi -g

CC = gcc

algorithmeDeComparaison.o: algorithmeDeComparaison.h
		$(CC) $(FLAGS) algorithmeDeComparaison.c -o algorithmeDeComparaison.o -c

lectureDeFichier.o: lectureDeFichier.h
		$(CC) $(FLAGS) lectureDeFichier.c -o lectureDeFichier.o -c

option.o: option.h
		$(CC) $(FLAGS) option.c -o option.o -c

main.o: lectureDeFichier.h algorithmeDeComparaison.h option.h
	$(CC) $(FLAGS) main.c -o main.o -c

compil: $(FILES)
	$(CC) $(FLAGS) -o comparaisonFichier $(FILES)

clean:
	rm -f $(FILES)
	rm -f comparaisonFichier
