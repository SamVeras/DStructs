# Compilador
COMPILER := gcc
FLAGS := -g -Wall -W -Werror -fsanitize=address -std=c99
LIBS :=

SRCEXT := c
HDREXT := h
OBJEXT := o

SOURCES := $(wildcard *.$(SRCEXT))
HEADERS := $(wildcard *.$(HDREXT))
OBJECTS := $(SOURCES:.$(SRCEXT)=.$(OBJEXT))

 # Nome da aplicação
TARGET := DoublyLinkedList

# Principal
$(TARGET): $(OBJECTS)
	$(COMPILER) $(FLAGS) $^ -o $@ $(LIBS)
	@echo "$(GC)Executável compilado: $(TARGET)$(NC)"

# Objetos
$(OBJECTS): %.$(OBJEXT): %.$(SRCEXT) $(HEADERS)
	$(COMPILER) $(FLAGS) -c $< -o $@
	@echo "$(CC)Objeto compilado: $@$(NC)"

# Limpar
clean:
	@rm -f $(TARGET) $(OBJECTS)
	@echo "$(BC)Arquivos limpados:\n$(RC)$(TARGET) $(OBJECTS)$(NC)"

# Executar
run:
	@echo "$(MC)Rodando $(TARGET)$(NC)"
	@./$(TARGET)


# bla:
# 	@echo "bla"
# 	@echo "$(SRCEXT),$(HDREXT),$(OBJEXT)"
# 	@echo "Sources: $(SOURCES)"
# 	@echo "Headers: $(HEADERS)"
# 	@echo "Objects: $(OBJECTS)"

.PHONY: all clean run

# Cores
NC := \033[0m
GC := \033[32m
MC := \033[35m
BC := \033[34m
CC := \033[36m
RC := \033[31m