CC= gcc
TARGET=run
SOURCES= main.c

all:
	$(CC) -o $(TARGET) $(SOURCES)
