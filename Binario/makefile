# Nombre del ejecutable
TARGET = ejecutable

# Archivos fuente
SRC = complemento2.c

# Compilador
CC = gcc

# Flags opcionales (podés sumar -Wall para ver warnings)
CFLAGS = 

# Regla principal
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET).exe $(SRC)

#run
run: $(TARGET)
	.\$(TARGET).exe

# Limpia el ejecutable
clean:
	del $(TARGET).exe
