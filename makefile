.SILENT :

LIB = Lib

OBJ = $(LIB)/output.o $(LIB)/input.o $(LIB)/menu.o $(LIB)/saveload.o

main : 	main.c $(OBJ)
	echo Creation du main
	gcc -o main main.c $(OBJ) -I$(LIB)

$(LIB)/input.o :	$(LIB)/input.h $(LIB)/input.c
					echo Creation de input.o
					gcc -c $(LIB)/input.c
					mv input.o $(LIB)

$(LIB)/output.o :	$(LIB)/output.h $(LIB)/output.c
					echo Creation de output.o
					gcc -c $(LIB)/output.c
					mv output.o $(LIB)

$(LIB)/menu.o :	$(LIB)/menu.h $(LIB)/menu.c
		echo Creation de menu.o
		gcc -c $(LIB)/menu.c
		mv menu.o $(LIB)

$(LIB)/saveload.o :	$(LIB)/saveload.h $(LIB)/saveload.c
			echo Creation de saveload.o
			gcc -c $(LIB)/saveload.c
			mv saveload.o $(LIB)
