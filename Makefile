#
# Makefile for Project in /home/Danz/Project/Gobang
#
# Made by gaspar_d
# Login   <gaspar_d@epita.fr>
#
# Started on  Wed 26 May 2010 04:04:38 PM CST gaspar_d
# Last update Fri 25 Jun 2010 03:21:58 AM CST gaspar_d
#

CC	= gcc
AR	= ar
RM	= rm
SRCDIR = src/
BINDIR = bin/
CFLAGS	= -Wall -W -std=c99 -pedantic \
	  -Wfloat-equal -Wundef -Wshadow -Wpointer-arith \
	  -Wbad-function-cast -Wcast-qual -Wcast-align \
	  -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes \
	  -Wmissing-declarations -Wnested-externs \
	  -Wunreachable-code
CCFLAGS = -Wall -Wcast-align -Wundef -pedantic -O3
LDFLAGS	= -L/usr/lib -lstdc++ -lboost_system -lpthread
ARFLAGS	= rsc
RMFLAGS = -rf
TARGET	= gobang
SOURCE	= src/get_successors.cc src/main.cc src/alpha_beta.cc \
	  src/heuristic.cc src/load.cc src/display.cc \
	  src/utils.cc src/game_shell.cc src/heuristic2.cc \
	  src/interface.cc
OBJS	= $(SOURCE:.cc=.o)
TODEL	= tags *~ .*.sw? \\\#*\\\# *.core

.PHONY: all clean distclean

DOC_GENERATOR	=	doxygen
DOC_CONFIG_FILE	=	.doxygen
DOC_FLAG	=

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(BINDIR)/$(TARGET) $(OBJS) $(LDFLAGS)

.cc.o:
	$(CC) $(CCFLAGS) -c $< -o $@

doc: $(DOC_CONFIG_FILE)
	$(DOC_GENERATOR) $(DOC_FLAG) $(DOC_CONFIG_FILE)

clean:
	$(RM) $(RMFLAGS) $(OBJS) $(TODEL)

distclean: clean
	$(RM) $(RMFLAGS) $(TARGET)
