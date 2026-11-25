# SISTEMA-DE-CALCULADORA-DE-MATRIZES

Sistema de Calculadora de Matrizes
Descrição do projeto

Este projeto consiste no desenvolvimento de um sistema interativo de calculadora de matrizes, desenvolvido na linguagem C.

O programa permite que o usuário cadastre duas ou mais matrizes, informe suas dimensões e seus respectivos elementos, e execute operações matemáticas entre elas.

O sistema foi desenvolvido para aplicar conceitos de programação estruturada, modularização, alocação dinâmica de memória, manipulação de matrizes e operações matemáticas.

Funcionalidades

O sistema oferece as seguintes funcionalidades:

Cadastro de duas ou mais matrizes.
Definição da quantidade de linhas e colunas de cada matriz.
Preenchimento individual dos elementos.
Exibição das matrizes cadastradas.
Operação de adição de matrizes.
Operação de subtração de matrizes.
Operação de multiplicação de matrizes.
Operação de divisão matricial por meio da matriz inversa.
Validação das dimensões necessárias para cada operação.
Identificação de matrizes singulares (sem inversa).
Execução sequencial das operações, da esquerda para a direita.
Menu interativo para realizar várias operações.
Opção para encerrar o programa.
Operações matemáticas
Adição

A adição somente pode ser realizada quando as matrizes possuem a mesma quantidade de linhas e colunas.

Subtração

A subtração também exige que as matrizes tenham dimensões iguais.

Multiplicação

A multiplicação é possível quando o número de colunas da primeira matriz é igual ao número de linhas da segunda matriz.

Divisão

A divisão matricial é definida pela seguinte expressão:

A / B = A × B⁻¹

Para realizar essa operação, a matriz divisora precisa:

Ser quadrada.
Possuir inversa.
Ter dimensões compatíveis com a matriz anterior.

A inversa é calculada utilizando o método de Gauss-Jordan com pivoteamento parcial.

Tecnologias utilizadas
Linguagem C.
Biblioteca padrão stdio.h.
Biblioteca stdlib.h.
Biblioteca math.h.
Alocação dinâmica de memória.
Organização do projeto
text
calculadora-de-matrizes/
│
├── main.c
└── README.md

Como compilar

É necessário possuir um compilador C, como o GCC.

No terminal, execute:

bash
gcc main.c -o calculadora -lm


A opção -lm realiza a ligação com a biblioteca matemática.

Como executar

No Linux ou macOS:

bash
./calculadora


No Windows:

bash
calculadora.exe

Como utilizar
Execute o programa.
Informe a quantidade de matrizes que deseja cadastrar (mínimo de duas).
Informe a quantidade de linhas e colunas de cada matriz.
Digite individualmente os valores de cada elemento.
Escolha uma operação no menu apresentado.
Visualize o resultado da operação.
Escolha outra operação ou encerre o programa.
Modularização

O programa foi organizado em funções específicas para facilitar a manutenção e compreensão do código.

Função	Responsabilidade
criarMatriz()	Alocar memória para uma matriz.
lerMatriz()	Receber os elementos da matriz.
exibirMatriz()	Apresentar a matriz na tela.
copiarMatriz()	Criar uma cópia de uma matriz.
somarMatrizes()	Realizar a adição.
subtrairMatrizes()	Realizar a subtração.
multiplicarMatrizes()	Realizar a multiplicação.
inverterMatriz()	Calcular a matriz inversa.
dividirMatrizes()	Realizar a divisão matricial.
liberarMatriz()	Liberar a memória utilizada.
main()	Coordenar o funcionamento do programa.
Observações
O programa utiliza alocação dinâmica de memória, permitindo matrizes com diferentes dimensões.
As operações com três ou mais matrizes são realizadas sequencialmente, da esquerda para a direita.
A divisão utiliza números reais (double), permitindo resultados com casas decimais.
Matrizes singulares não podem ser utilizadas como divisoras.
A memória alocada é liberada ao final da execução.
Autor

Projeto acadêmico desenvolvido para a atividade de programação em linguagem C.
