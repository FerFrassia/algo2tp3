# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall

# flags de linkeo
LDFLAGS=

# Agrear acá los directorios a incluir en la compilación
INCDIRS=-I../../../../../Modulos-CPP -I../base

# Agregar acá los archivos .cpp a compilar
SOURCES=test.cpp Driver.cpp ../base/ArbolSintactico.cpp 

# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) $(INCDIRS) $(CFLAGS) $< -c -o $@
