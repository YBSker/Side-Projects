CC = gcc
CONSERVATIVE_FLAGS = -std=c99 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
LDFLAGS = -lm
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

project: ppm_io.o imageManip.o project.o
	$(CC) $(LDFLAGS)  ppm_io.o imageManip.o project.o -o project

imageManip.o: imageManip.c imageManip.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c imageManip.c  

ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c

project.o: project.c imageManip.h ppm_io.h
	$(CC) $(CFLAGS) -c project.c

clean:
	rm -f *.o imageManip menu ppm_io project
