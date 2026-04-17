# AT1 - Gerenciamento de Processos com fork e exec

Este diretório contém uma implementação da atividade usando um container Ubuntu para compilar e executar o programa em ambiente Linux.

## Estrutura de arquivos em at1

- ATIVIDADE.md
Descrição original do enunciado da tarefa.

- atividade.c
Código-fonte principal da atividade.
Implementa:
1. processo pai imprimindo a transposta de uma matriz 10x10;
2. processo filho executando comandos de busca em página de notícias via exec.

- Dockerfile
Define a imagem Ubuntu 22.04 com as ferramentas necessárias para compilar e executar.
Instala: build-essential (gcc e ferramentas de compilação), curl, grep, vim, ca-certificates e coreutils.
Também copia o conteúdo do diretório para dentro do container.

- Makefile
Atalhos para compilação.
Alvos:
1. all: compila atividade.c e gera o binário atividade;
2. clean: remove o binário gerado.

- .dockerignore
Evita enviar artefatos desnecessários no contexto de build da imagem Docker.

- README.md
Este guia: explica os arquivos, os comandos e sugere um roteiro de vídeo.

## Pré-requisitos

- Docker Desktop instalado e em execução.
- Estar no diretório at1 antes de executar os comandos.

## Comandos e o que fazem

### 1) Construir a imagem Docker

Comando:

```bash
docker build -t atividade-at1 .
```

Explicação dos argumentos:

- docker build
Cria uma imagem a partir de um Dockerfile.

- -t atividade-at1
Define a tag (nome) da imagem criada como atividade-at1.

- .
Contexto de build: diretório atual. O Dockerfile e os arquivos de at1 são lidos daqui.

Resultado esperado:
- imagem local chamada atividade-at1 disponível para execução.

### 2) Executar compilação e programa dentro do container

Opcao A (execucao direta em um comando):

```bash
docker run --rm atividade-at1 bash -lc "make clean && make && ./atividade"
```

Opcao B (modo iterativo/interativo, recomendado para desenvolvimento):

```bash
docker run --rm -it -v "$(pwd)":/workspace/at1 -w /workspace/at1 atividade-at1 bash
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

- -v "$(pwd)":/workspace/at1
Monta a pasta local atual dentro do container. Assim, qualquer edicao no host aparece no container sem rebuild da imagem.

- -w /workspace/at1
Define o diretorio de trabalho inicial dentro do container.

- atividade-at1
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
- saída do processo pai com matriz original e transposta;
- saída do processo filho com contagem de ocorrências de "Hamilton" na página de Fórmula 1 do ge.globo.

## Fluxo de execução do programa

1. O programa cria uma matriz 10x10 e chama fork.
2. O processo pai imprime a matriz original e sua transposta.
3. O processo filho chama exec para rodar um pipeline com curl, egrep e wc.
4. O pai usa wait para aguardar o término do filho e imprime o status final.
