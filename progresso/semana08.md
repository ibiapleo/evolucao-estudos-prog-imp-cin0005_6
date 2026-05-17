# Semana 08

## O que foi estudado

- Unions e bitfields: definição, layout de campos e uso prático para decodificação de bytes e pacotes.
- Leitura e escrita de arquivos e tratamento de erros de I/O.
- Alocação dinâmica de vetores com `malloc`/`realloc`/`free` para armazenar linhas de CSV.
- Estratégias de parsing seguro (fscanf/sscanf, fgets + sscanf) e validação de entradas.

## Dificuldades

- Entender a ordenação e o comportamento de bitfields em diferentes compiladores (tamanho e alinhamento).
- Garantir leitura robusta de entradas mal formatadas sem travar o programa (uso combinado de `fgets` e `sscanf`).
- Gerenciar corretamente `realloc` e evitar vazamentos de memória em caminhos de erro.

## Aprendizados

- Aprendi a mapear representação binária para campos semânticos usando `union` + `struct` com bitfields.
- Ganhei prática em técnicas seguras de leitura de arquivos e validação de dados antes de aplicar mudanças de estado.
- Reforcei padrões de alocação dinâmica para coleções de tamanho variável e como redimensionar vetores de forma eficiente.

## Próximos passos

- Revisar comportamento de bitfields em diferentes arquiteturas e testar com casos de borda.
- Escrever testes adicionais com arquivos de entrada variada (incluindo casos mal formatados) para garantir robustez.
- Otimizar o uso de memória onde aplicável.

