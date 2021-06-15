CC= gcc
TARGET=run
SOURCES= main.c ga.c

.PHONY: all 10

all:
	$(CC) -o $(TARGET) $(SOURCES)

10:
	$(CC) -o $(TARGET) $(SOURCES) -D NPOP=10

50:
	$(CC) -o $(TARGET) $(SOURCES) -D NPOP=50

200:
	$(CC) -o $(TARGET) $(SOURCES) -D NPOP=200

500:
	$(CC) -o $(TARGET) $(SOURCES) -D NPOP=500

1000:
	$(CC) -o $(TARGET) $(SOURCES) -D NPOP=1000
