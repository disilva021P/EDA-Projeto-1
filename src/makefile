# Nome do executável final
TARGET = programaCompilado

# Lista de arquivos-fonte e os cabeçalhos
SRCS = main.c funcoes.c erros.c grafos.c
HEADERS = funcoes.h dados.h erros.h grafos.h

# Gerar nomes dos objetos (.o) automaticamente a partir dos fontes (.c)
OBJS = $(SRCS:.c=.o)

# Nome da biblioteca estática
LIB_NAME = libfuncoes.a

# Compilador e flags
CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -L. -l:$(LIB_NAME)  # Linkar com a biblioteca estática

# Regra padrão (compilar tudo)
all: $(TARGET)

# Criar o executável principal
$(TARGET): $(OBJS) $(LIB_NAME)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Criar a biblioteca estática
$(LIB_NAME): funcoes.o
	$(AR) rcs $(LIB_NAME) funcoes.o 

# Regra genérica para compilar qualquer arquivo .c em .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJS) $(LIB_NAME) $(TARGET)
