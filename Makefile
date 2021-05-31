CC= gcc
TARGET=run
SOURCES= main.c ga.c

all:
	$(CC) -o $(TARGET) $(SOURCES)
