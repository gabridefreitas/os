CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
TARGET = atividade
SOURCE = atividade.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean