# 📚 Compactador de Arquivos com Codificação de Huffman 📚

## Introdução
Bem-vindo ao nosso projeto de compactação de arquivos utilizando a Codificação de Huffman!

A Codificação de Huffman é uma técnica que utiliza a frequência dos caracteres em um texto para gerar códigos binários menores para caracteres mais frequentes. Isso resulta em uma compactação eficiente de dados. 
Vamos explorar os principais componentes do nosso projeto e suas funcionalidades. 🔍📄

## Implementação

### tLista 📜
Uma lista duplamente encadeada com sentinela, que guarda árvores com a frequência de cada caractere. Suas principais funções incluem:

- **InsereLista**: Insere uma árvore de forma ordenada na lista, organizando as frequências de cada nó em ordem crescente.
- **CriaListaNos**: Baseia-se num vetor de inteiros onde cada posição representa o código ASCII de um caractere e o conteúdo representa sua frequência.

### tTrilha 🧵
Uma pilha de caracteres projetada para preencher a tabela de codificação, otimizando a busca dos códigos de cada caractere. Funções importantes:

- **getInfoTrilha**: Concatena todos os caracteres da trilha para gerar uma string.
- **PreencheTabelaCodificacao**: Percorre a árvore de Huffman, inserindo '0' para nós à esquerda e '1' para nós à direita. Quando encontra um caractere (folha), insere o conteúdo da trilha gerada na tabela, no ID correspondente ao caractere.

### tAb 🌳
Uma árvore binária onde cada nó contém um caractere e uma frequência. Funções destacadas:

- **JoinAb**: Gera uma nova árvore cujos ramos são duas árvores passadas por parâmetro, com frequência resultante da soma dessas duas.
- **CriaArvoreHuf**: Utiliza a lista resultante de "CriaListaNos" e a função JoinAb recursivamente para criar uma árvore de Huffman até que reste apenas uma.

### Utils 🔧
Um TAD para suprir demandas gerais do projeto, incluído em quase todos os outros TADs. Funções importantes:

- **ContaFreqCaracteres**: Conta a frequência de cada caractere em um arquivo, armazenando os dados em um vetor de inteiros.
- **BinReadBitmap e BinDumpBitmap**: Funções responsáveis por ler e escrever o conteúdo de um bitmap em modo binário.

### bitmap 🖼️
Este TAD foi adicionado para suporte na manipulação de bits. Em nosso projeto, acrescentamos funções para adicionar e obter bytes do bitmap, utilizando as funções próprias deste TAD para operações com bytes inteiros.

## Comandos de Execução 🚀

Para testar o projeto, utilize os seguintes comandos no terminal:

- `make run-compacta`: O programa solicitará o nome de um arquivo (que deve estar no mesmo diretório do executável) para compactação.
- `make run-descompacta`: Este comando aceita apenas arquivos com a extensão `.comp` e descompacta o conteúdo. Se o arquivo original estiver no mesmo diretório, ele será sobrescrito.
- `make clean`: Exclui os executáveis gerados.

## Conclusão 🏁

Este projeto demonstra a aplicação prática dos conhecimentos adquiridos na disciplina de Estrutura de Dados, conferindo robustez e eficiência na manipulação de informações. A implementação da Codificação de Huffman, especialmente na manipulação de bits, exigiu um esforço considerável, mas foi facilitada pela biblioteca bitmap.

## Bibliografia 📚

- Materiais online da disciplina disponíveis no Classroom.
- Conversa com o ChatGPT sobre percorrer a árvore de Huffman: [ChatGPT Conversa 1](https://chatgpt.com/share/0c64bc06-6e6e-46c5-9efa-0f7c6d2c9ea7)
- Ajuda do ChatGPT para confecção de makefile: [ChatGPT Conversa 2](https://chatgpt.com/share/967b1426-2a2b-455e-b25d-a3833b7b2f87)
- Pesquisa de flags de compilação com o ChatGPT: [ChatGPT Conversa 3](https://chatgpt.com/share/56b08583-e341-4586-9884-3d1e15ebbf5d)

Esperamos que você aproveite e aprenda muito com este projeto! 😊👍
