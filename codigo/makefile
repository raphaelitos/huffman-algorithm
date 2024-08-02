# Definindo o compilador e as flags
CC = gcc
CFLAGS = -Wextra

# Nome do executável
TARGET = $(TARGET_NAME)

# Encontrando todos os arquivos .c, exceto o arquivo específico
SRCS_EXCLUDE_COMPACTA = $(filter-out descompacta.c, $(wildcard *.c))
SRCS_EXCLUDE_DESCOMPACTA = $(filter-out compacta.c, $(wildcard *.c))

# Diretório para os arquivos objeto temporários
OBJDIR = obj

# Criando a lista de arquivos objeto a partir dos arquivos .c
OBJS_COMPACTA = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS_EXCLUDE_COMPACTA))
OBJS_DESCOMPACTA = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS_EXCLUDE_DESCOMPACTA))

# Regra padrão
all: compacta descompacta

# Regra para criar o diretório de objetos
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Regra para compilar o executável (para compacta)
compacta: TARGET_NAME = compacta
compacta: $(OBJDIR) $(OBJS_COMPACTA)
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS_COMPACTA)
	@rm -rf $(OBJDIR)

# Regra para compilar o executável (para descompacta)
descompacta: TARGET_NAME = descompacta
descompacta: $(OBJDIR) $(OBJS_DESCOMPACTA)
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS_DESCOMPACTA)
	@rm -rf $(OBJDIR)

# Regra para compilar os arquivos .c em arquivos .o
$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	@rm -f compacta descompacta
	@rm -rf $(OBJDIR)

# Regra para compilar e rodar o executável com um arquivo como parâmetro
run: $(TARGET)
	@read -p "Digite o nome do arquivo: " FILE; \
	./$(TARGET) $$FILE

# Regra para compilar e rodar o executável específico
run-compacta: TARGET_NAME = compacta
run-compacta: compacta run

run-descompacta: TARGET_NAME = descompacta
run-descompacta: descompacta run

.PHONY: all clean run run-compacta run-descompacta compacta descompacta

