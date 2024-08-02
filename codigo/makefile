# Definindo o compilador e as flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Nome do executável
TARGET = $(TARGET_NAME)

# Encontrando todos os arquivos .c, exceto o arquivo específico
SRCS_EXCLUDE_COMPACTA = $(filter-out compacta.c, $(wildcard *.c))
SRCS_EXCLUDE_DESCOMPACTA = $(filter-out descompacta.c, $(wildcard *.c))

# Criando a lista de arquivos objeto a partir dos arquivos .c
OBJS_COMPACTA = $(SRCS_EXCLUDE_COMPACTA:.c=.o)
OBJS_DESCOMPACTA = $(SRCS_EXCLUDE_DESCOMPACTA:.c=.o)

# Regra padrão
all: $(TARGET)

# Regra para compilar o executável (para compacta)
compacta: TARGET_NAME = compacta
compacta: $(OBJS_COMPACTA)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS_COMPACTA)

# Regra para compilar o executável (para descompacta)
descompacta: TARGET_NAME = descompacta
descompacta: $(OBJS_DESCOMPACTA)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS_DESCOMPACTA)

# Regra para compilar os arquivos .c em arquivos .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(TARGET) $(OBJS_COMPACTA) $(OBJS_DESCOMPACTA)

# Regra para compilar e rodar o executável com um arquivo como parâmetro
run: all
	@read -p "Digite o nome do arquivo: " FILE; \
	./$(TARGET) $$FILE

# Regra para compilar e rodar o executável específico
run-%: TARGET_NAME=$*
run-%: $(TARGET) run

.PHONY: all clean run run-compacta run-descompacta compacta descompacta

