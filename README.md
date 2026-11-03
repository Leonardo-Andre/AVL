🌳 Implementação de Árvore AVL em C

Este repositório contém a implementação de uma Árvore AVL (uma árvore binária de busca autobalanceada) desenvolvida na linguagem C. O projeto foi estruturado como uma atividade acadêmica para gerenciar dados de "Alunos" utilizando esta estrutura de dados eficiente.

📂 Estrutura do Projeto

O projeto é modularizado e dividido nos seguintes arquivos:

avl.h e avl.c: Contêm a definição da estrutura da Árvore AVL e a implementação de suas funções principais, como:

Inserção de nós

Remoção de nós

Balanceamento (Rotações à esquerda, à direita, duplas)

Busca e travessias (em-ordem, pré-ordem, pós-ordem)

aluno.h e aluno.c: Definem a estrutura dos dados que serão armazenados na árvore (ex: matrícula, nome, notas do aluno) e suas funções de manipulação.

main.c: Arquivo principal que contém a função main(). Ele serve para testar a estrutura e demonstrar o uso da árvore AVL gerenciando os dados dos alunos.

.vscode/: Contém os arquivos launch.json e tasks.json configurados para compilar e depurar o projeto facilmente usando o Visual Studio Code.

🚀 Como Compilar e Executar

Para rodar este projeto, você precisará de um compilador C (como o gcc) instalado em sua máquina.

Via Terminal

Abra o terminal e navegue até o diretório do projeto (AVL-main).

Compile o código executando o seguinte comando:

gcc main.c avl.c aluno.c -o programa_avl


Execute o programa gerado:

No Linux/macOS:

./programa_avl


No Windows:

programa_avl.exe


Usando o VS Code

Como o projeto já inclui a pasta .vscode, basta abrir a pasta raiz do projeto no Visual Studio Code e pressionar F5 (ou ir na aba Run and Debug e iniciar o processo). Ele usará as tarefas pré-configuradas em tasks.json para compilar e o launch.json para rodar/depurar o código automaticamente.

📚 Sobre a Árvore AVL

A árvore AVL é uma árvore de busca binária onde a diferença de altura entre as subárvores esquerda e direita de qualquer nó (o fator de balanceamento) é no máximo 1. Isso garante que as operações de busca, inserção e remoção tenham um tempo de execução de O(log n), tornando-a altamente eficiente para grandes conjuntos de dados.
