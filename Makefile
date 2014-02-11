#### GTThread Library Makefile

CFLAGS  = -Wall -pedantic
LFLAGS  =
CC      = gcc
RM      = /bin/rm -rf
AR      = ar rc
RANLIB  = ranlib

PROG_SRC = gtDiningPhilosophers.c

PROG_OBJ = $(patsubst %.c,%.o,$(PROG_SRC))

# pattern rule for object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

PROGNAME = gtDiningPhilosophers

LIBRARY = gtthread.a

LIB_SRC = gtthread.c gtthread_sched.c gtthread_mutex.c gtthread_queue.c

LIB_OBJ = $(patsubst %.c,%.o,$(LIB_SRC))

# pattern rule for object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(LIBRARY) $(PROGNAME)

$(LIBRARY): $(LIB_OBJ)
	$(AR) $(LIBRARY) $(LIB_OBJ)
	$(RANLIB) $(LIBRARY)
	
$(PROGNAME): $(PROG_OBJ)
	$(CC) $(CFLAGS) -o $(PROGNAME) $(PROG_OBJ) $(LIBRARY)

clean:
	$(RM) $(LIBRARY) $(LIB_OBJ)
	$(RM) $(PROGNAME) $(PROG_OBJ)

.PHONY: depend
depend:
	$(CFLAGS) -- $(LIB_SRC)  2>/dev/null
	$(CFLAGS) -- $(PROG_SRC) 2>/dev/null
