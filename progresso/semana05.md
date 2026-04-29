# Semana 05

## O que foi estudado

Nesta semana estudei alocacao dinamica de memoria em C, com foco no gerenciamento da heap e no uso correto de ponteiros em arrays dinamicos.

- Gerenciamento da heap
- Alocacao e liberacao de memoria com `malloc` e `free`
- Redimensionamento de arrays com `realloc`
- Passagem de arrays dinamicos para funcoes
- Manipulacao de ponteiros dentro de funcoes

## Dificuldades

Tive mais dificuldade na questao 03 da lista de alocação dinâmica, principalmente na logica de insercao de novos valores e no redimensionamento dinamico com `realloc`.

No inicio fiquei confuso sobre quando realocar a memoria e como atualizar corretamente o ponteiro sem perder os dados ja armazenados.

## Aprendizados

Consolidei os conceitos de alocacao dinamica e entendi melhor como declarar arrays dinamicos em tempo de execucao.

Tambem aprendi a passar arrays dinamicos para funcoes e manipular ponteiros dentro dessas funcoes com mais seguranca.

Outro aprendizado importante foi o cuidado de sempre usar `free` ao final para evitar vazamento de memoria.

## Melhorias feitas

Revisei as solucoes para garantir melhor organizacao na manipulacao de memoria dinamica, especialmente na separacao da logica em funcoes auxiliares.

Na questao 03, refinei a estrutura da solucao apos receber um norte inicial, deixando o fluxo de insercao e realocacao mais claro.

## Próximos passos

Pretendo praticar mais exercicios com alocacao dinamica para ganhar mais confianca com `realloc` e com o gerenciamento de memoria em problemas maiores.

Tambem quero revisar padroes de validacao de alocacao para escrever codigos mais robustos e seguros.
