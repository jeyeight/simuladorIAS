# simuladorIAS

Trabalho destinado a disciplina de Arquitetura e Organização de Computadores I.

Consiste em uma implementação de um Computador IAS na linguagem de programação C, onde as instrução são executadas através de uma simulação de um pipeline escalar com 5 etapas:
- Busca
- Decodificação
- Busca de Operandos
- Execução
- Escrita de Resultados

Para fornecer o arquivo de entrada e saída para o simulador, use os seguintes argumentos na hora de executar o programa:

./nomeexecutavel -p <nomearquivoentrada.ias> -i "Valor Onde começam as instruções (500>)"

Exemplo: "./bin/main -p programas/fatorial/fatorial.ias -i 500

O arquivo de entrada deve conter o peso de execução (em ciclos de clock) para cada operação possível do IAS, além das instruções que serão passadas para o computador. As instruções são compostas pelas 21 instruções padrão, com uma instrução extra para interromper a execução, chamada de EXIT.

```
LOAD MQ  = LOADM:
LOAD MQ,M(X) = LOADMM:
STOR M(X) = STOR:
LOAD M(X) = LOAD:
LOAD –M(X) = LOAD-M:
LOAD |M(X)| = LOAD|M:
LOAD –|M(X)| = LOAD-|M:
JUMP M(X,0:19) = JUMP:
JUMP M(X,20:39) = JUMP:
JUMP + M ( X , 0 : 19) = JUMP+:
JUMP + M ( X , 20 : 39) = JUMP+:
ADD M(X) = ADD:
ADD |M(X)| = ADD|: ?
SUB M(X) = SUB:
SUB |M(X)| = SUB|: 
MUL M(X) = MUL:
DIV M(X) = DIV:
LSH = LSH:
RSH = RSH: 
STOR M(X,8:19) STORM:
STOR M(X,28:39) STORM: 
```

Os dados armazenados após a execução podem ser viualizados no arquivo de saída "inoutfiles/saida.ias.m", que contém toda a memória do IAS.

