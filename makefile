# Makefile para el proyecto 1 de Sistemas operativos I
# Autores: Victor De Ponte
#	   Isaac Lopez

EXE1 = reinas_p
EXE2 = reinas_t
EXE3 = reinas
OBJS1 = main_p.o ${LIBS}
OBJS2 = main_t.o ${LIBS}
LIBS = reinascommon.o almacenamiento.o

TFLAGS = -lpthread
CFLAGS = 

all: ${EXE1} ${EXE2} ${EXE3}

${EXE1}: ${OBJS1}
	gcc ${CFLAGS} ${OBJS1} -o ${EXE1}

${EXE2}: ${OBJS2}
	gcc ${CFLAGS} ${TFLAGS} ${OBJS2} -o ${EXE2}

${EXE3}: pReinas.c pReinas.h
	gcc ${CFLAGS} pReinas.c -o ${EXE3}

main_p.o: main_p.c main_p.h
	gcc ${CFLAGS} -c main_p.c

main_t.o: main_t.c main_t.h 
	gcc ${CFLAGS} -c main_t.c

reinascommon.o: reinascommon.c reinascommon.h
	gcc ${CFLAGS} -c reinascommon.c

almacenamiento.o: almacenamiento.c almacenamiento.h
	gcc ${CFLAGS} -c almacenamiento.c


clean:
	rm *.o ${EXE1} ${EXE2} ${EXE3}
