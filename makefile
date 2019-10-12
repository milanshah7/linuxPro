.PHONY = misra

TOOL := cppcheck

MISRAFLAGS := --enable=all
#MISRAFLAGS += --check-config

DIR := ./

LIBS := -lpthread
LIBS += -lrt

SRC1 := server.c
SRC2 += client.c

DEP := sock.c
DEP += msgQ.c

EXE1 := server
EXE2 := client

CFLAGS := -Wall

all:
	$(CC) $(CFLAGS) $(SRC1) $(DEP) -o $(EXE1) $(LIBS)
	$(CC) $(CFLAGS) $(SRC2) $(DEP) -o $(EXE2) $(LIBS)

misra:
	$(TOOL) $(MISRAFLAGS) $(DIR)

clean:
	$(RM) $(EXE1) $(EXE2)
