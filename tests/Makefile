CC    = /home/digirols/openmpi-1.8.5-normal/build/bin/mpicc
CFLAGS= -std=c99 -D_POSIX_C_SOURCE=199309L -g3 -O0 -I../include
LDFLAGS=  -L ../lib/ -Wl,-rpath,../lib/ -lff


all: broadcast sbroadcast scatter

%: %.c
	$(CC) $(CFLAGS) $*.c -o $* $(OBJECTS) $(LDFLAGS)

