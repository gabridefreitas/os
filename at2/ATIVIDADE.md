# Tarefa - Cálculo de Números Perfeitos Usando Threads

Para exercitarmos os conceitos estudados até o momento, realizaremos uma atividade prática focada no **uso de threads e sincronização com exclusão mútua**.

A atividade pode ser realizada em **colaboração**. Vocês têm a opção de formar **grupos de até 3 alunos** para trabalhar juntos. Esta é uma ótima oportunidade para combinar habilidades, compartilhar ideias e aprender uns com os outros. Lembrem-se de coordenar bem e distribuir as tarefas para que todos contribuam igualmente.

## Objetivo da Atividade

Desenvolver um programa em **C** utilizando **threads** para encontrar e exibir **os 5 primeiros números perfeitos**. Além disso, o programa deve:
- Utilizar pelo menos **2 threads** para a busca, mas pode utilizar mais dependendo dos recursos do computador ou da máquina virtual utilizada.
- Cada thread deve acessar uma **variável global compartilhada** para obter o próximo número a ser verificado.
- Deve ser garantida a **exclusão mútua** para evitar conflitos no acesso à variável compartilhada.
- Sempre que um número perfeito for encontrado, o programa deve imprimir:
    - **O número perfeito encontrado**.
    - **Qual thread encontrou esse número**.
- O tempo total de execução do programa deve ser medido e exibido ao final, em **milissegundos**.

---

## Requisitos do Programa

1️⃣ **Execução paralela eficiente**

- O programa deve usar **pthread** para criar e gerenciar threads.
- As threads devem rodar **simultaneamente**, garantindo paralelismo real.

2️⃣ **Controle de concorrência correto**

- O acesso à variável global que define o **próximo número a ser testado** deve ser protegido usando **mutex** ou **semaforos**.
- O uso de mutex **não deve impedir a execução paralela das threads**, ou seja, o bloqueio deve ocorrer **apenas onde for necessário**.

3️⃣ **Medição do tempo de execução**

- O tempo total de execução deve ser impresso ao final, mostrando **quantos milissegundos o programa demorou** para encontrar os 5 primeiros números perfeitos.

4️⃣ **Mensagens informativas**

- Sempre que uma **thread encontrar um número perfeito**, o programa deve exibir a mensagem:

```sh
Thread X encontrou o número perfeito: Y
```

---

## Ambiente de Desenvolvimento

O programa deve ser desenvolvido e testado em terminal **Linux**.
Utilize o mesmo ambiente configurado nos desafios anteriores (Módulos II e III).

Para compilar o código, use:

```sh
gcc -o numeros_perfeitos numeros_perfeitos.c -lpthread 
```

E para executar:

```sh
./numeros_perfeitos 
```

---

## O que deve ser entregue?

- **Código-fonte** do programa em C (`.c`).
- **Vídeo de até 3 minutos** demonstrando a **compilação, execução e explicação do código**.
    - O vídeo deve começar com os **nomes completos** dos participantes.
    - A execução do código deve mostrar claramente os **números perfeitos encontrados, qual thread os encontrou e o tempo total de execução**.

### Atenção!

- Trabalhos **copiados** da internet ou de outros colegas **receberão nota zero automaticamente** para todos os envolvidos.
- Trabalhos entregues **sem o vídeo** ou com **vídeo maior que 3 minutos não serão avaliados**.
- O código deve **compilar e executar corretamente** em um ambiente Linux.
- O uso de **mutex e threads deve ser feito corretamente**, garantindo concorrência real.

**Boa sorte e bons estudos!**