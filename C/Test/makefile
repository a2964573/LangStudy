CC		= gcc
CFLAGS	= -Wall -g
PROJECT	= execute
OBJECT  = main.o
SOURCE  = main.c

all: $(PROJECT)

$(OBJECT): $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)

$(PROJECT): $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(PROJECT)

clean:
	rm -f $(PROJECT)

upver:
	rm -f $(OBJECT)

