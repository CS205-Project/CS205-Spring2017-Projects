EXECS=dijkstra
MPICC?=mpicc

all: ${EXECS}

dijkstra: dijkstra.c
	${MPICC} -o dijkstra -lm -fopenmp dijkstra.c

clean:
	rm -f ${EXECS}
