CC      ?= gcc

CFLAGS  ?= 
LDFLAGS ?= 
LDLIBS  ?= -lgcrypt

SUFFIXES ?= .c .o 
.SUFFIXES: $(SUFFIXES) .

PROG  = pflupg 

OBJS  = pflupg.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm pflupg.o pflupg
