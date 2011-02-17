# Makefile para el proyecto 1 de Sistemas operativos I
# Autores: Victor De Ponte
#	   Isaac Lopez

EXE1 = reinas_p
EXE2 = reinas_t
OBJS1 = main_p.o almacenamiento.o
OBJS2 = main_t.o almacenamiento.o

CFLAGS = -lpthread

all: ${EXE1} ${EXE2}

${EXE1}: ${OBJS1}
	gcc ${CFLAGS} ${OBJS1} -o ${EXE1}

${EXE2}: ${OBJS2}
	gcc ${CFLAGS} ${OBJS2} -o ${EXE2}

main_p.o: main_p.c main_p.h
	gcc -c main_p.c

main_t.o: main_t.c main_t.h
	gcc -c main_t.c

almacenamiento.o: almacenamiento.c almacenamiento.h
	gcc -c almacenamiento.c

clean:
	rm *.o ${EXE1} ${EXE2}