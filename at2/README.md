# AT2 - Cálculo de Números Perfeitos Usando Threads

Este diretório contém uma implementação da atividade usando um container Ubuntu para compilar e executar o programa em ambiente Linux.

## Estrutura de arquivos em at2

- ATIVIDADE.md
Descrição original do enunciado da tarefa.

- atividade.c
Código-fonte principal da atividade.
Implementa:
1. Múltiplas threads para busca paralela de números perfeitos;
2. Exclusão mútua com pthread_mutex para sincronização;
3. Cálculo eficiente de divisores para identificar números perfeitos;
4. Medição de tempo total de execução em milissegundos.

- Dockerfile
Define a imagem Ubuntu 22.04 com as ferramentas necessárias para compilar e executar.
Instala: build-essential (gcc e ferramentas de compilação), curl, grep, vim, ca-certificates e coreutils.
Também copia o conteúdo do diretório para dentro do container.

- Makefile
Atalhos para compilação com suporte a pthread.
Alvos:
1. all: compila atividade.c com -lpthread e gera o binário atividade;
2. clean: remove o binário gerado.

- .dockerignore
Evita enviar artefatos desnecessários no contexto de build da imagem Docker.

- README.md
Este guia: explica os arquivos, os comandos e sugere um roteiro de vídeo.

## Pré-requisitos

- Docker Desktop instalado e em execução.
- Estar no diretório at2 antes de executar os comandos.

## Comandos e o que fazem

### 1) Construir a imagem Docker

Comando:

```bash
docker build -t atividade-at2 .
```

Explicação dos argumentos:

- docker build
Cria uma imagem a partir de um Dockerfile.

- -t atividade-at2
Define a tag (nome) da imagem criada como atividade-at2.

- .
Contexto de build: diretório atual. O Dockerfile e os arquivos de at2 são lidos daqui.

Resultado esperado:
- imagem local chamada atividade-at2 disponível para execução.


### 2) Executar compilação e programa dentro do container

Opcao A (execucao direta em um comando):

```bash
docker run --rm atividade-at2 bash -lc "make clean && make && ./atividade"
```

Opcao B (modo iterativo/interativo, recomendado para desenvolvimento):

```bash
docker run --rm -it -v "$(pwd)":/workspace/at2 -w /workspace/at2 atividade-at2 bash
```

Depois, dentro do shell do container:

```bash
make clean
make
./atividade
```

Explicação dos argumentos:

- docker run
Inicia um container a partir de uma imagem.

- --rm
Remove o container automaticamente ao final da execução.

- -it
Abre terminal interativo (stdin + tty) para usar o shell do container.

- -v "$(pwd)":/workspace/at2
Monta a pasta local atual dentro do container. Assim, qualquer edicao no host aparece no container sem rebuild da imagem.

- -w /workspace/at2
Define o diretorio de trabalho inicial dentro do container.

- atividade-at2
Nome da imagem a ser executada.

- bash -lc "..."
Abre um shell bash e executa o comando passado entre aspas.

- make clean
Remove binário antigo para garantir build limpo.

- &&
Executa o próximo comando apenas se o anterior tiver sucesso.

- make
Compila o programa com as regras do Makefile.

- ./atividade
Executa o binário compilado.

Resultado esperado:
- saída com os 5 números perfeitos encontrados;
- indicação de qual thread encontrou cada número;
- tempo total de execução em milissegundos.

## Detalhes da Implementação

### Fórmula de Euclides-Euler

O programa usa a Fórmula de Euclides-Euler para encontrar números perfeitos de forma eficiente:

**Um número perfeito par tem a forma: 2^(p-1) × (2^p - 1)**

onde (2^p - 1) é um número primo de Mersenne.

Exemplos:
- p=2: 2^1 × 3 = **6**
- p=3: 2^2 × 7 = **28**
- p=5: 2^4 × 31 = **496**
- p=7: 2^6 × 127 = **8128**
- p=13: 2^12 × 8191 = **33550336**

### Sincronização com Mutex

- Cada thread obtém um expoente de Mersenne de forma atômica (protegida por mutex)
- Após calcular o número perfeito, a thread atualiza o contador (também protegido)
- Isso garante exclusão mútua sem impedir o paralelismo real das threads

### Concorrência

Múltiplas execuções podem gerar padrões diferentes de qual thread encontra qual número,
pois as threads competem pelos expoentes disponíveis. Isso demonstra concorrência real.
