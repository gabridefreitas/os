CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS = -lpthread
TARGET = atividade
SOURCE = atividade.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
