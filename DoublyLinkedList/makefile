COMPILER := gcc # Compilador
FLAGS := -g -Wall -W -Werror -fsanitize=address -std=c99
LIBS :=

SRCEXT := c # Extensão dos arquivos-fonte
HDREXT := h # Extensão dos arquivos-headers
OBJEXT := o # Extensão dos objetos

SOURCES := $(wildcard *.$(SRCEXT)) # Encontrar arquivos-fonte
HEADERS := $(wildcard *.$(HDREXT)) # Encontrar arquivos-headers
OBJECTS := $(patsubst %.$(SRCEXT), %.$(OBJEXT), $(SOURCES)) # Encontrar objetos

TARGET := DoublyLinkedList # Nome da aplicação

# Principal
$(TARGET): $(OBJECTS)
	$(COMPILER) $(FLAGS) $^ -o $@ $(LIBS)
	@echo "$(CC) $(TARGET) $(NC)"

# Objetos
$(OBJECTS): $(SOURCES) $(HEADERS)
	$(COMPILER) $(FLAGS) -c $< -o $@
	@echo "$(CC) $@ $(NC)"

# Limpar
clean:
	rm -f $(TARGET) $(OBJECTS)
	@echo "$(CC) $(TARGET) $(NC)"

# Executar
run:
	@echo "$(CC) $(TARGET) $(NC)"
	./$(TARGET)

.PHONY: all clean run

# Cores
NC := \033[0m
GC := \033[32m
MC := \033[35m
BC := \033[34m
CC := \033[36m