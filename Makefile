CC = g++
CFLAGS = -g -Wall

SRCS = main.cpp src/Container.cpp src/FileHandler.cpp src/FlashCard.cpp

INCLUDES = -I./include

OBJS = $(SRCS:.c=.o)

MAIN = FlashCard

.PHONY: depend clean

all:	$(MAIN)

$(MAIN):	$(OBJS)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES)-c $< -o $@

clean:
	$(RM) *.o *- $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
