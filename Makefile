SHELL = /bin/sh
CC    = mpicc
CFLAGS= -std=c99 -g -O3 -Iinclude -I $(P4_TEST_DIR) -I $(P4_INCLUDE_DIR) -fPIC
LDFLAGS= -L $(P4_TEST_DIR)/.libs/ -L $(P4_LIB_DIR) -Wl,-rpath,$(P4_LIB_DIR) -lportals -lportals_runtime -lm -shared
#CFLAGS= -std=c99 -g -O3 -Iinclude -I $(P4_TEST_DIR) -I $(P4_INCLUDE_DIR)
#LDFLAGS= -lm 

#LIBFILE = ff.c ff_send.c ff_recv.c ff_op.c ff_storage.c ff_schedule.c ff_collectives.c ff_computation.c ff_container.c

TARGET  = lib/libff.so
SOURCES = $(shell echo src/*.c src/colls/*.c)
HEADERS = $(shell echo include/*.h)
OBJECTS = $(SOURCES:.c=.o)


.PHONY: show

all: $(TARGET)

clean:
	rm src/*.o src/colls/*.o

paper: SC/outline.tex
	cd SC; pdflatex -synctex=1 -interaction=nonstopmode "outline".tex
        
show:
	evince SC/outline.pdf

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)


